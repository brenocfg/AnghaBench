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
struct TYPE_4__ {int step; int minval; int maxval; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ stb_search ;

/* Variables and functions */
 int /*<<< orphan*/  STB_probe_open_largest ; 
 int /*<<< orphan*/  STB_probe_open_smallest ; 
 int /*<<< orphan*/  stb_probe_guess (TYPE_1__*,int*) ; 

int stb_search_open(stb_search *s, int minv, int find_smallest)
{
   int r;
   s->step   = 4;
   s->minval = minv;
   s->maxval = minv+s->step;
   s->mode = find_smallest ? STB_probe_open_smallest : STB_probe_open_largest;
   stb_probe_guess(s, &r);
   return r;
}