#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int ref; int /*<<< orphan*/ * callback; int /*<<< orphan*/  file_name; TYPE_2__ IServiceProvider_iface; TYPE_1__ IBindStatusCallback_iface; } ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  IBindStatusCallback ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ DownloadBSC ;

/* Variables and functions */
 int /*<<< orphan*/  BindStatusCallbackVtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IBindStatusCallback_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ServiceProviderVtbl ; 
 TYPE_3__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_3__*) ; 
 int /*<<< orphan*/  heap_strdupW (scalar_t__) ; 

__attribute__((used)) static HRESULT DownloadBSC_Create(IBindStatusCallback *callback, LPCWSTR file_name, DownloadBSC **ret_callback)
{
    DownloadBSC *ret;

    ret = heap_alloc_zero(sizeof(*ret));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->IBindStatusCallback_iface.lpVtbl = &BindStatusCallbackVtbl;
    ret->IServiceProvider_iface.lpVtbl = &ServiceProviderVtbl;
    ret->ref = 1;

    if(file_name) {
        ret->file_name = heap_strdupW(file_name);
        if(!ret->file_name) {
            heap_free(ret);
            return E_OUTOFMEMORY;
        }
    }

    if(callback)
        IBindStatusCallback_AddRef(callback);
    ret->callback = callback;

    *ret_callback = ret;
    return S_OK;
}