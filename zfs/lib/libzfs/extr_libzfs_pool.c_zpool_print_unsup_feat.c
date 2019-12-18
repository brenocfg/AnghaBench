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
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 scalar_t__ DATA_TYPE_STRING ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_LOAD_INFO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_UNSUP_FEAT ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_type (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_value_string (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  verify (int) ; 

void
zpool_print_unsup_feat(nvlist_t *config)
{
	nvlist_t *nvinfo, *unsup_feat;
	nvpair_t *nvp;

	verify(nvlist_lookup_nvlist(config, ZPOOL_CONFIG_LOAD_INFO, &nvinfo) ==
	    0);
	verify(nvlist_lookup_nvlist(nvinfo, ZPOOL_CONFIG_UNSUP_FEAT,
	    &unsup_feat) == 0);

	for (nvp = nvlist_next_nvpair(unsup_feat, NULL); nvp != NULL;
	    nvp = nvlist_next_nvpair(unsup_feat, nvp)) {
		char *desc;

		verify(nvpair_type(nvp) == DATA_TYPE_STRING);
		verify(nvpair_value_string(nvp, &desc) == 0);

		if (strlen(desc) > 0)
			(void) printf("\t%s (%s)\n", nvpair_name(nvp), desc);
		else
			(void) printf("\t%s\n", nvpair_name(nvp));
	}
}