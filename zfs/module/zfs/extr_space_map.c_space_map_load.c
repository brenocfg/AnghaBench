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
typedef  int /*<<< orphan*/  space_map_t ;
typedef  int /*<<< orphan*/  range_tree_t ;
typedef  int /*<<< orphan*/  maptype_t ;

/* Variables and functions */
 int /*<<< orphan*/  space_map_length (int /*<<< orphan*/ *) ; 
 int space_map_load_length (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
space_map_load(space_map_t *sm, range_tree_t *rt, maptype_t maptype)
{
	return (space_map_load_length(sm, rt, maptype, space_map_length(sm)));
}