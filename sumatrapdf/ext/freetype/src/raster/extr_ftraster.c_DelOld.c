#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* link; } ;
typedef  TYPE_1__** PProfileList ;
typedef  TYPE_1__* PProfile ;

/* Variables and functions */

__attribute__((used)) static void
  DelOld( PProfileList  list,
          PProfile      profile )
  {
    PProfile  *old, current;


    old     = list;
    current = *old;

    while ( current )
    {
      if ( current == profile )
      {
        *old = current->link;
        return;
      }

      old     = &current->link;
      current = *old;
    }

    /* we should never get there, unless the profile was not part of */
    /* the list.                                                     */
  }