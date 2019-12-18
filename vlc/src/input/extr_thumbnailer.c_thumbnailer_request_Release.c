#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  input_item; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; TYPE_1__ params; scalar_t__ input_thread; } ;
typedef  TYPE_2__ vlc_thumbnailer_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  input_Close (scalar_t__) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void thumbnailer_request_Release( void* data )
{
    vlc_thumbnailer_request_t* request = data;
    if ( request->input_thread )
        input_Close( request->input_thread );

    input_item_Release( request->params.input_item );
    vlc_mutex_destroy( &request->lock );
    free( request );
}