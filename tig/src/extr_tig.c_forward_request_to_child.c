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
struct view {TYPE_1__* ops; int /*<<< orphan*/  vid; } ;
typedef  enum request { ____Placeholder_request } request ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int displayed_views () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ view_is_displayed (struct view*) ; 

__attribute__((used)) static bool
forward_request_to_child(struct view *child, enum request request)
{
	return displayed_views() == 2 && view_is_displayed(child) &&
		!strcmp(child->vid, child->ops->id);
}