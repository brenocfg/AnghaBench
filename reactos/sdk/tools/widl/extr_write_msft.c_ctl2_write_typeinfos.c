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
struct TYPE_7__ {int* func_data; int* var_data; int* func_indices; int* var_indices; int* func_names; int* var_names; int* func_offsets; int* var_offsets; TYPE_1__* typeinfo; struct TYPE_7__* next_typeinfo; } ;
typedef  TYPE_3__ msft_typeinfo_t ;
struct TYPE_5__ {int cElement; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_data (int*,int) ; 

__attribute__((used)) static void ctl2_write_typeinfos(msft_typelib_t *typelib)
{
    msft_typeinfo_t *typeinfo;
    int typedata_size;

    for (typeinfo = typelib->typeinfos; typeinfo; typeinfo = typeinfo->next_typeinfo) {
        if (!typeinfo->func_data && !typeinfo->var_data) continue;
        typedata_size = 0;
	if (typeinfo->func_data)
            typedata_size = typeinfo->func_data[0];
	if (typeinfo->var_data)
            typedata_size += typeinfo->var_data[0];
	put_data(&typedata_size, sizeof(int));
        if (typeinfo->func_data)
            put_data(typeinfo->func_data + 1, typeinfo->func_data[0]);
        if (typeinfo->var_data)
            put_data(typeinfo->var_data + 1, typeinfo->var_data[0]);
        if (typeinfo->func_indices)
            put_data(typeinfo->func_indices, (typeinfo->typeinfo->cElement & 0xffff) * 4);
        if (typeinfo->var_indices)
            put_data(typeinfo->var_indices, (typeinfo->typeinfo->cElement >> 16) * 4);
        if (typeinfo->func_names)
            put_data(typeinfo->func_names,   (typeinfo->typeinfo->cElement & 0xffff) * 4);
        if (typeinfo->var_names)
            put_data(typeinfo->var_names,   (typeinfo->typeinfo->cElement >> 16) * 4);
        if (typeinfo->func_offsets)
            put_data(typeinfo->func_offsets, (typeinfo->typeinfo->cElement & 0xffff) * 4);
        if (typeinfo->var_offsets) {
            int add = 0, i, offset;
            if(typeinfo->func_data)
                add = typeinfo->func_data[0];
            for(i = 0; i < (typeinfo->typeinfo->cElement >> 16); i++) {
                offset = typeinfo->var_offsets[i];
                offset += add;
                put_data(&offset, 4);
            }
        }
    }
}