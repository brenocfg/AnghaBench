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
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct downloadcb {int ref; char* id; char* display; int /*<<< orphan*/  file_name; int /*<<< orphan*/  event_done; int /*<<< orphan*/  dl_previous_kb; int /*<<< orphan*/  dl_size; TYPE_3__* engine; int /*<<< orphan*/  hr; TYPE_1__ IBindStatusCallback_iface; } ;
struct TYPE_6__ {int /*<<< orphan*/  downloaded_kb; } ;
struct TYPE_7__ {int /*<<< orphan*/  IInstallEngine2_iface; TYPE_2__ thread; } ;
typedef  TYPE_3__ InstallEngine ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BindStatusCallbackVtbl ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IInstallEngine2_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 struct downloadcb* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (struct downloadcb*) ; 
 int /*<<< orphan*/  strAtoW (char*) ; 

__attribute__((used)) static HRESULT downloadcb_create(InstallEngine *engine, HANDLE event, char *file_name, char *id,
                                 char *display, DWORD dl_size, struct downloadcb **callback)
{
    struct downloadcb *cb;

    cb = heap_alloc_zero(sizeof(*cb));
    if (!cb) return E_OUTOFMEMORY;

    cb->IBindStatusCallback_iface.lpVtbl = &BindStatusCallbackVtbl;
    cb->ref = 1;
    cb->hr = E_FAIL;
    cb->id = id;
    cb->display = display;
    cb->engine = engine;
    cb->dl_size = dl_size;
    cb->dl_previous_kb = engine->thread.downloaded_kb;
    cb->event_done = event;
    cb->file_name = strAtoW(file_name);
    if (!cb->file_name)
    {
        heap_free(cb);
        return E_OUTOFMEMORY;
    }

    IInstallEngine2_AddRef(&engine->IInstallEngine2_iface);

    *callback = cb;
    return S_OK;
}