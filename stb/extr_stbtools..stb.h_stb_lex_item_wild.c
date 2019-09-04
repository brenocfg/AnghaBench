#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ stb_uint16 ;
struct TYPE_7__ {TYPE_1__* nodes; int /*<<< orphan*/  start_node; } ;
typedef  TYPE_2__ stb_matcher ;
struct TYPE_6__ {int goal; } ;

/* Variables and functions */
 int /*<<< orphan*/  stb__lex_reset (TYPE_2__*) ; 
 char* stb__wild_parse (TYPE_2__*,int /*<<< orphan*/ ,char*,scalar_t__*) ; 

int stb_lex_item_wild(stb_matcher *matcher, const char *regex, int result)
{
   char *z;
   stb_uint16 end;

   z = stb__wild_parse(matcher, matcher->start_node, (char*) regex, &end);

   if (z == NULL)
      return 0;

   stb__lex_reset(matcher);

   matcher->nodes[(int) end].goal = result;
   return 1;
}