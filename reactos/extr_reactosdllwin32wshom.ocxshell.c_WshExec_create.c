#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int ref; TYPE_3__ IWshExec_iface; int /*<<< orphan*/  classinfo; int /*<<< orphan*/  info; } ;
typedef  TYPE_1__ WshExecImpl ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ STARTUPINFOW ;
typedef  TYPE_3__ IWshExec ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_WshExec ; 
 int /*<<< orphan*/  CreateProcessW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WshExecVtbl ; 
 TYPE_1__* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  init_classinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT WshExec_create(BSTR command, IWshExec **ret)
{
    STARTUPINFOW si = {0};
    WshExecImpl *This;

    *ret = NULL;

    This = heap_alloc(sizeof(*This));
    if (!This)
        return E_OUTOFMEMORY;

    This->IWshExec_iface.lpVtbl = &WshExecVtbl;
    This->ref = 1;

    if (!CreateProcessW(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &This->info)) {
        heap_free(This);
        return HRESULT_FROM_WIN32(GetLastError());
    }

    init_classinfo(&CLSID_WshExec, (IUnknown *)&This->IWshExec_iface, &This->classinfo);
    *ret = &This->IWshExec_iface;
    return S_OK;
}