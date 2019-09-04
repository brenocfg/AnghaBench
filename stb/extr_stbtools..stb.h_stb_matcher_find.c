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
struct TYPE_4__ {scalar_t__ does_lex; } ;
typedef  TYPE_1__ stb_matcher ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int stb__matcher_dfa (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 

int stb_matcher_find(stb_matcher *m, char *str)
{
   assert(m->does_lex == 0);
   return stb__matcher_dfa(m, str, NULL);
}