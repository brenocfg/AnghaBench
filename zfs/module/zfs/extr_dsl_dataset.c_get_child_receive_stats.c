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
typedef  int /*<<< orphan*/  recvname ;
struct TYPE_9__ {TYPE_1__* ds_dir; } ;
typedef  TYPE_2__ dsl_dataset_t ;
struct TYPE_8__ {int /*<<< orphan*/  dd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  ZFS_MAX_DATASET_NAME_LEN ; 
 scalar_t__ dsl_dataset_hold (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  dsl_dataset_name (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* get_receive_resume_stats_impl (TYPE_2__*) ; 
 char* kmem_strdup (char*) ; 
 char* recv_clone_name ; 
 int strlcat (char*,char*,int) ; 

char *
get_child_receive_stats(dsl_dataset_t *ds)
{
	char recvname[ZFS_MAX_DATASET_NAME_LEN + 6];
	dsl_dataset_t *recv_ds;
	dsl_dataset_name(ds, recvname);
	if (strlcat(recvname, "/", sizeof (recvname)) <
	    sizeof (recvname) &&
	    strlcat(recvname, recv_clone_name, sizeof (recvname)) <
	    sizeof (recvname) &&
	    dsl_dataset_hold(ds->ds_dir->dd_pool, recvname, FTAG,
	    &recv_ds)  == 0) {
		char *propval = get_receive_resume_stats_impl(recv_ds);
		dsl_dataset_rele(recv_ds, FTAG);
		return (propval);
	}
	return (kmem_strdup(""));
}