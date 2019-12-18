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
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_2__ {int /*<<< orphan*/ ** def_val; } ;

/* Variables and functions */
 size_t VI_DEFAULT ; 
 int findoption (int /*<<< orphan*/ *) ; 
 TYPE_1__* options ; 

char_u *
get_highlight_default()
{
    int i;

    i = findoption((char_u *)"hl");
    if (i >= 0)
	return options[i].def_val[VI_DEFAULT];
    return (char_u *)NULL;
}