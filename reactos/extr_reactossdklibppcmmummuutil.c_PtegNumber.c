#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int vaddr_t ;

/* Variables and functions */
 int GetSR (int) ; 
 int HTABSIZ ; 
 int PPC_VSID_MASK ; 

int PtegNumber(vaddr_t virt, int hfun)
{
    int sr = GetSR( (virt >> 28) & 0xf );
    int vsid = sr & PPC_VSID_MASK;
    return ((((vsid & 0x7ffff) ^ ((virt >> 12) & 0xffff)) ^ (hfun ? -1 : 0)) & ((HTABSIZ - 1) >> 3) & 0x3ff);
}