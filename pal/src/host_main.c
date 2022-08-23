#include "api.h"
#include "pal_internal_arch.h"
#include "pal_linux_defs.h"
#include "log.h"
#include "syscall.h"
#include "elf.h"
#include "pal_linux.h"
#include "host_internal.h"
#include "linux_utils.h"

#include <stdnoreturn.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <asm/errno.h>
#include <string.h>

pid_t g_host_pid;
char* g_pal_loader_path;

noreturn static void print_usage_and_exit(const char* argv_0){
    const char* self = argv_0 ?: "<this program>";
    log_always("USAGE:\n"
               "\tFirst process: %s <path to libpal.so> init <application> args...\n"
               "\tChildren:      %s <path to libpal.so> child <parent_stream_fd> args...",
               self, self);
    log_always("This is an internal interface. Use pal_loader to launch applications in "
               "Gramine.");
    DO_SYSCALL(exit_group,1);
    die_or_inf_loop();
}

static void force_linux_to_grow_stack(void){
    ARCH_PROBE_STACK(THREAD_STACK_SIZE,PRESET_PAGESIZE);
}

static int get_aux_value(char** envp, uint64_t type, uint64_t* out_value){
    while(*envp)
        envp++;
    
    for(elf_auxv_t* auxv = (elf_auxv_t*)(envp+1); auvx->a_type != AT_NULL; auxv++){
        if(auxv->a_type == type){
            *out_value = auxv->a_un.a_val;
            return 0;
        }
    }
    return -1;
}
char* g_libpal_path = NULL ;
struct pal_enclave g_pal_enclave;

__attribute_no_sanitize_address
int main(int argc, char* argv[], char* envp[]){
    bool need_gsgx = true;
    char* manifest_path = NULL;
    char* manifest = NULL;
    int ret = 0;

    force_linux_to_grow_stack();

    if(argc < 4)
        print_usage_and_exit(argv[0]);
    
    g_host_pid=DO_SYSCALL(getpid);

    g_pal_loader_path = get_main_exec_path();
    if(!g_pal_loader_path)
        return -ENOMEM;
    
    /* check whether host kernel supports FSGSBASE feature, otherwise we need the GSGX driver */
    uint64_t at_hwcap2;
    if(get_aux_value(envp, AT_HWCAP2, &at_hwcap2) == 0 && (at_hwcap2 & 0x2)){
        need_gsgx = false;
    }

    g_libpal_path = strdup(argv[1]);
    if(!g_libpal_path){
        return -ENOMEM;
    }

    bool first_process = !strcmp(argv[2], "init");
    if(!first_process && strcmp(argv[2], "child")){
        print_usage_and_exit(argv[0]);
    }

    int parent_process_fd = -1;

    if(first_process){
        g_pal_enclave.is_first_process = true;

        g_pal_enclave.application_path = argv[3];
        manifest_path = alloc_concat(g_pal_enclave.application_path, -1, ".manifest.sgx", -1);
        if(!manifest_path){
            return -ENOMEM;
        }

        log_debug("Manifest file: %s", manifest_path);
        ret = read_text_file_to_cstr(manifest_path, &manifest);
        if(ret < 0){
            log_error("Reading manifest failed");
            return ret;
        }
        free(manifest_path);
        manifest_path = NULL;
    }else {
        g_pal_enclave.is_first_process = false;

        parent_process_fd = atoi(argv[3]);
        ret = sgx_init_child_process();
        if(ret < 0)
            return ret;
    }
    g_pal_enclave.raw_manifest = manifest;
    
    /*
     * While C does not guarantee that the argv[i] and envp[i] strings are
     * continuous we know that we are running on Linux, which does this. This
     * saves us creating a copy of all argv and envp strings.
     */
    
}