#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stb_uint16 ;
struct TYPE_8__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ stb_nfa_edge ;
struct TYPE_9__ {TYPE_1__* nodes; } ;
typedef  TYPE_3__ stb_matcher ;
typedef  int /*<<< orphan*/  stb_int16 ;
struct TYPE_7__ {int /*<<< orphan*/ * out; } ;

/* Variables and functions */
 int /*<<< orphan*/  stb_arr_malloc (void**,TYPE_3__*) ; 
 int /*<<< orphan*/  stb_arr_push (int /*<<< orphan*/ *,TYPE_2__) ; 

__attribute__((used)) static void stb__add_edge(stb_matcher *matcher, int from, int to, int type)
{
    stb_nfa_edge z = { (stb_int16)type, (stb_uint16)to };
   if (matcher->nodes[from].out == NULL)
      stb_arr_malloc((void **) &matcher->nodes[from].out, matcher);
   stb_arr_push(matcher->nodes[from].out, z);
}