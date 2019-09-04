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
struct options_entry {int dummy; } ;
struct options {int /*<<< orphan*/  tree; } ;

/* Variables and functions */
 struct options_entry* RB_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  options_tree ; 

struct options_entry *
options_first(struct options *oo)
{
	return (RB_MIN(options_tree, &oo->tree));
}