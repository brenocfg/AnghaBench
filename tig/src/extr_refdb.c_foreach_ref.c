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
struct ref_visitor_data {void* member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  ref_visitor_fn ;

/* Variables and functions */
 int /*<<< orphan*/  foreach_ref_visitor ; 
 int /*<<< orphan*/  refs_by_name ; 
 int /*<<< orphan*/  string_map_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ref_visitor_data*) ; 

void
foreach_ref(ref_visitor_fn visitor, void *data)
{
	struct ref_visitor_data visitor_data = { visitor, data };

	string_map_foreach(&refs_by_name, foreach_ref_visitor, &visitor_data);
}