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

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeProxyInfo (scalar_t__) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WININET_cs ; 
 scalar_t__ global_proxy ; 
 int /*<<< orphan*/  heap_free (scalar_t__) ; 

__attribute__((used)) static void free_global_proxy( void )
{
    EnterCriticalSection( &WININET_cs );
    if (global_proxy)
    {
        FreeProxyInfo( global_proxy );
        heap_free( global_proxy );
    }
    LeaveCriticalSection( &WININET_cs );
}