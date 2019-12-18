#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct input_preparser_req_t {scalar_t__ cbs; } ;
struct TYPE_11__ {int /*<<< orphan*/  worker; int /*<<< orphan*/  deactivated; } ;
typedef  TYPE_1__ input_preparser_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* on_preparse_ended ) (TYPE_3__*,int /*<<< orphan*/ ,void*) ;} ;
typedef  TYPE_2__ input_preparser_callbacks_t ;
struct TYPE_13__ {int i_type; int b_net; int b_preparse_interact; int /*<<< orphan*/  lock; } ;
typedef  TYPE_3__ input_item_t ;
typedef  int input_item_meta_request_option_t ;
typedef  enum input_item_type_e { ____Placeholder_input_item_type_e } input_item_type_e ;

/* Variables and functions */
 int /*<<< orphan*/  ITEM_PREPARSE_FAILED ; 
 int /*<<< orphan*/  ITEM_PREPARSE_SKIPPED ; 
#define  ITEM_TYPE_DIRECTORY 131 
#define  ITEM_TYPE_FILE 130 
#define  ITEM_TYPE_NODE 129 
#define  ITEM_TYPE_PLAYLIST 128 
 int META_REQUEST_OPTION_DO_INTERACT ; 
 int META_REQUEST_OPTION_SCOPE_NETWORK ; 
 struct input_preparser_req_t* ReqCreate (TYPE_3__*,int,TYPE_2__ const*,void*) ; 
 int /*<<< orphan*/  ReqRelease (struct input_preparser_req_t*) ; 
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 scalar_t__ background_worker_Push (int /*<<< orphan*/ ,struct input_preparser_req_t*,void*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void input_preparser_Push( input_preparser_t *preparser,
    input_item_t *item, input_item_meta_request_option_t i_options,
    const input_preparser_callbacks_t *cbs, void *cbs_userdata,
    int timeout, void *id )
{
    if( atomic_load( &preparser->deactivated ) )
        return;

    vlc_mutex_lock( &item->lock );
    enum input_item_type_e i_type = item->i_type;
    int b_net = item->b_net;
    if( i_options & META_REQUEST_OPTION_DO_INTERACT )
        item->b_preparse_interact = true;
    vlc_mutex_unlock( &item->lock );

    switch( i_type )
    {
        case ITEM_TYPE_NODE:
        case ITEM_TYPE_FILE:
        case ITEM_TYPE_DIRECTORY:
        case ITEM_TYPE_PLAYLIST:
            if( !b_net || i_options & META_REQUEST_OPTION_SCOPE_NETWORK )
                break;
            /* fallthrough */
        default:
            if (cbs && cbs->on_preparse_ended)
                cbs->on_preparse_ended(item, ITEM_PREPARSE_SKIPPED, cbs_userdata);
            return;
    }

    struct input_preparser_req_t *req = ReqCreate(item, i_options,
                                                  cbs, cbs_userdata);

    if (background_worker_Push(preparser->worker, req, id, timeout))
        if (req->cbs && cbs->on_preparse_ended)
            cbs->on_preparse_ended(item, ITEM_PREPARSE_FAILED, cbs_userdata);

    ReqRelease(req);
}