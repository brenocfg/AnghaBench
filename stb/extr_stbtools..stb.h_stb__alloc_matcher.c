#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dfa_result; int /*<<< orphan*/  dfa_mapping; int /*<<< orphan*/  dfa; int /*<<< orphan*/  dfa_start; scalar_t__ does_lex; scalar_t__ match_start; scalar_t__ num_charset; int /*<<< orphan*/  nodes; scalar_t__ start_node; } ;
typedef  TYPE_1__ stb_matcher ;

/* Variables and functions */
 int /*<<< orphan*/  STB__DFA_UNDEF ; 
 int /*<<< orphan*/  stb__add_node (TYPE_1__*) ; 
 int /*<<< orphan*/  stb_arr_malloc (void**,TYPE_1__*) ; 
 scalar_t__ stb_malloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static stb_matcher *stb__alloc_matcher(void)
{
   stb_matcher *matcher = (stb_matcher *) stb_malloc(0,sizeof(*matcher));

   matcher->start_node  = 0;
   stb_arr_malloc((void **) &matcher->nodes, matcher);
   matcher->num_charset = 0;
   matcher->match_start = 0;
   matcher->does_lex    = 0;

   matcher->dfa_start   = STB__DFA_UNDEF;
   stb_arr_malloc((void **) &matcher->dfa, matcher);
   stb_arr_malloc((void **) &matcher->dfa_mapping, matcher);
   stb_arr_malloc((void **) &matcher->dfa_result, matcher);

   stb__add_node(matcher);

   return matcher;
}