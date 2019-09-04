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
 char get_key (char*,char*) ; 
 scalar_t__ interactive ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static char print_fat_dirty_state(void)
{
    printf("Dirty bit is set. Fs was not properly unmounted and"
	   " some data may be corrupt.\n");

    if (interactive) {
	printf("1) Remove dirty bit\n" "2) No action\n");
	return get_key("12", "?");
#ifndef __REACTOS__
    } else
#else
    } else if (rw) {
#endif
	printf(" Automatically removing dirty bit.\n");
    return '1';
#ifdef __REACTOS__
    }
    return '2';
#endif
}