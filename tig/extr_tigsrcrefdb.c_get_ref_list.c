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
struct ref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  refs_by_id ; 
 struct ref const* string_map_get (int /*<<< orphan*/ *,char const*) ; 

const struct ref *
get_ref_list(const char *id)
{
	return string_map_get(&refs_by_id, id);
}