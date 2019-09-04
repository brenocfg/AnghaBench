#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* hostname; int /*<<< orphan*/  connections; int /*<<< orphan*/  entry; scalar_t__ ref; } ;
typedef  TYPE_1__ hostdata_t ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connection_pool_cs ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

void release_host( hostdata_t *host )
{
    LONG ref;

    EnterCriticalSection( &connection_pool_cs );
    if (!(ref = --host->ref)) list_remove( &host->entry );
    LeaveCriticalSection( &connection_pool_cs );
    if (ref) return;

    assert( list_empty( &host->connections ) );
    heap_free( host->hostname );
    heap_free( host );
}