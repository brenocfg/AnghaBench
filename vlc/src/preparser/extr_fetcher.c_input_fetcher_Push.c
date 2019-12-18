#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fetcher_request {int options; int /*<<< orphan*/  rc; void* userdata; int /*<<< orphan*/  const* cbs; int /*<<< orphan*/ * item; } ;
struct background_worker {int dummy; } ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  int input_item_meta_request_option_t ;
struct TYPE_3__ {struct background_worker* network; struct background_worker* local; } ;
typedef  TYPE_1__ input_fetcher_t ;
typedef  int /*<<< orphan*/  input_fetcher_callbacks_t ;

/* Variables and functions */
 int META_REQUEST_OPTION_FETCH_ANY ; 
 int META_REQUEST_OPTION_FETCH_LOCAL ; 
 int /*<<< orphan*/  NotifyArtFetchEnded (struct fetcher_request*,int) ; 
 int /*<<< orphan*/  RequestRelease (struct fetcher_request*) ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ background_worker_Push (struct background_worker*,struct fetcher_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_Hold (int /*<<< orphan*/ *) ; 
 struct fetcher_request* malloc (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_atomic_rc_init (int /*<<< orphan*/ *) ; 

int input_fetcher_Push( input_fetcher_t* fetcher, input_item_t* item,
    input_item_meta_request_option_t options,
    const input_fetcher_callbacks_t *cbs, void *cbs_userdata )
{
    assert(options & META_REQUEST_OPTION_FETCH_ANY);
    struct fetcher_request* req = malloc( sizeof *req );

    if( unlikely( !req ) )
        return VLC_ENOMEM;

    req->item = item;
    req->options = options;
    req->cbs = cbs;
    req->userdata = cbs_userdata;

    vlc_atomic_rc_init( &req->rc );
    input_item_Hold( item );

    struct background_worker* worker =
        options & META_REQUEST_OPTION_FETCH_LOCAL ? fetcher->local : fetcher->network;
    if( background_worker_Push( worker, req, NULL, 0 ) )
        NotifyArtFetchEnded(req, false);

    RequestRelease( req );
    return VLC_SUCCESS;
}