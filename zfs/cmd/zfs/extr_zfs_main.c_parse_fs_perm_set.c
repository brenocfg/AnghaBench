#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uu_avl_index_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  fs_perm_t ;
struct TYPE_8__ {int /*<<< orphan*/  fsps_list; int /*<<< orphan*/  fsps_list_pool; } ;
typedef  TYPE_1__ fs_perm_set_t ;
struct TYPE_9__ {int /*<<< orphan*/  fspn_list_node; int /*<<< orphan*/  fspn_fsperm; } ;
typedef  TYPE_2__ fs_perm_node_t ;
typedef  scalar_t__ data_type_t ;

/* Variables and functions */
 scalar_t__ DATA_TYPE_NVLIST ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  fs_perm_init (int /*<<< orphan*/ *,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  nomem () ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_type (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  parse_fs_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* safe_malloc (int) ; 
 int /*<<< orphan*/  uu_list_insert (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_list_node_init (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_list_numnodes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
parse_fs_perm_set(fs_perm_set_t *fspset, nvlist_t *nvl)
{
	nvpair_t *nvp = NULL;
	uu_avl_index_t idx = 0;

	while ((nvp = nvlist_next_nvpair(nvl, nvp)) != NULL) {
		nvlist_t *nvl2 = NULL;
		const char *fsname = nvpair_name(nvp);
		data_type_t type = nvpair_type(nvp);
		fs_perm_t *fsperm = NULL;
		fs_perm_node_t *node = safe_malloc(sizeof (fs_perm_node_t));
		if (node == NULL)
			nomem();

		fsperm = &node->fspn_fsperm;

		VERIFY(DATA_TYPE_NVLIST == type);

		uu_list_node_init(node, &node->fspn_list_node,
		    fspset->fsps_list_pool);

		idx = uu_list_numnodes(fspset->fsps_list);
		fs_perm_init(fsperm, fspset, fsname);

		if (nvpair_value_nvlist(nvp, &nvl2) != 0)
			return (-1);

		(void) parse_fs_perm(fsperm, nvl2);

		uu_list_insert(fspset->fsps_list, node, idx);
	}

	return (0);
}