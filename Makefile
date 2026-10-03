BPFTOOL ?= bpftool
BPF_CFLAGS ?= -O2 -g -target bpf -I.
LIBBPF_FLAGS := $(shell pkg-config --cflags --libs libbpf)

.PHONY: all clean

all: loader

vmlinux.h:
	$(BPFTOOL) btf dump file /sys/kernel/btf/vmlinux format c > $@

example.bpf.o: example.bpf.c vmlinux.h
	clang $(BPF_CFLAGS) -c $< -o $@

example.skel.h: example.bpf.o
	$(BPFTOOL) gen skeleton $< > $@

loader: loader.cpp example.skel.h
	clang++ -O2 -g $< -o $@ $(LIBBPF_FLAGS)

clean:
	rm -f example.bpf.o example.skel.h loader
