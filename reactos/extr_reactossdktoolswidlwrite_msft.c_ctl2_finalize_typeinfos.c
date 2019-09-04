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
struct TYPE_6__ {TYPE_3__* typeinfos; } ;
typedef  TYPE_2__ msft_typelib_t ;
struct TYPE_7__ {scalar_t__* var_data; scalar_t__* func_data; TYPE_1__* typeinfo; struct TYPE_7__* next_typeinfo; } ;
typedef  TYPE_3__ msft_typeinfo_t ;
struct TYPE_5__ {int memoffset; int cElement; } ;

/* Variables and functions */

__attribute__((used)) static void ctl2_finalize_typeinfos(msft_typelib_t *typelib, int filesize)
{
    msft_typeinfo_t *typeinfo;

    for (typeinfo = typelib->typeinfos; typeinfo; typeinfo = typeinfo->next_typeinfo) {
	typeinfo->typeinfo->memoffset = filesize;
	if (typeinfo->func_data)
	    filesize += typeinfo->func_data[0] + ((typeinfo->typeinfo->cElement & 0xffff) * 12);
	if (typeinfo->var_data)
	    filesize += typeinfo->var_data[0] + (((typeinfo->typeinfo->cElement >> 16) & 0xffff) * 12);
        if (typeinfo->func_data || typeinfo->var_data)
            filesize += 4;
    }
}