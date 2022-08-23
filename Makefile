OS_TYPE ?= $(findstring Ubuntu, $(shell cat /etc/os-release | grep -w NAME))$
ifeq ($(OS_TYPE),Ubuntu)
GRAMINE_PKGLIBDIR ?= /usr/lib/x86_64-linux-gnu/gramine
ARCH_LIBDIR ?= /lib/$(shell $(CC) -dumpmachine)
else
ifeq ($(OS_TYPE),Anolis OS)
GRAMINE_PKGLIBDIR ?= /usr/lib64/gramine
ARCH_LIBDIR ?= /lib64
else
GRAMINE_PKGLIBDIR ?= /usr/lib64/gramine
ARCH_LIBDIR ?= /lib64
endif
endif