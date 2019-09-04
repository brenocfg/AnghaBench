#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned short generation; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int nb_handles; TYPE_2__* handles; } ;
typedef  TYPE_1__* PUSER_HANDLE_TABLE ;
typedef  TYPE_2__* PUSER_HANDLE_ENTRY ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int FIRST_USER_HANDLE ; 
 unsigned short HIWORD (int /*<<< orphan*/ ) ; 
 int LOWORD (int /*<<< orphan*/ ) ; 

PUSER_HANDLE_ENTRY handle_to_entry(PUSER_HANDLE_TABLE ht, HANDLE handle )
{
   unsigned short generation;
   int index = (LOWORD(handle) - FIRST_USER_HANDLE) >> 1;
   if (index < 0 || index >= ht->nb_handles)
      return NULL;
   if (!ht->handles[index].type)
      return NULL;
   generation = HIWORD(handle);
   if (generation == ht->handles[index].generation || !generation || generation == 0xffff)
      return &ht->handles[index];
   return NULL;
}