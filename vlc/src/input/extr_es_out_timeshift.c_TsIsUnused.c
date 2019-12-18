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
struct TYPE_3__ {scalar_t__ rate; scalar_t__ rate_source; int /*<<< orphan*/  lock; int /*<<< orphan*/  p_storage_r; int /*<<< orphan*/  b_paused; } ;
typedef  TYPE_1__ ts_thread_t ;

/* Variables and functions */
 scalar_t__ TsStorageIsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool TsIsUnused( ts_thread_t *p_ts )
{
    bool b_unused;

    vlc_mutex_lock( &p_ts->lock );
    b_unused = !p_ts->b_paused &&
               p_ts->rate == p_ts->rate_source &&
               TsStorageIsEmpty( p_ts->p_storage_r );
    vlc_mutex_unlock( &p_ts->lock );

    return b_unused;
}