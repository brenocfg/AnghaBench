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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  USER_HANDLE_ENTRY ;
typedef  int ULONG ;
struct TYPE_3__ {int allocated_handles; scalar_t__ nb_handles; int /*<<< orphan*/  handles; int /*<<< orphan*/ * freelist; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PUSER_HANDLE_TABLE ;

/* Variables and functions */

VOID UserInitHandleTable(PUSER_HANDLE_TABLE ht, PVOID mem, ULONG bytes)
{
   ht->freelist = NULL;
   ht->handles = mem;

   ht->nb_handles = 0;
   ht->allocated_handles = bytes / sizeof(USER_HANDLE_ENTRY);
}