#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int zfs_deleg_who_type_t ;
struct TYPE_9__ {char* who_name; char* who_ug_name; int who_type; int /*<<< orphan*/ * who_deleg_perm_avl; } ;
struct TYPE_11__ {TYPE_1__ who_perm; } ;
typedef  TYPE_3__ who_perm_node_t ;
typedef  int /*<<< orphan*/  uu_avl_walk_t ;
typedef  int /*<<< orphan*/  uu_avl_t ;
struct TYPE_10__ {scalar_t__ dp_local; scalar_t__ dp_descend; int /*<<< orphan*/  dp_name; } ;
struct TYPE_12__ {TYPE_2__ dpn_perm; } ;
typedef  TYPE_4__ deleg_perm_node_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  UU_WALK_ROBUST ; 
#define  ZFS_DELEG_EVERYONE 133 
#define  ZFS_DELEG_EVERYONE_SETS 132 
#define  ZFS_DELEG_GROUP 131 
#define  ZFS_DELEG_GROUP_SETS 130 
#define  ZFS_DELEG_USER 129 
#define  ZFS_DELEG_USER_SETS 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  nomem () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_4__* uu_avl_first (int /*<<< orphan*/ *) ; 
 TYPE_4__* uu_avl_next (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  uu_avl_walk_end (int /*<<< orphan*/ *) ; 
 TYPE_3__* uu_avl_walk_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uu_avl_walk_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_uge_deleg_perms(uu_avl_t *who_avl, boolean_t local, boolean_t descend,
    const char *title)
{
	who_perm_node_t *who_node = NULL;
	boolean_t prt_title = B_TRUE;
	uu_avl_walk_t *walk;

	if ((walk = uu_avl_walk_start(who_avl, UU_WALK_ROBUST)) == NULL)
		nomem();

	while ((who_node = uu_avl_walk_next(walk)) != NULL) {
		const char *who_name = who_node->who_perm.who_name;
		const char *nice_who_name = who_node->who_perm.who_ug_name;
		uu_avl_t *avl = who_node->who_perm.who_deleg_perm_avl;
		zfs_deleg_who_type_t who_type = who_node->who_perm.who_type;
		char delim = ' ';
		deleg_perm_node_t *deleg_node;
		boolean_t prt_who = B_TRUE;

		for (deleg_node = uu_avl_first(avl);
		    deleg_node != NULL;
		    deleg_node = uu_avl_next(avl, deleg_node)) {
			if (local != deleg_node->dpn_perm.dp_local ||
			    descend != deleg_node->dpn_perm.dp_descend)
				continue;

			if (prt_who) {
				const char *who = NULL;
				if (prt_title) {
					prt_title = B_FALSE;
					(void) printf("%s", title);
				}

				switch (who_type) {
				case ZFS_DELEG_USER_SETS:
				case ZFS_DELEG_USER:
					who = gettext("user");
					if (nice_who_name)
						who_name  = nice_who_name;
					break;
				case ZFS_DELEG_GROUP_SETS:
				case ZFS_DELEG_GROUP:
					who = gettext("group");
					if (nice_who_name)
						who_name  = nice_who_name;
					break;
				case ZFS_DELEG_EVERYONE_SETS:
				case ZFS_DELEG_EVERYONE:
					who = gettext("everyone");
					who_name = NULL;
					break;

				default:
					assert(who != NULL);
				}

				prt_who = B_FALSE;
				if (who_name == NULL)
					(void) printf("\t%s", who);
				else
					(void) printf("\t%s %s", who, who_name);
			}

			(void) printf("%c%s", delim,
			    deleg_node->dpn_perm.dp_name);
			delim = ',';
		}

		if (!prt_who)
			(void) printf("\n");
	}

	uu_avl_walk_end(walk);
}