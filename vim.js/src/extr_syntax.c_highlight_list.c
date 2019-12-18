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
 int /*<<< orphan*/  HLF_D ; 
 int /*<<< orphan*/  highlight_list_two (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hl_attr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
highlight_list()
{
    int		i;

    for (i = 10; --i >= 0; )
	highlight_list_two(i, hl_attr(HLF_D));
    for (i = 40; --i >= 0; )
	highlight_list_two(99, 0);
}