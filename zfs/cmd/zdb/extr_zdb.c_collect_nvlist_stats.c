#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t zns_leaf_total; size_t zns_leaf_largest; int /*<<< orphan*/  zns_leaf_count; int /*<<< orphan*/  zns_boolean; int /*<<< orphan*/  zns_uint64; int /*<<< orphan*/  zns_string; int /*<<< orphan*/  zns_list_count; } ;
typedef  TYPE_1__ zdb_nvl_stats_t ;
typedef  size_t uint_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
#define  DATA_TYPE_BOOLEAN 132 
#define  DATA_TYPE_NVLIST 131 
#define  DATA_TYPE_NVLIST_ARRAY 130 
#define  DATA_TYPE_STRING 129 
#define  DATA_TYPE_UINT64 128 
 int /*<<< orphan*/  NV_ENCODE_XDR ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvpair_value_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvpair_value_uint64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_size (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int nvpair_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvpair_value_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ***,size_t*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void
collect_nvlist_stats(nvlist_t *nvl, zdb_nvl_stats_t *stats)
{
	nvlist_t *list, **array;
	nvpair_t *nvp = NULL;
	char *name;
	uint_t i, items;

	stats->zns_list_count++;

	while ((nvp = nvlist_next_nvpair(nvl, nvp)) != NULL) {
		name = nvpair_name(nvp);

		switch (nvpair_type(nvp)) {
		case DATA_TYPE_STRING:
			fnvlist_add_string(stats->zns_string, name,
			    fnvpair_value_string(nvp));
			break;
		case DATA_TYPE_UINT64:
			fnvlist_add_uint64(stats->zns_uint64, name,
			    fnvpair_value_uint64(nvp));
			break;
		case DATA_TYPE_BOOLEAN:
			fnvlist_add_boolean(stats->zns_boolean, name);
			break;
		case DATA_TYPE_NVLIST:
			if (nvpair_value_nvlist(nvp, &list) == 0)
				collect_nvlist_stats(list, stats);
			break;
		case DATA_TYPE_NVLIST_ARRAY:
			if (nvpair_value_nvlist_array(nvp, &array, &items) != 0)
				break;

			for (i = 0; i < items; i++) {
				collect_nvlist_stats(array[i], stats);

				/* collect stats on leaf vdev */
				if (strcmp(name, "children") == 0) {
					size_t size;

					(void) nvlist_size(array[i], &size,
					    NV_ENCODE_XDR);
					stats->zns_leaf_total += size;
					if (size > stats->zns_leaf_largest)
						stats->zns_leaf_largest = size;
					stats->zns_leaf_count++;
				}
			}
			break;
		default:
			(void) printf("skip type %d!\n", (int)nvpair_type(nvp));
		}
	}
}