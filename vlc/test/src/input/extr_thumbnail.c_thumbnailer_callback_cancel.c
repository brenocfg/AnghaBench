#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct test_ctx {int b_done; int /*<<< orphan*/  cond; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  picture_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void thumbnailer_callback_cancel( void* data, picture_t* p_thumbnail )
{
    struct test_ctx* p_ctx = data;
    assert( p_thumbnail == NULL );
    vlc_mutex_lock( &p_ctx->lock );
    p_ctx->b_done = true;
    vlc_mutex_unlock( &p_ctx->lock );
    vlc_cond_signal( &p_ctx->cond );
}