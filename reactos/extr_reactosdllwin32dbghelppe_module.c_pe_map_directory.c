#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct module {scalar_t__ type; TYPE_5__** format_info; } ;
struct TYPE_12__ {TYPE_3__* DataDirectory; } ;
struct TYPE_14__ {TYPE_4__ OptionalHeader; } ;
struct TYPE_10__ {TYPE_1__* pe_info; } ;
struct TYPE_13__ {TYPE_2__ u; } ;
struct TYPE_11__ {int /*<<< orphan*/  VirtualAddress; int /*<<< orphan*/  Size; } ;
struct TYPE_9__ {int /*<<< orphan*/  fmap; } ;
typedef  TYPE_6__ IMAGE_NT_HEADERS ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 size_t DFI_PE ; 
 scalar_t__ DMT_PE ; 
 int IMAGE_NUMBEROF_DIRECTORY_ENTRIES ; 
 char const* RtlImageRvaToVa (TYPE_6__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* pe_map_full (int /*<<< orphan*/ *,TYPE_6__**) ; 

const char* pe_map_directory(struct module* module, int dirno, DWORD* size)
{
    IMAGE_NT_HEADERS*   nth;
    void*               mapping;

    if (module->type != DMT_PE || !module->format_info[DFI_PE]) return NULL;
    if (dirno >= IMAGE_NUMBEROF_DIRECTORY_ENTRIES ||
        !(mapping = pe_map_full(&module->format_info[DFI_PE]->u.pe_info->fmap, &nth)))
        return NULL;
    if (size) *size = nth->OptionalHeader.DataDirectory[dirno].Size;
    return RtlImageRvaToVa(nth, mapping,
                           nth->OptionalHeader.DataDirectory[dirno].VirtualAddress, NULL);
}