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
struct async_header {void (* proc ) (struct async_header*) ;int /*<<< orphan*/ * sink; void* wait; void* cancel; } ;
typedef  int /*<<< orphan*/  IWbemObjectSink ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (void*) ; 
 void* CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IWbemObjectSink_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL init_async( struct async_header *async, IWbemObjectSink *sink,
                        void (*proc)(struct async_header *) )
{
    if (!(async->wait = CreateEventW( NULL, FALSE, FALSE, NULL ))) return FALSE;
    if (!(async->cancel = CreateEventW( NULL, FALSE, FALSE, NULL )))
    {
        CloseHandle( async->wait );
        return FALSE;
    }
    async->proc = proc;
    async->sink = sink;
    IWbemObjectSink_AddRef( sink );
    return TRUE;
}