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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  Tox ;

/* Variables and functions */
 int typing_changes ; 

void print_typingchange(Tox *m, uint32_t friendnumber, bool typing, void *userdata)
{
    if (*((uint32_t *)userdata) != 974536)
        return;

    if (!typing)
        typing_changes = 1;
    else
        typing_changes = 2;
}