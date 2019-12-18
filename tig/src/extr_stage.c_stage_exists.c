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
struct view {struct view* parent; } ;
struct status {int dummy; } ;
typedef  enum line_type { ____Placeholder_line_type } line_type ;

/* Variables and functions */
 int main_status_exists (struct view*,int) ; 
 struct view main_view ; 
 int status_exists (struct view*,struct status*,int) ; 
 struct view status_view ; 

__attribute__((used)) static bool
stage_exists(struct view *view, struct status *status, enum line_type type)
{
	struct view *parent = view->parent;

	if (parent == &status_view)
		return status_exists(parent, status, type);

	if (parent == &main_view)
		return main_status_exists(parent, type);

	return false;
}