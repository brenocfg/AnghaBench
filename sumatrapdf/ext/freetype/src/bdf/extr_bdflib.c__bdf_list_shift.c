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
struct TYPE_3__ {unsigned long used; int /*<<< orphan*/ * field; } ;
typedef  TYPE_1__ _bdf_list_t ;

/* Variables and functions */

__attribute__((used)) static void
  _bdf_list_shift( _bdf_list_t*   list,
                   unsigned long  n )
  {
    unsigned long  i, u;


    if ( list == 0 || list->used == 0 || n == 0 )
      return;

    if ( n >= list->used )
    {
      list->used = 0;
      return;
    }

    for ( u = n, i = 0; u < list->used; i++, u++ )
      list->field[i] = list->field[u];
    list->used -= n;
  }