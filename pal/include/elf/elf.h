#pragma once

#include <features.h>
#include <stdint.h>

__BEGIN_DECLS

#define __ELF_NATIVE_CLASS 64

#define ElfW(type)       _ElfW(Elf, __ELF_NATIVE_CLASS, type)
#define ELFW(type)       _ElfW(ELF, __ELF_NATIVE_CLASS, type)
#define _ElfW(e, w, t)   _ElfW_1(e, w, _##t)
#define _ElfW_1(e, w, t) e##w##t

typedef ElfW(Addr)   elf_addr_t;
typedef ElfW(auxv_t) elf_auxv_t;
typedef ElfW(Dyn)    elf_dyn_t;
typedef ElfW(Ehdr)   elf_ehdr_t;
typedef ElfW(Half)   elf_half_t;
typedef ElfW(Off)    elf_off_t;
typedef ElfW(Phdr)   elf_phdr_t;
typedef ElfW(Rela)   elf_rela_t;
typedef ElfW(Sym)    elf_sym_t;
typedef ElfW(Word)   elf_word_t;
typedef ElfW(Xword)  elf_xword_t;

__END_DECLS