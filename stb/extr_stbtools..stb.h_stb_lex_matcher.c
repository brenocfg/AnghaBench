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
struct TYPE_4__ {int match_start; int does_lex; } ;
typedef  TYPE_1__ stb_matcher ;

/* Variables and functions */
 TYPE_1__* stb__alloc_matcher () ; 

stb_matcher *stb_lex_matcher(void)
{
   stb_matcher *matcher = stb__alloc_matcher();

   matcher->match_start = 1;
   matcher->does_lex    = 1;

   return matcher;
}