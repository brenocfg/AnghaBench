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
struct TYPE_3__ {int /*<<< orphan*/  dfa_start; int /*<<< orphan*/  dfa_result; int /*<<< orphan*/  dfa_mapping; int /*<<< orphan*/  dfa; } ;
typedef  TYPE_1__ stb_matcher ;

/* Variables and functions */
 int /*<<< orphan*/  STB__DFA_UNDEF ; 
 int /*<<< orphan*/  stb_arr_setlen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stb__lex_reset(stb_matcher *matcher)
{
   // flush cached dfa data
   stb_arr_setlen(matcher->dfa, 0);
   stb_arr_setlen(matcher->dfa_mapping, 0);
   stb_arr_setlen(matcher->dfa_result, 0);
   matcher->dfa_start = STB__DFA_UNDEF;
}