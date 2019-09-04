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
typedef  int /*<<< orphan*/  ole_priv_data ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int /*<<< orphan*/  DVTARGETDEVICE ;

/* Variables and functions */

__attribute__((used)) static inline DVTARGETDEVICE *td_offs_to_ptr(ole_priv_data *data, DWORD_PTR off)
{
    if(off == 0) return NULL;
    return (DVTARGETDEVICE*)((char*)data + off);
}