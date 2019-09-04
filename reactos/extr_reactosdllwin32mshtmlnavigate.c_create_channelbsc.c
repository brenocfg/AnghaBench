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
struct TYPE_8__ {int post_data_len; scalar_t__ post_data; int /*<<< orphan*/  headers; } ;
struct TYPE_9__ {TYPE_2__ request_data; int /*<<< orphan*/  IBindStatusCallback_iface; } ;
struct TYPE_7__ {TYPE_3__ bsc; int /*<<< orphan*/  is_doc_channel; } ;
typedef  TYPE_1__ nsChannelBSC ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  scalar_t__ BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BINDF_ASYNCHRONOUS ; 
 int BINDF_ASYNCSTORAGE ; 
 int BINDF_FORMS_SUBMIT ; 
 int BINDF_GETNEWESTVERSION ; 
 int BINDF_HYPERLINK ; 
 int BINDF_PRAGMA_NO_CACHE ; 
 int BINDF_PULLDATA ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ GlobalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IBindStatusCallback_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 TYPE_1__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_strdupW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  init_bscallback (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  nsChannelBSCVtbl ; 
 int /*<<< orphan*/  release_request_data (TYPE_2__*) ; 

HRESULT create_channelbsc(IMoniker *mon, const WCHAR *headers, BYTE *post_data, DWORD post_data_size,
        BOOL is_doc_binding, nsChannelBSC **retval)
{
    nsChannelBSC *ret;
    DWORD bindf;

    ret = heap_alloc_zero(sizeof(*ret));
    if(!ret)
        return E_OUTOFMEMORY;

    bindf = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_PULLDATA;
    if(post_data_size)
        bindf |= BINDF_FORMS_SUBMIT | BINDF_PRAGMA_NO_CACHE | BINDF_HYPERLINK | BINDF_GETNEWESTVERSION;

    init_bscallback(&ret->bsc, &nsChannelBSCVtbl, mon, bindf);
    ret->is_doc_channel = is_doc_binding;

    if(headers) {
        ret->bsc.request_data.headers = heap_strdupW(headers);
        if(!ret->bsc.request_data.headers) {
            IBindStatusCallback_Release(&ret->bsc.IBindStatusCallback_iface);
            return E_OUTOFMEMORY;
        }
    }

    if(post_data) {
        ret->bsc.request_data.post_data = GlobalAlloc(0, post_data_size+1);
        if(!ret->bsc.request_data.post_data) {
            release_request_data(&ret->bsc.request_data);
            IBindStatusCallback_Release(&ret->bsc.IBindStatusCallback_iface);
            return E_OUTOFMEMORY;
        }

        memcpy(ret->bsc.request_data.post_data, post_data, post_data_size);
        ((BYTE*)ret->bsc.request_data.post_data)[post_data_size] = 0;
        ret->bsc.request_data.post_data_len = post_data_size;
    }

    TRACE("created %p\n", ret);
    *retval = ret;
    return S_OK;
}