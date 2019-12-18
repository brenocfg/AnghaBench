#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int debug; } ;

/* Variables and functions */
 int pp_flex_debug ; 
 TYPE_1__ pp_status ; 
 int ppy_debug ; 

void wpp_set_debug( int lex_debug, int parser_debug, int msg_debug )
{
    pp_flex_debug   = lex_debug;
    ppy_debug       = parser_debug;
    pp_status.debug = msg_debug;
}