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
struct cache_tree {int entry_count; } ;

/* Variables and functions */
 struct cache_tree* calloc (int,int) ; 

struct cache_tree *cache_tree(void)
{
    struct cache_tree *it = calloc(1, sizeof(struct cache_tree));
    it->entry_count = -1;
    return it;
}