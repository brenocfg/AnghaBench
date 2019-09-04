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
struct TYPE_3__ {int notify_mask; int /*<<< orphan*/  context; int /*<<< orphan*/  handle; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ object_header_t ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void send_callback( object_header_t *hdr, DWORD status, LPVOID info, DWORD buflen )
{
    if (hdr->callback && (hdr->notify_mask & status))
    {
        TRACE("%p, 0x%08x, %p, %u\n", hdr, status, info, buflen);
        hdr->callback( hdr->handle, hdr->context, status, info, buflen );
        TRACE("returning from 0x%08x callback\n", status);
    }
}