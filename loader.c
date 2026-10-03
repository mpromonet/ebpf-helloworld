#include <stdio.h>
#include "example.skel.h"

int main(void)
{
    struct example_bpf *skel = example_bpf__open_and_load();
    if (!skel) {
        fprintf(stderr, "Failed to load BPF program\n");
        return 1;
    }

    int err = example_bpf__attach(skel);
    if (err) {
        fprintf(stderr, "Failed to attach uprobe: %d\n", err);
        example_bpf__destroy(skel);
        return 1;
    }

    puts("Tracepoint attached. Press Enter to detach.");
    getchar();

    example_bpf__destroy(skel);
    return 0;
}