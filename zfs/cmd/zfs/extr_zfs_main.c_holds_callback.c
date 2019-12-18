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
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_2__ {size_t cb_max_namelen; size_t cb_max_taglen; int /*<<< orphan*/  cb_snapname; scalar_t__ cb_recursive; int /*<<< orphan*/ ** cb_nvlp; } ;
typedef  TYPE_1__ holds_cbdata_t ;

/* Variables and functions */
 int nvlist_add_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ zfs_get_holds (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 char* zfs_get_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
holds_callback(zfs_handle_t *zhp, void *data)
{
	holds_cbdata_t *cbp = data;
	nvlist_t *top_nvl = *cbp->cb_nvlp;
	nvlist_t *nvl = NULL;
	nvpair_t *nvp = NULL;
	const char *zname = zfs_get_name(zhp);
	size_t znamelen = strlen(zname);

	if (cbp->cb_recursive) {
		const char *snapname;
		char *delim  = strchr(zname, '@');
		if (delim == NULL)
			return (0);

		snapname = delim + 1;
		if (strcmp(cbp->cb_snapname, snapname))
			return (0);
	}

	if (zfs_get_holds(zhp, &nvl) != 0)
		return (-1);

	if (znamelen > cbp->cb_max_namelen)
		cbp->cb_max_namelen  = znamelen;

	while ((nvp = nvlist_next_nvpair(nvl, nvp)) != NULL) {
		const char *tag = nvpair_name(nvp);
		size_t taglen = strlen(tag);
		if (taglen > cbp->cb_max_taglen)
			cbp->cb_max_taglen  = taglen;
	}

	return (nvlist_add_nvlist(top_nvl, zname, nvl));
}