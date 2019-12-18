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
struct window_mode_entry {int dummy; } ;

/* Variables and functions */
 int window_copy_search (struct window_mode_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
window_copy_search_up(struct window_mode_entry *wme)
{
	return (window_copy_search(wme, 0));
}