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
typedef  scalar_t__ uval ;
struct TYPE_3__ {int length; scalar_t__* input; scalar_t__ dont_care; } ;
typedef  TYPE_1__ table ;

/* Variables and functions */

int strip_table(table *t, int exceptions)
{
   uval terminal_value;
   int p = t->length-1;
   while (t->input[p] == t->dont_care)
      --p;
   terminal_value = t->input[p];

   while (p >= 0x10000) {
      if (t->input[p] != terminal_value && t->input[p] != t->dont_care) {
         if (exceptions)
            --exceptions;
         else
            break;
      }
      --p;
   }
   return p+1; // p is a character we must output
}