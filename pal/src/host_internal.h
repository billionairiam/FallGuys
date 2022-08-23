#include "api.h"
#include "pal_linux.h"

struct pal_enclave
{
    bool is_first_process;

    char* application_path;
    char* raw_manifest;
    unsigned long baseaddr;
    unsigned long size;
    unsigned long thread_num;
    unsigned long rpc_thread_num;
    unsigned long ssa_frame_size;
    bool nopie_binary;
    enum sgx_attestation_type attestation_type;
    char* libpal_uri;
};
