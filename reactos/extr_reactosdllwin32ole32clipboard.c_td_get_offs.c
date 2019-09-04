#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* entries; } ;
typedef  TYPE_3__ ole_priv_data ;
struct TYPE_5__ {int /*<<< orphan*/ * ptd; } ;
struct TYPE_6__ {TYPE_1__ fmtetc; } ;
typedef  int DWORD_PTR ;
typedef  size_t DWORD ;

/* Variables and functions */

__attribute__((used)) static inline DWORD_PTR td_get_offs(ole_priv_data *data, DWORD idx)
{
    if(data->entries[idx].fmtetc.ptd == NULL) return 0;
    return (char*)data->entries[idx].fmtetc.ptd - (char*)data;
}