#define MSG_SIZE 128

// Include the vmlinux.h header for kernel structures and definitions
#include "vmlinux.h"

// Include the BPF-specific functions
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>

// Tracepoint for the sys_enter_unlinkat syscall
SEC("tracepoint/syscalls/sys_enter_unlinkat")
int trace_unlinkat(struct trace_event_raw_sys_enter* ctx) {
 
    // Get the current process ID
    __u32 pid = bpf_get_current_pid_tgid() >> 32;

    // Get the current command name (process name)
    char comm[16];
    bpf_get_current_comm(&comm, sizeof(comm));

    // Read the filename argument from user space
    char filename[256];
    bpf_probe_read_user_str(&filename, sizeof(filename), (void *)(ctx->args[1]));

    bpf_printk("Intercepted unlinkat: pid=%d, comm=%s, filename=%s\n", pid, comm, filename);

    return 0; // Return 0 to indicate success
}

// Define the license for the eBPF program
char _license[] SEC("license") = "GPL";