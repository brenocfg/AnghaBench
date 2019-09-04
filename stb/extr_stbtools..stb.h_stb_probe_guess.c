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
struct TYPE_3__ {int mode; int minval; int maxval; int guess; } ;
typedef  TYPE_1__ stb_search ;

/* Variables and functions */
#define  STB_probe_binary_largest 131 
#define  STB_probe_binary_smallest 130 
#define  STB_probe_open_largest 129 
#define  STB_probe_open_smallest 128 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int stb_probe_guess(stb_search *s, int *result)
{
   switch(s->mode) {
      case STB_probe_binary_largest:
         if (s->minval == s->maxval) {
            *result = s->minval;
            return 0;
         }
         assert(s->minval < s->maxval);
         // if a < b, then a < p <= b
         s->guess = s->minval + (((unsigned) s->maxval - s->minval + 1) >> 1);
         break;

      case STB_probe_binary_smallest:
         if (s->minval == s->maxval) {
            *result = s->minval;
            return 0;
         }
         assert(s->minval < s->maxval);
         // if a < b, then a <= p < b
         s->guess = s->minval + (((unsigned) s->maxval - s->minval) >> 1);
         break;
      case STB_probe_open_smallest:
      case STB_probe_open_largest:
         s->guess = s->maxval;  // guess the current maxval
         break;
   }
   *result = s->guess;
   return 1;
}