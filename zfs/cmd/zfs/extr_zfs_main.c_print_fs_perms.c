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
typedef  int /*<<< orphan*/  uu_avl_t ;
struct TYPE_9__ {int /*<<< orphan*/  fsps_list; } ;
typedef  TYPE_2__ fs_perm_set_t ;
struct TYPE_8__ {char* fsp_name; int /*<<< orphan*/ * fsp_uge_avl; int /*<<< orphan*/ * fsp_sc_avl; } ;
struct TYPE_10__ {TYPE_1__ fspn_fsperm; } ;
typedef  TYPE_3__ fs_perm_node_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  MAXNAMELEN ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  print_set_creat_perms (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_uge_deleg_perms (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int strlen (char*) ; 
 TYPE_3__* uu_list_first (int /*<<< orphan*/ ) ; 
 TYPE_3__* uu_list_next (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void
print_fs_perms(fs_perm_set_t *fspset)
{
	fs_perm_node_t *node = NULL;
	char buf[MAXNAMELEN + 32];
	const char *dsname = buf;

	for (node = uu_list_first(fspset->fsps_list); node != NULL;
	    node = uu_list_next(fspset->fsps_list, node)) {
		uu_avl_t *sc_avl = node->fspn_fsperm.fsp_sc_avl;
		uu_avl_t *uge_avl = node->fspn_fsperm.fsp_uge_avl;
		int left = 0;

		(void) snprintf(buf, sizeof (buf),
		    gettext("---- Permissions on %s "),
		    node->fspn_fsperm.fsp_name);
		(void) printf("%s", dsname);
		left = 70 - strlen(buf);
		while (left-- > 0)
			(void) printf("-");
		(void) printf("\n");

		print_set_creat_perms(sc_avl);
		print_uge_deleg_perms(uge_avl, B_TRUE, B_FALSE,
		    gettext("Local permissions:\n"));
		print_uge_deleg_perms(uge_avl, B_FALSE, B_TRUE,
		    gettext("Descendent permissions:\n"));
		print_uge_deleg_perms(uge_avl, B_TRUE, B_TRUE,
		    gettext("Local+Descendent permissions:\n"));
	}
}