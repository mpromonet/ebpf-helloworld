#include <cstdio>
#include <iostream>

#include "example.skel.h"

int main()
{
    auto *skel = example_bpf::open_and_load();
    if (skel == nullptr) {
        std::cerr << "Failed to load BPF program\n";
        return 1;
    }

    int err = example_bpf::attach(skel);
    if (err) {
        std::cerr << "Failed to attach tracepoint: " << err << '\n';
        example_bpf::destroy(skel);
        return 1;
    }

    std::cout << "Tracepoint attached. Press Enter to detach.\n";
    std::getchar();

    example_bpf::destroy(skel);
    return 0;
}