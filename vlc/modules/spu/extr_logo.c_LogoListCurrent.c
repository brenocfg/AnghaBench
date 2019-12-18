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
typedef  int /*<<< orphan*/  logo_t ;
struct TYPE_3__ {size_t i_counter; int /*<<< orphan*/ * p_logo; } ;
typedef  TYPE_1__ logo_list_t ;

/* Variables and functions */

__attribute__((used)) static logo_t *LogoListCurrent( logo_list_t *p_list )
{
    return &p_list->p_logo[p_list->i_counter];
}