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
struct TYPE_3__ {scalar_t__ p_type; unsigned int p_flags; size_t p_vaddr; size_t p_filesz; size_t p_memsz; } ;
typedef  TYPE_1__ Elf32_Phdr ;
typedef  int Elf32_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ) ; 
 unsigned int const ET_EXEC ; 
 int MAP_ANONYMOUS ; 
 int MAP_FIXED ; 
 int MAP_PRIVATE ; 
 unsigned int PAGE_MASK ; 
 unsigned int PF_X ; 
 int /*<<< orphan*/  PROT_NONE ; 
 scalar_t__ PT_LOAD ; 
 int /*<<< orphan*/  STR_xfind_pages () ; 
 int /*<<< orphan*/  mflags ; 
 char* mmap (void*,size_t,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_brk ; 
 int umax (int,int) ; 

__attribute__((used)) static unsigned long  // returns relocation constant
#if defined(__i386__)  /*{*/
__attribute__((regparm(3), stdcall))
#endif  /*}*/
xfind_pages(unsigned const e_type, Elf32_Phdr const *phdr, int phnum,
    Elf32_Addr old_hi[2])
{
    size_t sz[2]= { 0u,  0u};  // [0] is .data;  [1] is .text
    size_t hi[2]= { 0u,  0u};
    size_t lo[2]= {~0u, ~0u};
    char *addr[2];
    unsigned level= 0;
    int j;

    DPRINTF((STR_xfind_pages(), mflags, phdr, phnum, p_brk));
    for (; --phnum>=0; ++phdr) if (PT_LOAD==phdr->p_type) {
        unsigned const td = PF_X & phdr->p_flags;  // requires 1==PF_X
        if (lo[td] > phdr->p_vaddr) {
            lo[td] = phdr->p_vaddr;
            sz[td] = phdr->p_filesz;
        }
        if (hi[td] < (phdr->p_memsz + phdr->p_vaddr)) {
            hi[td] =  phdr->p_memsz + phdr->p_vaddr;
        }
    }
    if ((ET_EXEC!=e_type) && 0x20000000u<=hi[0]) { // is split
        level=  (0xfc000000u & old_hi[1]) +  // "segment base" of old .text
            umax(0x03ffffffu & old_hi[1],
                 0x03ffffffu & old_hi[0] );
        level= PAGE_MASK & (level - PAGE_MASK -1);  // ALIGN_UP
    }
    for (j=0; j<=1; ++j) {
        sz[j] += ~PAGE_MASK & lo[j];  // page fragment on lo edge
        lo[j] -= ~PAGE_MASK & lo[j];  // round down to page boundary
        old_hi[j] = level + hi[j];
        hi[j]  =  PAGE_MASK & (hi[j] - lo[j] - PAGE_MASK -1);  // page length
        sz[j]  =  PAGE_MASK & (sz[j]         - PAGE_MASK -1);  // page length
        addr[j] = mmap((void *)(level + lo[j]), hi[j], PROT_NONE,
            MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    }
    return (unsigned long)addr[0] - lo[0];
}