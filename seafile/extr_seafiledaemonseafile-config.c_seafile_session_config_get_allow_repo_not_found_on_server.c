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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  SeafileSession ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_ALLOW_REPO_NOT_FOUND_ON_SERVER ; 
 int /*<<< orphan*/  seafile_session_config_get_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

gboolean
seafile_session_config_get_allow_repo_not_found_on_server(SeafileSession *session)
{
    return seafile_session_config_get_bool (session,
                                            KEY_ALLOW_REPO_NOT_FOUND_ON_SERVER);
}