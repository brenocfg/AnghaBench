#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ p_type; size_t p_vaddr; size_t p_filesz; size_t p_memsz; } ;
typedef  TYPE_1__ Elf32_Phdr ;

/* Variables and functions */
 unsigned int MAP_ANONYMOUS ; 
 unsigned int MAP_PRIVATE ; 
 size_t PAGE_MASK ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 scalar_t__ PT_LOAD ; 
 char* mmap (void*,size_t,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (char*,size_t) ; 

__attribute__((used)) static unsigned long  // returns relocation constant
__attribute__((regparm(3), stdcall))
xfind_pages(unsigned mflags, Elf32_Phdr const *phdr, int phnum,
    char **const p_brk
)
{
    size_t lo= ~0, hi= 0, szlo= 0;
    char *addr;
    mflags += MAP_PRIVATE | MAP_ANONYMOUS;  // '+' can optimize better than '|'
    for (; --phnum>=0; ++phdr) if (PT_LOAD==phdr->p_type) {
        if (phdr->p_vaddr < lo) {
            lo = phdr->p_vaddr;
            szlo = phdr->p_filesz;
        }
        if (hi < (phdr->p_memsz + phdr->p_vaddr)) {
            hi =  phdr->p_memsz + phdr->p_vaddr;
        }
    }
    szlo += ~PAGE_MASK & lo;  // page fragment on lo edge
    lo   -= ~PAGE_MASK & lo;  // round down to page boundary
    hi    =  PAGE_MASK & (hi - lo - PAGE_MASK -1);  // page length
    szlo  =  PAGE_MASK & (szlo    - PAGE_MASK -1);  // page length
    addr = mmap((void *)lo, hi, PROT_READ|PROT_WRITE|PROT_EXEC, mflags, 0, 0);
    *p_brk = hi + addr;  // the logical value of brk(0)
    munmap(szlo + addr, hi - szlo);  // desirable if PT_LOAD non-contiguous
    return (unsigned long)addr - lo;
}