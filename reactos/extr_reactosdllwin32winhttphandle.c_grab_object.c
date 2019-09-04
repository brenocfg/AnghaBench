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
typedef  int /*<<< orphan*/  object_header_t ;
typedef  int ULONG_PTR ;
typedef  int /*<<< orphan*/  HINTERNET ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * addref_object (scalar_t__) ; 
 int /*<<< orphan*/  handle_cs ; 
 scalar_t__* handles ; 
 int max_handles ; 

object_header_t *grab_object( HINTERNET hinternet )
{
    object_header_t *hdr = NULL;
    ULONG_PTR handle = (ULONG_PTR)hinternet;

    EnterCriticalSection( &handle_cs );

    if ((handle > 0) && (handle <= max_handles) && handles[handle - 1])
        hdr = addref_object( handles[handle - 1] );

    LeaveCriticalSection( &handle_cs );

    TRACE("handle 0x%lx -> %p\n", handle, hdr);
    return hdr;
}