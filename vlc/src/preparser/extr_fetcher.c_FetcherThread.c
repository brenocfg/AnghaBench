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
struct fetcher_thread {int /*<<< orphan*/  worker; int /*<<< orphan*/  active; int /*<<< orphan*/  req; int /*<<< orphan*/  fetcher; int /*<<< orphan*/  (* pf_worker ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  interrupt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  background_worker_RequestProbe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_interrupt_set (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void* FetcherThread( void* handle )
{
    struct fetcher_thread* th = handle;
    vlc_interrupt_set( &th->interrupt );

    th->pf_worker( th->fetcher, th->req );

    atomic_store( &th->active, false );
    background_worker_RequestProbe( th->worker );
    return NULL;
}