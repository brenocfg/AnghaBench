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
struct TYPE_3__ {char* input_name; int /*<<< orphan*/  near_text; int /*<<< orphan*/  line_number; } ;
typedef  TYPE_1__ loc_info_t ;

/* Variables and functions */
 char* input_name ; 
 int /*<<< orphan*/  line_number ; 
 int /*<<< orphan*/  parser_text ; 

void init_loc_info(loc_info_t *i)
{
    i->input_name = input_name ? input_name : "stdin";
    i->line_number = line_number;
    i->near_text = parser_text;
}