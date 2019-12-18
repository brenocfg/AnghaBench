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

/* Variables and functions */
 int /*<<< orphan*/  pp_del_define (char*) ; 

__attribute__((used)) static void del_special_defines(void)
{
    pp_del_define( "__DATE__" );
    pp_del_define( "__TIME__" );
    pp_del_define( "__FILE__" );
    pp_del_define( "__LINE__" );
}