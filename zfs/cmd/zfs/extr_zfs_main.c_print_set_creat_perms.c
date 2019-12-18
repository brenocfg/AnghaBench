#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_deleg_who_type_t ;
struct TYPE_9__ {char* dp_name; } ;
struct TYPE_8__ {char* who_name; int /*<<< orphan*/  who_type; int /*<<< orphan*/ * who_deleg_perm_avl; } ;
struct TYPE_10__ {TYPE_2__ dpn_perm; TYPE_1__ who_perm; } ;
typedef  TYPE_3__ who_perm_node_t ;
typedef  int /*<<< orphan*/  uu_avl_t ;
typedef  TYPE_3__ deleg_perm_node_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 char const* gettext (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strnlen (char const*,int) ; 
 TYPE_3__* uu_avl_first (int /*<<< orphan*/ *) ; 
 TYPE_3__* uu_avl_next (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int who_type2weight (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_set_creat_perms(uu_avl_t *who_avl)
{
	const char *sc_title[] = {
		gettext("Permission sets:\n"),
		gettext("Create time permissions:\n"),
		NULL
	};
	who_perm_node_t *who_node = NULL;
	int prev_weight = -1;

	for (who_node = uu_avl_first(who_avl); who_node != NULL;
	    who_node = uu_avl_next(who_avl, who_node)) {
		uu_avl_t *avl = who_node->who_perm.who_deleg_perm_avl;
		zfs_deleg_who_type_t who_type = who_node->who_perm.who_type;
		const char *who_name = who_node->who_perm.who_name;
		int weight = who_type2weight(who_type);
		boolean_t first = B_TRUE;
		deleg_perm_node_t *deleg_node;

		if (prev_weight != weight) {
			(void) printf("%s", sc_title[weight]);
			prev_weight = weight;
		}

		if (who_name == NULL || strnlen(who_name, 1) == 0)
			(void) printf("\t");
		else
			(void) printf("\t%s ", who_name);

		for (deleg_node = uu_avl_first(avl); deleg_node != NULL;
		    deleg_node = uu_avl_next(avl, deleg_node)) {
			if (first) {
				(void) printf("%s",
				    deleg_node->dpn_perm.dp_name);
				first = B_FALSE;
			} else
				(void) printf(",%s",
				    deleg_node->dpn_perm.dp_name);
		}

		(void) printf("\n");
	}
}