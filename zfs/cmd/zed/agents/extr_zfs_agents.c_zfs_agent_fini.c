#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fmd_hdl_t ;
struct TYPE_5__ {int /*<<< orphan*/  ae_nvl; } ;
typedef  TYPE_1__ agent_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  _zfs_diagnosis_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _zfs_retire_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  agent_cond ; 
 int /*<<< orphan*/  agent_events ; 
 int agent_exiting ; 
 int /*<<< orphan*/  fmd_hdl_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fmd_module_hdl (char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_agents_tid ; 
 int /*<<< orphan*/ * g_zfs_hdl ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_slm_fini () ; 

void
zfs_agent_fini(void)
{
	fmd_hdl_t *hdl;
	agent_event_t *event;

	agent_exiting = 1;
	(void) pthread_cond_signal(&agent_cond);

	/* wait for zfs_enum_pools thread to complete */
	(void) pthread_join(g_agents_tid, NULL);

	/* drain any pending events */
	while ((event = (list_head(&agent_events))) != NULL) {
		list_remove(&agent_events, event);
		nvlist_free(event->ae_nvl);
		free(event);
	}

	list_destroy(&agent_events);

	if ((hdl = fmd_module_hdl("zfs-retire")) != NULL) {
		_zfs_retire_fini(hdl);
		fmd_hdl_unregister(hdl);
	}
	if ((hdl = fmd_module_hdl("zfs-diagnosis")) != NULL) {
		_zfs_diagnosis_fini(hdl);
		fmd_hdl_unregister(hdl);
	}

	zed_log_msg(LOG_INFO, "Add Agent: fini");
	zfs_slm_fini();

	g_zfs_hdl = NULL;
}