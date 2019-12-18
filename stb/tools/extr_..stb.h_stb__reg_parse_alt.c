#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int stb_uint16 ;
typedef  int /*<<< orphan*/  stb_matcher ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stb__add_epsilon (int /*<<< orphan*/ *,int,int) ; 
 int stb__add_node (int /*<<< orphan*/ *) ; 
 char* stb__reg_parse (int /*<<< orphan*/ *,int,char*,int*) ; 

__attribute__((used)) static char *stb__reg_parse_alt(stb_matcher *matcher, int start, char *regex, stb_uint16 *end)
{
   stb_uint16 last_end = start;
   stb_uint16 main_end;

   int head, tail;

   head = stb__add_node(matcher);
   stb__add_epsilon(matcher, start, head);

   regex = stb__reg_parse(matcher, head, regex, &last_end);
   if (regex == NULL) return NULL;
   if (*regex == 0 || *regex == ')') {
      *end = last_end;
      return regex;
   }

   main_end = last_end;
   tail = stb__add_node(matcher);

   stb__add_epsilon(matcher, last_end, tail);

   // start alternatives from the same starting node; use epsilon
   // transitions to combine their endings
   while(*regex && *regex != ')') {
      assert(*regex == '|');
      head = stb__add_node(matcher);
      stb__add_epsilon(matcher, start, head);
      regex = stb__reg_parse(matcher, head, regex+1, &last_end);
      if (regex == NULL)
         return NULL;
      stb__add_epsilon(matcher, last_end, tail);
   }

   *end = tail;
   return regex;
}