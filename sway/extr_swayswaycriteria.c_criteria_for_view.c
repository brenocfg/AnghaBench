#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sway_view {int dummy; } ;
struct criteria {int type; } ;
struct TYPE_6__ {int length; struct criteria** items; } ;
typedef  TYPE_1__ list_t ;
typedef  enum criteria_type { ____Placeholder_criteria_type } criteria_type ;
struct TYPE_7__ {TYPE_1__* criteria; } ;

/* Variables and functions */
 TYPE_5__* config ; 
 TYPE_1__* create_list () ; 
 scalar_t__ criteria_matches_view (struct criteria*,struct sway_view*) ; 
 int /*<<< orphan*/  list_add (TYPE_1__*,struct criteria*) ; 

list_t *criteria_for_view(struct sway_view *view, enum criteria_type types) {
	list_t *criterias = config->criteria;
	list_t *matches = create_list();
	for (int i = 0; i < criterias->length; ++i) {
		struct criteria *criteria = criterias->items[i];
		if ((criteria->type & types) && criteria_matches_view(criteria, view)) {
			list_add(matches, criteria);
		}
	}
	return matches;
}