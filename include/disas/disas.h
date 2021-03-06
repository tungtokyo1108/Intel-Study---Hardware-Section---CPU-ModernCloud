/*
 * disas.h
 *
 *  Created on: Dec 7, 2018
 *      Student (MIG Virtual Developer): Tung Dang
 */

#ifndef DISAS_DISAS_H_
#define DISAS_DISAS_H_

#include "qemu-common.h"

#ifdef NEED_CPU_H
#include "qom/cpu.h"

void disas(FILE *out, void *code, unsigned long size);
void target_disas(FILE *out, CPUState *cpu, target_ulong code, target_ulong size);
void monitor_disas(Monitor *mon, CPUState *cpu, target_ulong pc, int nb_insn, int is_physical);
const char *lookup_symbol(target_ulong orig_addr);

#endif

struct syminfo;
struct elf32_sym;
struct elf64_sym;

#if defined(CONFIG_USER_ONLY)
typedef const char *(*lookup_sysmbol_t)(struct syminfo *s, target_ulong orig_addr);
#else
typedef const char *(*lookup_sysmbol_t)(struct syminfo *s, hwaddr orig_addr);
#endif

struct syminfo {
    lookup_symbol_t lookup_symbol;
    unsigned int disas_num_syms;
    union {
        struct elf32_sym *elf32;
        struct elf64_sym *elf64;
    } disas_symtab;
    const char *disas_strtab;
    struct syminfo *next;
};

extern struct syminfo *syminfos;

#endif /* DISAS_DISAS_H_ */
