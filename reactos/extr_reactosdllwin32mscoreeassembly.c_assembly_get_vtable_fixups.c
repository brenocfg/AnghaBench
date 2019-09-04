#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VTableFixup ;
typedef  int ULONG ;
struct TYPE_6__ {TYPE_1__* corhdr; } ;
struct TYPE_5__ {int /*<<< orphan*/  VTableFixups; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  TYPE_2__ ASSEMBLY ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int assembly_datadir_get_data (TYPE_2__*,int /*<<< orphan*/ *,void**) ; 

HRESULT assembly_get_vtable_fixups(ASSEMBLY *assembly, VTableFixup **fixups, DWORD *count)
{
    ULONG size;

    size = assembly_datadir_get_data(assembly, &assembly->corhdr->VTableFixups, (void**)fixups);
    *count = size / sizeof(VTableFixup);

    return S_OK;
}