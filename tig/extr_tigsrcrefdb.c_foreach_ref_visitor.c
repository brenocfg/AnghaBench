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
struct ref_visitor_data {int (* visitor ) (int /*<<< orphan*/ ,struct ref const*) ;int /*<<< orphan*/  data; } ;
struct ref {int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct ref const*) ; 

__attribute__((used)) static bool
foreach_ref_visitor(void *data, void *value)
{
	struct ref_visitor_data *visitor_data = data;
	const struct ref *ref = value;

	if (!ref->valid)
		return true;
	return visitor_data->visitor(visitor_data->data, ref);
}