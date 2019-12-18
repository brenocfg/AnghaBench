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
struct TYPE_8__ {int /*<<< orphan*/  worker; } ;
typedef  TYPE_2__ vlc_thumbnailer_t ;
struct TYPE_7__ {int /*<<< orphan*/ * cb; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; TYPE_1__ params; } ;
typedef  TYPE_3__ vlc_thumbnailer_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  background_worker_Cancel (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void vlc_thumbnailer_Cancel( vlc_thumbnailer_t* thumbnailer,
                             vlc_thumbnailer_request_t* req )
{
    vlc_mutex_lock( &req->lock );
    /* Ensure we won't invoke the callback if the input was running. */
    req->params.cb = NULL;
    vlc_mutex_unlock( &req->lock );
    background_worker_Cancel( thumbnailer->worker, req );
}