#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  user_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * input_thread; int /*<<< orphan*/  lock; TYPE_1__ params; } ;
typedef  TYPE_2__ vlc_thumbnailer_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (void*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_Stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void thumbnailer_request_Stop( void* owner, void* handle )
{
    VLC_UNUSED(owner);

    vlc_thumbnailer_request_t *request = handle;
    vlc_mutex_lock( &request->lock );
    /*
     * If the callback hasn't been invoked yet, we assume a timeout and
     * signal it back to the user
     */
    if ( request->params.cb != NULL )
    {
        request->params.cb( request->params.user_data, NULL );
        request->params.cb = NULL;
    }
    vlc_mutex_unlock( &request->lock );
    assert( request->input_thread != NULL );
    input_Stop( request->input_thread );
}