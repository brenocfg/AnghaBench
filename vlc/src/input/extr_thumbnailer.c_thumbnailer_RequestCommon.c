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
struct TYPE_11__ {int /*<<< orphan*/  worker; } ;
typedef  TYPE_1__ vlc_thumbnailer_t ;
struct TYPE_13__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  input_item; } ;
struct TYPE_12__ {int done; int /*<<< orphan*/  lock; TYPE_3__ params; int /*<<< orphan*/ * input_thread; TYPE_1__* thumbnailer; } ;
typedef  TYPE_2__ vlc_thumbnailer_request_t ;
typedef  TYPE_3__ vlc_thumbnailer_params_t ;

/* Variables and functions */
 int MS_FROM_VLC_TICK (int /*<<< orphan*/ ) ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 scalar_t__ background_worker_Push (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  input_item_Hold (int /*<<< orphan*/ ) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  thumbnailer_request_Release (TYPE_2__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vlc_thumbnailer_request_t*
thumbnailer_RequestCommon( vlc_thumbnailer_t* thumbnailer,
                           const vlc_thumbnailer_params_t* params )
{
    vlc_thumbnailer_request_t *request = malloc( sizeof( *request ) );
    if ( unlikely( request == NULL ) )
        return NULL;
    request->thumbnailer = thumbnailer;
    request->input_thread = NULL;
    request->params = *(vlc_thumbnailer_params_t*)params;
    request->done = false;
    input_item_Hold( request->params.input_item );
    vlc_mutex_init( &request->lock );

    int timeout = params->timeout == VLC_TICK_INVALID ?
                0 : MS_FROM_VLC_TICK( params->timeout );
    if ( background_worker_Push( thumbnailer->worker, request, request,
                                  timeout ) != VLC_SUCCESS )
    {
        thumbnailer_request_Release( request );
        return NULL;
    }
    return request;
}