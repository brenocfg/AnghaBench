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
struct TYPE_4__ {int /*<<< orphan*/  does_lex; } ;
typedef  TYPE_1__ stb_matcher ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int stb__matcher_dfa (TYPE_1__*,char*,int*) ; 

int stb_lex(stb_matcher *m, char *str, int *len)
{
   assert(m->does_lex);
   return stb__matcher_dfa(m, str, len);
}