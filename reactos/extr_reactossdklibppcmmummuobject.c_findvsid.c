#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int vsid; struct TYPE_4__* next; } ;
typedef  TYPE_1__ MmuVsidInfo ;

/* Variables and functions */
 TYPE_1__* VsidHead ; 

MmuVsidInfo *findvsid(int vsid)
{
    MmuVsidInfo *info;
    for(info = VsidHead; info; info = info->next)
    {
	if(info->vsid == vsid) return info;
    }
    return 0;
}