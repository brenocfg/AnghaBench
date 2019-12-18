#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* gboolean ;
struct TYPE_8__ {int cdc_average_block_size; int /*<<< orphan*/  sync_mgr; int /*<<< orphan*/  clone_mgr; int /*<<< orphan*/  repo_mgr; int /*<<< orphan*/  filelock_mgr; int /*<<< orphan*/  branch_mgr; int /*<<< orphan*/  fs_mgr; int /*<<< orphan*/  commit_mgr; int /*<<< orphan*/  mq_mgr; void* disable_block_hash; void* http_proxy_password; void* http_proxy_username; void* http_proxy_port; void* http_proxy_addr; void* http_proxy_type; void* use_http_proxy; void* disable_verify_certificate; int /*<<< orphan*/  enable_http_sync; void* sync_extra_temp_file; void* client_name; void* client_id; int /*<<< orphan*/  ccnet_dir; } ;
typedef  TYPE_1__ SeafileSession ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_CDC_AVERAGE_BLOCK_SIZE ; 
 int /*<<< orphan*/  KEY_CLIENT_ID ; 
 int /*<<< orphan*/  KEY_CLIENT_NAME ; 
 char* KEY_DISABLE_BLOCK_HASH ; 
 char* KEY_DISABLE_VERIFY_CERTIFICATE ; 
 int /*<<< orphan*/  KEY_PROXY_ADDR ; 
 int /*<<< orphan*/  KEY_PROXY_PASSWORD ; 
 int /*<<< orphan*/  KEY_PROXY_PORT ; 
 int /*<<< orphan*/  KEY_PROXY_TYPE ; 
 int /*<<< orphan*/  KEY_PROXY_USERNAME ; 
 char* KEY_SYNC_EXTRA_TEMP_FILE ; 
 char* KEY_USE_PROXY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 void* g_strdup (char*) ; 
 void* generate_client_id () ; 
 int /*<<< orphan*/  load_system_proxy (TYPE_1__*) ; 
 int /*<<< orphan*/  read_ccnet_conf (int /*<<< orphan*/ ,char**,char**) ; 
 int /*<<< orphan*/  seaf_branch_manager_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_clone_manager_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_commit_manager_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_filelock_manager_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_fs_manager_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_mq_manager_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_repo_manager_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_sync_manager_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,void*,void*) ; 
 void* seafile_session_config_get_bool (TYPE_1__*,char*) ; 
 void* seafile_session_config_get_int (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* seafile_session_config_get_string (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seafile_session_config_set_string (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 

void
seafile_session_prepare (SeafileSession *session)
{
    char *client_id = NULL, *client_name = NULL;

    /* load config */

    read_ccnet_conf (session->ccnet_dir, &client_id, &client_name);

    session->client_id = seafile_session_config_get_string (session, KEY_CLIENT_ID);
    if (!session->client_id) {
        if (client_id) {
            session->client_id = g_strdup (client_id);
        } else {
            session->client_id = generate_client_id();
        }
        seafile_session_config_set_string (session,
                                           KEY_CLIENT_ID,
                                           session->client_id);
    }

    session->client_name = seafile_session_config_get_string (session, KEY_CLIENT_NAME);
    if (!session->client_name) {
        if (client_name) {
            session->client_name = g_strdup (client_name);
            seafile_session_config_set_string (session,
                                               KEY_CLIENT_NAME,
                                               session->client_name);
        } else {
            session->client_name = g_strdup("unknown");
        }
    }

    seaf_warning ("client id = %s, client_name = %s\n", session->client_id, session->client_name);
    g_free (client_id);
    g_free (client_name);

    session->sync_extra_temp_file = seafile_session_config_get_bool
        (session, KEY_SYNC_EXTRA_TEMP_FILE);

    /* Enable http sync by default. */
    session->enable_http_sync = TRUE;

    session->disable_verify_certificate = seafile_session_config_get_bool
        (session, KEY_DISABLE_VERIFY_CERTIFICATE);

    session->use_http_proxy =
        seafile_session_config_get_bool(session, KEY_USE_PROXY);

    gboolean use_system_proxy =
        seafile_session_config_get_bool(session, "use_system_proxy");

    if (use_system_proxy) {
        load_system_proxy(session);
    } else {
        session->http_proxy_type =
            seafile_session_config_get_string(session, KEY_PROXY_TYPE);
        session->http_proxy_addr =
            seafile_session_config_get_string(session, KEY_PROXY_ADDR);
        session->http_proxy_port =
            seafile_session_config_get_int(session, KEY_PROXY_PORT, NULL);
        session->http_proxy_username =
            seafile_session_config_get_string(session, KEY_PROXY_USERNAME);
        session->http_proxy_password =
            seafile_session_config_get_string(session, KEY_PROXY_PASSWORD);
    }

    int block_size = seafile_session_config_get_int(session, KEY_CDC_AVERAGE_BLOCK_SIZE, NULL);
    if (block_size > 0)
        session->cdc_average_block_size = block_size;
    else
        session->cdc_average_block_size = 0;

    session->disable_block_hash =
        seafile_session_config_get_bool (session, KEY_DISABLE_BLOCK_HASH);
    
    /* Start mq manager earlier, so that we can send notifications
     * when start repo manager. */
    seaf_mq_manager_init (session->mq_mgr);
    seaf_commit_manager_init (session->commit_mgr);
    seaf_fs_manager_init (session->fs_mgr);
    seaf_branch_manager_init (session->branch_mgr);
    seaf_filelock_manager_init (session->filelock_mgr);
    seaf_repo_manager_init (session->repo_mgr);
    seaf_clone_manager_init (session->clone_mgr);
#ifndef SEAF_TOOL    
    seaf_sync_manager_init (session->sync_mgr);
#endif
}