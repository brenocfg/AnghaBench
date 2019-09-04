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
struct ref_opt {char const* member_0; char const* member_1; } ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int add_to_refs (char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct ref_opt*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

enum status_code
add_ref(const char *id, char *name, const char *remote_name, const char *head)
{
	struct ref_opt opt = { remote_name, head };

	return add_to_refs(id, strlen(id), name, strlen(name), &opt);
}