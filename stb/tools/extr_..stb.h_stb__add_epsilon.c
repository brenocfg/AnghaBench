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
struct TYPE_6__ {TYPE_1__* nodes; } ;
typedef  TYPE_2__ stb_matcher ;
struct TYPE_5__ {int /*<<< orphan*/ * eps; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stb_arr_malloc (void**,TYPE_2__*) ; 
 int /*<<< orphan*/  stb_arr_push (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void stb__add_epsilon(stb_matcher *matcher, int from, int to)
{
   assert(from != to);
   if (matcher->nodes[from].eps == NULL)
      stb_arr_malloc((void **) &matcher->nodes[from].eps, matcher);
   stb_arr_push(matcher->nodes[from].eps, to);
}