#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int preparse_status; TYPE_4__* req; int /*<<< orphan*/  parser; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ input_preparser_task_t ;
struct TYPE_11__ {scalar_t__ fetcher; } ;
typedef  TYPE_3__ input_preparser_t ;
struct TYPE_12__ {int options; int /*<<< orphan*/  userdata; int /*<<< orphan*/ * item; TYPE_1__* cbs; } ;
typedef  TYPE_4__ input_preparser_req_t ;
typedef  int /*<<< orphan*/  input_item_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* on_preparse_ended ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ITEM_PREPARSE_DONE ; 
 int ITEM_PREPARSE_FAILED ; 
 int ITEM_PREPARSE_TIMEOUT ; 
 int META_REQUEST_OPTION_FETCH_ANY ; 
 int /*<<< orphan*/  ReqHold (TYPE_4__*) ; 
 int /*<<< orphan*/  ReqRelease (TYPE_4__*) ; 
#define  VLC_ETIMEOUT 129 
#define  VLC_SUCCESS 128 
 int atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  input_fetcher_Push (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  input_fetcher_callbacks ; 
 int /*<<< orphan*/  input_item_SetPreparsed (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  input_item_parser_id_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PreparserCloseInput( void* preparser_, void* task_ )
{
    input_preparser_task_t* task = task_;
    input_preparser_req_t *req = task->req;

    input_preparser_t* preparser = preparser_;
    input_item_t* item = req->item;

    int status;
    switch( atomic_load( &task->state ) )
    {
        case VLC_SUCCESS:
            status = ITEM_PREPARSE_DONE;
            break;
        case VLC_ETIMEOUT:
            status = ITEM_PREPARSE_TIMEOUT;
            break;
        default:
            status = ITEM_PREPARSE_FAILED;
            break;
    }

    input_item_parser_id_Release( task->parser );

    if( preparser->fetcher && (req->options & META_REQUEST_OPTION_FETCH_ANY) )
    {
        task->preparse_status = status;
        ReqHold(task->req);
        if (!input_fetcher_Push(preparser->fetcher, item,
                                req->options & META_REQUEST_OPTION_FETCH_ANY,
                                &input_fetcher_callbacks, task))
        {
            return;
        }
        ReqRelease(task->req);
    }

    free(task);

    input_item_SetPreparsed( item, true );
    if (req->cbs && req->cbs->on_preparse_ended)
        req->cbs->on_preparse_ended(req->item, status, req->userdata);
}