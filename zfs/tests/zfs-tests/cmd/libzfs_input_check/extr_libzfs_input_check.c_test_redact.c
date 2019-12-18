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
typedef  int /*<<< orphan*/  bookmark ;

/* Variables and functions */
 int /*<<< orphan*/  IOC_INPUT_TEST (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXNAMELEN ; 
 int /*<<< orphan*/  ZFS_IOC_REDACT ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcat (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  zfs_destroy (char*) ; 

__attribute__((used)) static void
test_redact(const char *snapshot1, const char *snapshot2)
{
	nvlist_t *required = fnvlist_alloc();
	nvlist_t *snapnv = fnvlist_alloc();
	char bookmark[MAXNAMELEN + 32];

	fnvlist_add_string(required, "bookname", "testbookmark");
	fnvlist_add_boolean(snapnv, snapshot2);
	fnvlist_add_nvlist(required, "snapnv", snapnv);

	IOC_INPUT_TEST(ZFS_IOC_REDACT, snapshot1, required, NULL, 0);

	nvlist_free(snapnv);
	nvlist_free(required);

	strlcpy(bookmark, snapshot1, sizeof (bookmark));
	*strchr(bookmark, '@') = '\0';
	strlcat(bookmark, "#testbookmark", sizeof (bookmark) -
	    strlen(bookmark));
	zfs_destroy(bookmark);
}