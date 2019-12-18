#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  user_data; } ;
struct TYPE_8__ {int done; TYPE_3__* thumbnailer; int /*<<< orphan*/  lock; TYPE_2__ params; int /*<<< orphan*/  input_thread; } ;
typedef  TYPE_4__ vlc_thumbnailer_request_t ;
struct TYPE_5__ {scalar_t__ value; } ;
struct vlc_input_event {scalar_t__ type; int /*<<< orphan*/ * thumbnail; TYPE_1__ state; } ;
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_7__ {int /*<<< orphan*/  worker; } ;

/* Variables and functions */
 scalar_t__ END_S ; 
 scalar_t__ ERROR_S ; 
 scalar_t__ INPUT_EVENT_STATE ; 
 scalar_t__ INPUT_EVENT_THUMBNAIL_READY ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  background_worker_RequestProbe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_Stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
on_thumbnailer_input_event( input_thread_t *input,
                            const struct vlc_input_event *event, void *userdata )
{
    VLC_UNUSED(input);
    if ( event->type != INPUT_EVENT_THUMBNAIL_READY &&
         ( event->type != INPUT_EVENT_STATE || ( event->state.value != ERROR_S &&
                                                 event->state.value != END_S ) ) )
         return;

    vlc_thumbnailer_request_t* request = userdata;
    picture_t *pic = NULL;

    if ( event->type == INPUT_EVENT_THUMBNAIL_READY )
    {
        /*
         * Stop the input thread ASAP, delegate its release to
         * thumbnailer_request_Release
         */
        input_Stop( request->input_thread );
        pic = event->thumbnail;
    }
    vlc_mutex_lock( &request->lock );
    request->done = true;
    /*
     * If the request has not been cancelled, we can invoke the completion
     * callback.
     */
    if ( request->params.cb )
    {
        request->params.cb( request->params.user_data, pic );
        request->params.cb = NULL;
    }
    vlc_mutex_unlock( &request->lock );
    background_worker_RequestProbe( request->thumbnailer->worker );
}