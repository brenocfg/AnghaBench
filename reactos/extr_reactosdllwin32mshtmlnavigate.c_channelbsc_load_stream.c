#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  IBindStatusCallback_iface; TYPE_5__* window; } ;
struct TYPE_12__ {TYPE_2__ bsc; TYPE_3__* nschannel; } ;
typedef  TYPE_4__ nsChannelBSC ;
struct TYPE_9__ {int /*<<< orphan*/  outer_window; } ;
struct TYPE_13__ {TYPE_1__ base; TYPE_4__* bscallback; } ;
struct TYPE_11__ {int /*<<< orphan*/  content_type; } ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  TYPE_5__ HTMLInnerWindow ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBindStatusCallback_OnStopBinding (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  async_stop_request (TYPE_4__*) ; 
 int /*<<< orphan*/  heap_strdupA (char*) ; 
 int /*<<< orphan*/  read_stream_data (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_current_mon (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

HRESULT channelbsc_load_stream(HTMLInnerWindow *pending_window, IMoniker *mon, IStream *stream)
{
    nsChannelBSC *bscallback = pending_window->bscallback;
    HRESULT hres = S_OK;

    if(!bscallback->nschannel) {
        ERR("NULL nschannel\n");
        return E_FAIL;
    }

    bscallback->nschannel->content_type = heap_strdupA("text/html");
    if(!bscallback->nschannel->content_type)
        return E_OUTOFMEMORY;

    set_current_mon(pending_window->base.outer_window, mon, 0);

    bscallback->bsc.window = pending_window;
    if(stream)
        hres = read_stream_data(bscallback, stream);
    if(SUCCEEDED(hres))
        hres = async_stop_request(bscallback);
    if(FAILED(hres))
        IBindStatusCallback_OnStopBinding(&bscallback->bsc.IBindStatusCallback_iface, hres,
                ERROR_SUCCESS);

    return hres;
}