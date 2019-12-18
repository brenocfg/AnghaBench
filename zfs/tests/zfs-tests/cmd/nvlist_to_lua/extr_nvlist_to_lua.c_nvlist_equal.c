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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
#define  DATA_TYPE_BOOLEAN_VALUE 131 
#define  DATA_TYPE_INT64 130 
#define  DATA_TYPE_NVLIST 129 
#define  DATA_TYPE_STRING 128 
 int /*<<< orphan*/  fnvlist_lookup_boolean_value (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fnvlist_lookup_int64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvlist (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvpair (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fnvlist_lookup_string (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ fnvlist_num_pairs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvpair_value_boolean_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvpair_value_int64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvpair_value_nvlist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvpair_value_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
nvlist_equal(nvlist_t *nvla, nvlist_t *nvlb)
{
	if (fnvlist_num_pairs(nvla) != fnvlist_num_pairs(nvlb))
		return (B_FALSE);
	/*
	 * The nvlists have the same number of pairs and keys are unique, so
	 * if every key in A is also in B and assigned to the same value, the
	 * lists are identical.
	 */
	for (nvpair_t *pair = nvlist_next_nvpair(nvla, NULL);
	    pair != NULL; pair = nvlist_next_nvpair(nvla, pair)) {
		char *key = nvpair_name(pair);

		if (!nvlist_exists(nvlb, key))
			return (B_FALSE);

		if (nvpair_type(pair) !=
		    nvpair_type(fnvlist_lookup_nvpair(nvlb, key)))
			return (B_FALSE);

		switch (nvpair_type(pair)) {
		case DATA_TYPE_BOOLEAN_VALUE:
			if (fnvpair_value_boolean_value(pair) !=
			    fnvlist_lookup_boolean_value(nvlb, key)) {
				return (B_FALSE);
			}
			break;
		case DATA_TYPE_STRING:
			if (strcmp(fnvpair_value_string(pair),
			    fnvlist_lookup_string(nvlb, key))) {
				return (B_FALSE);
			}
			break;
		case DATA_TYPE_INT64:
			if (fnvpair_value_int64(pair) !=
			    fnvlist_lookup_int64(nvlb, key)) {
				return (B_FALSE);
			}
			break;
		case DATA_TYPE_NVLIST:
			if (!nvlist_equal(fnvpair_value_nvlist(pair),
			    fnvlist_lookup_nvlist(nvlb, key))) {
				return (B_FALSE);
			}
			break;
		default:
			(void) printf("Unexpected type for nvlist_equal\n");
			return (B_FALSE);
		}
	}
	return (B_TRUE);
}