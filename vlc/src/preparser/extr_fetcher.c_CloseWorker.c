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
struct fetcher_thread {int /*<<< orphan*/  interrupt; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (void*) ; 
 int /*<<< orphan*/  free (struct fetcher_thread*) ; 
 int /*<<< orphan*/  vlc_interrupt_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CloseWorker( void* fetcher_, void* th_ )
{
    struct fetcher_thread* th = th_;
    VLC_UNUSED( fetcher_ );

    vlc_interrupt_kill( &th->interrupt );
    vlc_join( th->thread, NULL );
    vlc_interrupt_deinit( &th->interrupt );
    free( th );
}