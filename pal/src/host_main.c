#include "api.h"
#include "pal_internal_arch.h"
#include "pal_linux_defs.h"
#include "log.h"
#include <stdnoreturn.h>


noreturn static void print_usage_and_exit(const char* argv_0){
    const char* self = argv_0 ?: "<this program>";
    log_always("USAGE:\n"
               "\tFirst process: %s <path to libpal.so> init <application> args...\n"
               "\tChildren:      %s <path to libpal.so> child <parent_stream_fd> args...",
               self, self);
    log_always("This is an internal interface. Use pal_loader to launch applications in "
               "Gramine.");
    
     
}

static void force_linux_to_grow_stack(void){
    ARCH_PROBE_STACK(THREAD_STACK_SIZE,PRESET_PAGESIZE);
}

__attribute_no_sanitize_address
int main(int argc, char* argv[], char* envp[]){
    force_linux_to_grow_stack();

    if(argc < 4)
        print_usage_and_exit(argv[0]);
}