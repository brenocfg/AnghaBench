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

/* Variables and functions */
 int SA_OK ; 
 int SA_SYNTAX_ERR ; 
 int /*<<< orphan*/  add_linux_shareopt (char**,char const*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
get_linux_shareopts_cb(const char *key, const char *value, void *cookie)
{
	char **plinux_opts = (char **)cookie;

	/* host-specific options, these are taken care of elsewhere */
	if (strcmp(key, "ro") == 0 || strcmp(key, "rw") == 0 ||
	    strcmp(key, "sec") == 0)
		return (SA_OK);

	if (strcmp(key, "anon") == 0)
		key = "anonuid";

	if (strcmp(key, "root_mapping") == 0) {
		(void) add_linux_shareopt(plinux_opts, "root_squash", NULL);
		key = "anonuid";
	}

	if (strcmp(key, "nosub") == 0)
		key = "subtree_check";

	if (strcmp(key, "insecure") != 0 && strcmp(key, "secure") != 0 &&
	    strcmp(key, "async") != 0 && strcmp(key, "sync") != 0 &&
	    strcmp(key, "no_wdelay") != 0 && strcmp(key, "wdelay") != 0 &&
	    strcmp(key, "nohide") != 0 && strcmp(key, "hide") != 0 &&
	    strcmp(key, "crossmnt") != 0 &&
	    strcmp(key, "no_subtree_check") != 0 &&
	    strcmp(key, "subtree_check") != 0 &&
	    strcmp(key, "insecure_locks") != 0 &&
	    strcmp(key, "secure_locks") != 0 &&
	    strcmp(key, "no_auth_nlm") != 0 && strcmp(key, "auth_nlm") != 0 &&
	    strcmp(key, "no_acl") != 0 && strcmp(key, "mountpoint") != 0 &&
	    strcmp(key, "mp") != 0 && strcmp(key, "fsuid") != 0 &&
	    strcmp(key, "refer") != 0 && strcmp(key, "replicas") != 0 &&
	    strcmp(key, "root_squash") != 0 &&
	    strcmp(key, "no_root_squash") != 0 &&
	    strcmp(key, "all_squash") != 0 &&
	    strcmp(key, "no_all_squash") != 0 && strcmp(key, "fsid") != 0 &&
	    strcmp(key, "anonuid") != 0 && strcmp(key, "anongid") != 0) {
		return (SA_SYNTAX_ERR);
	}

	(void) add_linux_shareopt(plinux_opts, key, value);

	return (SA_OK);
}