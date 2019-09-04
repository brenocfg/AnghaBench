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

/* Variables and functions */
 scalar_t__ Booted ; 
 int GetSR (int) ; 
 int PPC_VSID_MASK ; 
 int /*<<< orphan*/ * Segs ; 
 int /*<<< orphan*/  SetSR (int,int) ; 
 int* Vsid ; 
 int /*<<< orphan*/  findvsid (int) ; 

void mmusetvsid(int start, int end, int vsid)
{
    int i, sr, s_vsid;
    for(i = start; i < end; i++)
    {
	s_vsid = (vsid << 4) | (i & 15);
	sr = (GetSR(i) & ~PPC_VSID_MASK) | s_vsid;
	if (Booted)
            SetSR(i, sr);
	Segs[i] = findvsid(s_vsid);
        Vsid[i] = vsid;
    }
}