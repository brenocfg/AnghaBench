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
struct TYPE_5__ {int /*<<< orphan*/  header; scalar_t__ async_notif; void* headers; TYPE_2__* post_data; void* url; } ;
typedef  TYPE_1__ task_doc_navigate_t ;
typedef  scalar_t__ VARIANT_BOOL ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int /*<<< orphan*/  pvData; } ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DocHost ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_2__* SafeArrayCreateVector (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* SysAllocString (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ VARIANT_FALSE ; 
 int /*<<< orphan*/  VT_UI1 ; 
 int /*<<< orphan*/  abort_dochost_tasks (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__) ; 
 int /*<<< orphan*/  doc_navigate_proc ; 
 int /*<<< orphan*/  doc_navigate_task_destr (int /*<<< orphan*/ *) ; 
 TYPE_1__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_before_navigate2 (int /*<<< orphan*/ *,void*,TYPE_2__*,void*,scalar_t__*) ; 
 int /*<<< orphan*/  push_dochost_task (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *),int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT async_doc_navigate(DocHost *This, LPCWSTR url, LPCWSTR headers, PBYTE post_data, ULONG post_data_size,
        BOOL async_notif)
{
    task_doc_navigate_t *task;

    TRACE("%s\n", debugstr_w(url));

    task = heap_alloc_zero(sizeof(*task));
    if(!task)
        return E_OUTOFMEMORY;

    task->url = SysAllocString(url);
    if(!task->url) {
        doc_navigate_task_destr(&task->header);
        return E_OUTOFMEMORY;
    }

    if(headers) {
        task->headers = SysAllocString(headers);
        if(!task->headers) {
            doc_navigate_task_destr(&task->header);
            return E_OUTOFMEMORY;
        }
    }

    if(post_data) {
        task->post_data = SafeArrayCreateVector(VT_UI1, 0, post_data_size);
        if(!task->post_data) {
            doc_navigate_task_destr(&task->header);
            return E_OUTOFMEMORY;
        }

        memcpy(task->post_data->pvData, post_data, post_data_size);
    }

    if(!async_notif) {
        VARIANT_BOOL cancel = VARIANT_FALSE;

        on_before_navigate2(This, task->url, task->post_data, task->headers, &cancel);
        if(cancel) {
            TRACE("Navigation canceled\n");
            doc_navigate_task_destr(&task->header);
            return S_OK;
        }
    }

    task->async_notif = async_notif;
    abort_dochost_tasks(This, doc_navigate_proc);
    push_dochost_task(This, &task->header, doc_navigate_proc, doc_navigate_task_destr, FALSE);
    return S_OK;
}