#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int ref; int nb_xtemplates; TYPE_3__ IDirectXFile_iface; TYPE_2__* xtemplates; } ;
struct TYPE_9__ {int nb_members; TYPE_1__* members; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int nb_dims; int* dim_value; int /*<<< orphan*/ * dim_fixed; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__* LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_4__ IDirectXFileImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DXFILEERR_BADALLOC ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirectXFile_Vtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TOKEN_DWORD ; 
 int /*<<< orphan*/  TOKEN_FLOAT ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

HRESULT IDirectXFileImpl_Create(IUnknown* pUnkOuter, LPVOID* ppObj)
{
    IDirectXFileImpl* object;

    TRACE("(%p,%p)\n", pUnkOuter, ppObj);

    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDirectXFileImpl));
    if (!object)
        return DXFILEERR_BADALLOC;

    object->IDirectXFile_iface.lpVtbl = &IDirectXFile_Vtbl;
    object->ref = 1;

    /* Reserve first template to handle the case sensitive legacy type indexColor */
    object->nb_xtemplates = 1;
    strcpy(object->xtemplates[0].name, "indexColor");
    object->xtemplates[0].nb_members = 2;
    object->xtemplates[0].members[0].type = TOKEN_DWORD;
    object->xtemplates[0].members[0].nb_dims = 0;
    object->xtemplates[0].members[1].type = TOKEN_FLOAT;
    object->xtemplates[0].members[1].nb_dims = 1;
    object->xtemplates[0].members[1].dim_fixed[0] = TRUE;
    object->xtemplates[0].members[1].dim_value[0] = 4;

    *ppObj = &object->IDirectXFile_iface;

    return S_OK;
}