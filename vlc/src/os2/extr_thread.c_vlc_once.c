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
struct TYPE_3__ {int done; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ vlc_once_t ;

/* Variables and functions */
 int /*<<< orphan*/  __atomic_xchg (unsigned int*,int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void vlc_once(vlc_once_t *once, void (*cb)(void))
{
    unsigned done;

    /* load once->done */
    __atomic_xchg( &done, once->done );

    /* not initialized ? */
    if( done == 0 )
    {
        vlc_mutex_lock( &once->mutex );

        /* load once->done */
        __atomic_xchg( &done, once->done );

        /* still not initialized ? */
        if( done == 0 )
        {
            cb();

            /* set once->done to 1 */
            __atomic_xchg( &once->done, 1 );
        }

        vlc_mutex_unlock( &once->mutex );
    }
}