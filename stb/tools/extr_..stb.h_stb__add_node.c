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
struct TYPE_5__ {scalar_t__ out; scalar_t__ goal; scalar_t__ eps; scalar_t__ active; } ;
typedef  TYPE_1__ stb_nfa_node ;
struct TYPE_6__ {int /*<<< orphan*/  nodes; } ;
typedef  TYPE_2__ stb_matcher ;

/* Variables and functions */
 int stb_arr_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb_arr_push (int /*<<< orphan*/ ,TYPE_1__) ; 

__attribute__((used)) static int stb__add_node(stb_matcher *matcher)
{
   stb_nfa_node z;
   z.active = 0;
   z.eps    = 0;
   z.goal   = 0;
   z.out    = 0;
   stb_arr_push(matcher->nodes, z);
   return stb_arr_len(matcher->nodes)-1;
}