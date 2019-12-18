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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  nomem () ; 
 scalar_t__ nvlist_add_boolean (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ nvlist_exists (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 

__attribute__((used)) static boolean_t
parsepropname(nvlist_t *props, char *propname)
{
	if (strchr(propname, '=') != NULL) {
		(void) fprintf(stderr, gettext("invalid character "
		    "'=' in property argument\n"));
		return (B_FALSE);
	}
	if (nvlist_exists(props, propname)) {
		(void) fprintf(stderr, gettext("property '%s' "
		    "specified multiple times\n"), propname);
		return (B_FALSE);
	}
	if (nvlist_add_boolean(props, propname) != 0)
		nomem();
	return (B_TRUE);
}