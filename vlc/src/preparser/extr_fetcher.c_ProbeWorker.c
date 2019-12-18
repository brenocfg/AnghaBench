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
struct fetcher_thread {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (void*) ; 
 int /*<<< orphan*/  atomic_load (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ProbeWorker( void* fetcher_, void* th_ )
{
    return !atomic_load( &((struct fetcher_thread*)th_)->active );
    VLC_UNUSED( fetcher_ );
}