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
struct TYPE_5__ {scalar_t__ X; struct TYPE_5__* link; } ;
typedef  TYPE_1__** PProfileList ;
typedef  TYPE_1__* PProfile ;
typedef  scalar_t__ Long ;

/* Variables and functions */

__attribute__((used)) static void
  InsNew( PProfileList  list,
          PProfile      profile )
  {
    PProfile  *old, current;
    Long       x;


    old     = list;
    current = *old;
    x       = profile->X;

    while ( current )
    {
      if ( x < current->X )
        break;
      old     = &current->link;
      current = *old;
    }

    profile->link = current;
    *old          = profile;
  }