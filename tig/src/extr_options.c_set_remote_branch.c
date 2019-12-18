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
struct TYPE_2__ {scalar_t__* remote; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRING_SIZE (char*) ; 
 int /*<<< orphan*/  prefixcmp (char const*,char*) ; 
 TYPE_1__ repo ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  string_format_from (scalar_t__*,size_t*,char*,char const*) ; 
 int /*<<< orphan*/  string_ncopy (scalar_t__*,char const*,size_t) ; 
 size_t strlen (scalar_t__*) ; 

__attribute__((used)) static void
set_remote_branch(const char *name, const char *value, size_t valuelen)
{
	if (!strcmp(name, ".remote")) {
		string_ncopy(repo.remote, value, valuelen);

	} else if (*repo.remote && !strcmp(name, ".merge")) {
		size_t from = strlen(repo.remote);

		if (!prefixcmp(value, "refs/heads/"))
			value += STRING_SIZE("refs/heads/");

		if (!string_format_from(repo.remote, &from, "/%s", value))
			repo.remote[0] = 0;
	}
}