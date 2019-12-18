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
struct match_data {int /*<<< orphan*/ * matches; struct criteria* criteria; } ;
struct criteria {int dummy; } ;
typedef  int /*<<< orphan*/  list_t ;

/* Variables and functions */
 int /*<<< orphan*/ * create_list () ; 
 int /*<<< orphan*/  criteria_get_views_iterator ; 
 int /*<<< orphan*/  root_for_each_container (int /*<<< orphan*/ ,struct match_data*) ; 

list_t *criteria_get_views(struct criteria *criteria) {
	list_t *matches = create_list();
	struct match_data data = {
		.criteria = criteria,
		.matches = matches,
	};
	root_for_each_container(criteria_get_views_iterator, &data);
	return matches;
}