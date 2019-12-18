#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mode; scalar_t__ guess; scalar_t__ minval; scalar_t__ maxval; scalar_t__ step; } ;
typedef  TYPE_1__ stb_search ;

/* Variables and functions */
#define  STB_probe_binary_largest 131 
#define  STB_probe_binary_smallest 130 
#define  STB_probe_open_largest 129 
#define  STB_probe_open_smallest 128 
 int stb_probe_guess (TYPE_1__*,int*) ; 

int stb_probe(stb_search *s, int compare, int *result)
{
   switch(s->mode) {
      case STB_probe_open_smallest:
      case STB_probe_open_largest: {
         if (compare <= 0) {
            // then it lies within minval & maxval
            if (s->mode == STB_probe_open_smallest)
               s->mode = STB_probe_binary_smallest;
            else
               s->mode = STB_probe_binary_largest;
         } else {
            // otherwise, we need to probe larger
            s->minval  = s->maxval + 1;
            s->maxval  = s->minval + s->step;
            s->step   += s->step;
         }
         break;
      }
      case STB_probe_binary_smallest: {
         // if compare < 0, then s->minval <= a <  p
         // if compare = 0, then s->minval <= a <= p
         // if compare > 0, then         p <  a <= s->maxval
         if (compare <= 0)
            s->maxval = s->guess;
         else
            s->minval = s->guess+1;
         break;
      }
      case STB_probe_binary_largest: {
         // if compare < 0, then s->minval <= a < p
         // if compare = 0, then         p <= a <= s->maxval
         // if compare > 0, then         p <  a <= s->maxval
         if (compare < 0)
            s->maxval = s->guess-1;
         else
            s->minval = s->guess;
         break;
      }
   }
   return stb_probe_guess(s, result);
}