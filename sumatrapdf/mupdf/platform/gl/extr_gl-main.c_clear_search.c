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
 int /*<<< orphan*/  currentpage ; 
 int /*<<< orphan*/  fz_make_location (int,int) ; 
 scalar_t__ search_hit_count ; 
 int /*<<< orphan*/  search_hit_page ; 
 int /*<<< orphan*/  search_page ; 
 scalar_t__ showsearch ; 

__attribute__((used)) static void clear_search(void)
{
	showsearch = 0;
	search_page = currentpage;
	search_hit_page = fz_make_location(-1, -1);
	search_hit_count = 0;
}