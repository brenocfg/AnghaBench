#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int done; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vlc_thumbnailer_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (void*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int thumbnailer_request_Probe( void* owner, void* handle )
{
    VLC_UNUSED(owner);
    vlc_thumbnailer_request_t *request = handle;
    vlc_mutex_lock( &request->lock );
    int res = request->done;
    vlc_mutex_unlock( &request->lock );
    return res;
}