#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ objects; int /*<<< orphan*/  imagesize; } ;
struct TYPE_3__ {scalar_t__ vaddr; int /*<<< orphan*/  vsize; int /*<<< orphan*/  rawdataptr; } ;

/* Variables and functions */
 int MAP_ANONYMOUS ; 
 int MAP_FIXED ; 
 int MAP_PRIVATE ; 
 int /*<<< orphan*/  MEM_COMMIT ; 
 int /*<<< orphan*/  PAGE_EXECUTE_READWRITE ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ UPX_MMAP_ADDRESS ; 
 scalar_t__ VirtualAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int errno ; 
 int /*<<< orphan*/  f ; 
 int fread (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ ih ; 
 TYPE_1__* isections ; 
 scalar_t__ mmap (void*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int print (char*,...) ; 
 scalar_t__ vaddr ; 

__attribute__((used)) static int read(void)
{
    unsigned ic;
#ifdef __linux__
    vaddr = mmap((void *) UPX_MMAP_ADDRESS, ih.imagesize,
                 PROT_WRITE | PROT_READ | PROT_EXEC,
                 MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
    if (((int) vaddr) == -1)
        return print("mmap() failed: %d\n", errno);
    print("mmap for %p (size %x) successful\n", vaddr, ih.imagesize);
#else
    if ((vaddr = VirtualAlloc(0, ih.imagesize,
                              MEM_COMMIT, PAGE_EXECUTE_READWRITE)) == 0)
        return print("VirtualAlloc() failed\n");
    print("VirtualAlloc() ok %x\n", vaddr);
#endif
    for (ic = 1; ic <= (unsigned) ih.objects - 1; ic++)
        if (fseek(f, isections[ic].rawdataptr, SEEK_SET)
            || fread(vaddr + isections[ic].vaddr,
                     isections[ic].vsize, 1, f) != 1)
            return print("error reading section %u\n", ic);
    return 0;
}