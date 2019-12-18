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
 unsigned int MAP_FIXED ; 
 unsigned int MAP_PRIVATE ; 
 size_t PAGE_MASK ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 scalar_t__ PT_LOAD ; 
 int /*<<< orphan*/  do_brk (void*) ; 
 char* mmap (void*,size_t,int,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long  // returns relocation constant
__attribute__((regparm(3), stdcall))
xfind_pages(unsigned mflags, Elf32_Phdr const *phdr, int phnum)
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
    if (MAP_FIXED & mflags) { // the "shell", and not the PT_INTERP
        // This is a dirty hack to set the proper value for brk(0) as seen by
        // the "shell" which we will mmap() soon, upon return to do_xmap().
        // It depends on our own brk() starting out at 0x08048000, which is the
        // default base address used by /bin/ld for an ET_EXEC.  We must brk()
        // now.  If we wait until after mmap() of shell pages, then the kernel
        // "vma" containing our original brk() of 0x08048000 will not be contiguous
        // with  hi  [the mmap'ed pages from the shell will be in between],
        // and various linux kernels will not move the brk() in this case;
        // the typical symptom is SIGSEGV early in ld-linux.so.2 (the PT_INTERP).
        do_brk((void *)hi);
    }
    szlo += ~PAGE_MASK & lo;  // page fragment on lo edge
    lo   -= ~PAGE_MASK & lo;  // round down to page boundary
    hi    =  PAGE_MASK & (hi - lo - PAGE_MASK -1);  // page length
    szlo  =  PAGE_MASK & (szlo    - PAGE_MASK -1);  // page length
    addr = mmap((void *)lo, hi, PROT_READ|PROT_WRITE|PROT_EXEC, mflags, -1, 0);

    // Doing this may destroy the brk() that we set so carefully above.
    // The munmap() is "needed" only for discontiguous PT_LOAD,
    // and neither shells nor ld-linux.so.2 have that.
    // munmap(szlo + addr, hi - szlo);

    return (unsigned long)addr - lo;
}