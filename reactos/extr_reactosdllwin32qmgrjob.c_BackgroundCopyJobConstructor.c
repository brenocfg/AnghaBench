#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_3__* DebugInfo; } ;
struct TYPE_18__ {int /*<<< orphan*/ * file; int /*<<< orphan*/  code; scalar_t__ context; } ;
struct TYPE_17__ {scalar_t__ FilesTransferred; scalar_t__ FilesTotal; scalar_t__ BytesTransferred; scalar_t__ BytesTotal; } ;
struct TYPE_15__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_19__ {int ref; int notify_flags; int /*<<< orphan*/  jobId; void* done; void* cancel; void* wait; int /*<<< orphan*/  http_options; TYPE_5__ error; int /*<<< orphan*/  callback2; int /*<<< orphan*/ * callback; int /*<<< orphan*/ * description; int /*<<< orphan*/  state; TYPE_4__ jobProgress; int /*<<< orphan*/  files; struct TYPE_19__* displayName; TYPE_9__ cs; int /*<<< orphan*/  type; TYPE_2__ IBackgroundCopyJobHttpOptions_iface; TYPE_1__ IBackgroundCopyJob3_iface; } ;
struct TYPE_16__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  scalar_t__ DWORD_PTR ;
typedef  TYPE_6__ BackgroundCopyJobImpl ;
typedef  int /*<<< orphan*/  BG_JOB_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  BG_JOB_STATE_SUSPENDED ; 
 int BG_NOTIFY_JOB_ERROR ; 
 int BG_NOTIFY_JOB_TRANSFERRED ; 
 int /*<<< orphan*/  BackgroundCopyJob3Vtbl ; 
 int /*<<< orphan*/  CoCreateGuid (int /*<<< orphan*/ *) ; 
 void* CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteCriticalSection (TYPE_9__*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_6__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_9__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,TYPE_6__*,...) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_options_vtbl ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_6__* strdupW (int /*<<< orphan*/ ) ; 

HRESULT BackgroundCopyJobConstructor(LPCWSTR displayName, BG_JOB_TYPE type, GUID *job_id, BackgroundCopyJobImpl **job)
{
    HRESULT hr;
    BackgroundCopyJobImpl *This;

    TRACE("(%s,%d,%p)\n", debugstr_w(displayName), type, job);

    This = HeapAlloc(GetProcessHeap(), 0, sizeof *This);
    if (!This)
        return E_OUTOFMEMORY;

    This->IBackgroundCopyJob3_iface.lpVtbl = &BackgroundCopyJob3Vtbl;
    This->IBackgroundCopyJobHttpOptions_iface.lpVtbl = &http_options_vtbl;
    InitializeCriticalSection(&This->cs);
    This->cs.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": BackgroundCopyJobImpl.cs");

    This->ref = 1;
    This->type = type;

    This->displayName = strdupW(displayName);
    if (!This->displayName)
    {
        This->cs.DebugInfo->Spare[0] = 0;
        DeleteCriticalSection(&This->cs);
        HeapFree(GetProcessHeap(), 0, This);
        return E_OUTOFMEMORY;
    }

    hr = CoCreateGuid(&This->jobId);
    if (FAILED(hr))
    {
        This->cs.DebugInfo->Spare[0] = 0;
        DeleteCriticalSection(&This->cs);
        HeapFree(GetProcessHeap(), 0, This->displayName);
        HeapFree(GetProcessHeap(), 0, This);
        return hr;
    }
    *job_id = This->jobId;

    list_init(&This->files);
    This->jobProgress.BytesTotal = 0;
    This->jobProgress.BytesTransferred = 0;
    This->jobProgress.FilesTotal = 0;
    This->jobProgress.FilesTransferred = 0;

    This->state = BG_JOB_STATE_SUSPENDED;
    This->description = NULL;
    This->notify_flags = BG_NOTIFY_JOB_ERROR | BG_NOTIFY_JOB_TRANSFERRED;
    This->callback = NULL;
    This->callback2 = FALSE;

    This->error.context = 0;
    This->error.code = S_OK;
    This->error.file = NULL;

    memset(&This->http_options, 0, sizeof(This->http_options));

    This->wait   = CreateEventW(NULL, FALSE, FALSE, NULL);
    This->cancel = CreateEventW(NULL, FALSE, FALSE, NULL);
    This->done   = CreateEventW(NULL, FALSE, FALSE, NULL);

    *job = This;

    TRACE("created job %s:%p\n", debugstr_guid(&This->jobId), This);

    return S_OK;
}