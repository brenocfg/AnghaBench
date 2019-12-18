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
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  SeafileSession ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_ALLOW_INVALID_WORKTREE ; 
 int seafile_session_config_set_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

int
seafile_session_config_set_allow_invalid_worktree(SeafileSession *session, gboolean val)
{
    return seafile_session_config_set_string(session, KEY_ALLOW_INVALID_WORKTREE,
                                             val ? "true" : "false");
}