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
typedef  int ULONG_PTR ;
typedef  int /*<<< orphan*/  PUSER_HANDLE_TABLE ;
typedef  int /*<<< orphan*/  PUSER_HANDLE_ENTRY ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ entry_to_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_to_entry (int /*<<< orphan*/ ,scalar_t__) ; 

HANDLE get_user_full_handle(PUSER_HANDLE_TABLE ht,  HANDLE handle )
{
   PUSER_HANDLE_ENTRY entry;

   if ((ULONG_PTR)handle >> 16)
      return handle;
   if (!(entry = handle_to_entry(ht, handle )))
      return handle;
   return entry_to_handle( ht, entry );
}