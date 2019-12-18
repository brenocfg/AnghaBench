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
struct TYPE_3__ {int /*<<< orphan*/  abst_lock; int /*<<< orphan*/  dl_cond; int /*<<< orphan*/  dl_lock; } ;
typedef  TYPE_1__ hds_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cleanup_threading( hds_stream_t *stream )
{
    vlc_mutex_destroy( &stream->dl_lock );
    vlc_cond_destroy( &stream->dl_cond );
    vlc_mutex_destroy( &stream->abst_lock );
}