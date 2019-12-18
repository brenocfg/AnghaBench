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

/* Variables and functions */
 int /*<<< orphan*/  register_marshals ; 
 int /*<<< orphan*/  seafile_cancel_clone_task ; 
 int /*<<< orphan*/  seafile_check_path_for_clone ; 
 int /*<<< orphan*/  seafile_clone ; 
 int /*<<< orphan*/  seafile_destroy_repo ; 
 int /*<<< orphan*/  seafile_diff ; 
 int /*<<< orphan*/  seafile_disable_auto_sync ; 
 int /*<<< orphan*/  seafile_download ; 
 int /*<<< orphan*/  seafile_enable_auto_sync ; 
 int /*<<< orphan*/  seafile_find_transfer_task ; 
 int /*<<< orphan*/  seafile_gen_default_worktree ; 
 int /*<<< orphan*/  seafile_generate_magic_and_random_key ; 
 int /*<<< orphan*/  seafile_get_clone_tasks ; 
 int /*<<< orphan*/  seafile_get_config ; 
 int /*<<< orphan*/  seafile_get_config_int ; 
 int /*<<< orphan*/  seafile_get_download_rate ; 
 int /*<<< orphan*/  seafile_get_file_sync_errors ; 
 int /*<<< orphan*/  seafile_get_path_sync_status ; 
 int /*<<< orphan*/  seafile_get_repo ; 
 int /*<<< orphan*/  seafile_get_repo_list ; 
 int /*<<< orphan*/  seafile_get_repo_property ; 
 int /*<<< orphan*/  seafile_get_repo_sync_task ; 
 int /*<<< orphan*/  seafile_get_server_property ; 
 int /*<<< orphan*/  seafile_get_session_info ; 
 int /*<<< orphan*/  seafile_get_sync_notification ; 
 int /*<<< orphan*/  seafile_get_upload_rate ; 
 int /*<<< orphan*/  seafile_is_auto_sync_enabled ; 
 int /*<<< orphan*/  seafile_mark_file_locked ; 
 int /*<<< orphan*/  seafile_mark_file_unlocked ; 
 int /*<<< orphan*/  seafile_remove_clone_task ; 
 int /*<<< orphan*/  seafile_remove_repo_tokens_by_account ; 
 int /*<<< orphan*/  seafile_set_config ; 
 int /*<<< orphan*/  seafile_set_config_int ; 
 int /*<<< orphan*/  seafile_set_download_rate_limit ; 
 int /*<<< orphan*/  seafile_set_repo_property ; 
 int /*<<< orphan*/  seafile_set_repo_token ; 
 int /*<<< orphan*/  seafile_set_server_property ; 
 int /*<<< orphan*/  seafile_set_upload_rate_limit ; 
 int /*<<< orphan*/  seafile_shutdown ; 
 int /*<<< orphan*/  seafile_sync ; 
 int /*<<< orphan*/  seafile_sync_error_id_to_str ; 
 int /*<<< orphan*/  seafile_unsync_repos_by_account ; 
 int /*<<< orphan*/  seafile_update_repos_server_host ; 
 int /*<<< orphan*/  searpc_create_service (char*) ; 
 int /*<<< orphan*/  searpc_server_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  searpc_server_register_function (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  searpc_signature_int__int () ; 
 int /*<<< orphan*/  searpc_signature_int__string () ; 
 int /*<<< orphan*/  searpc_signature_int__string_int () ; 
 int /*<<< orphan*/  searpc_signature_int__string_string () ; 
 int /*<<< orphan*/  searpc_signature_int__string_string_string () ; 
 int /*<<< orphan*/  searpc_signature_int__void () ; 
 int /*<<< orphan*/  searpc_signature_json__void () ; 
 int /*<<< orphan*/  searpc_signature_object__int_string_string () ; 
 int /*<<< orphan*/  searpc_signature_object__string () ; 
 int /*<<< orphan*/  searpc_signature_object__void () ; 
 int /*<<< orphan*/  searpc_signature_objlist__int_int () ; 
 int /*<<< orphan*/  searpc_signature_objlist__string_string_string_int () ; 
 int /*<<< orphan*/  searpc_signature_objlist__void () ; 
 int /*<<< orphan*/  searpc_signature_string__int () ; 
 int /*<<< orphan*/  searpc_signature_string__string () ; 
 int /*<<< orphan*/  searpc_signature_string__string_int_string_string_string_string_string_string_string_string_string_string_int_string () ; 
 int /*<<< orphan*/  searpc_signature_string__string_string () ; 
 int /*<<< orphan*/  searpc_signature_string__string_string_int () ; 

__attribute__((used)) static void
register_rpc_service ()
{
    searpc_server_init (register_marshals);

    searpc_create_service ("seafile-rpcserver");
    searpc_create_service ("seafile-threaded-rpcserver");

    /* seafile-rpcserver */
    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_sync_error_id_to_str,
                                     "seafile_sync_error_id_to_str",
                                     searpc_signature_string__int());
    
    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_get_session_info,
                                     "seafile_get_session_info",
                                     searpc_signature_object__void());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_get_config,
                                     "seafile_get_config",
                                     searpc_signature_string__string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_set_config,
                                     "seafile_set_config",
                                     searpc_signature_int__string_string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_get_config_int,
                                     "seafile_get_config_int",
                                     searpc_signature_int__string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_set_config_int,
                                     "seafile_set_config_int",
                                     searpc_signature_int__string_int());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_set_upload_rate_limit,
                                     "seafile_set_upload_rate_limit",
                                     searpc_signature_int__int());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_set_download_rate_limit,
                                     "seafile_set_download_rate_limit",
                                     searpc_signature_int__int());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_unsync_repos_by_account,
                                     "seafile_unsync_repos_by_account",
                                     searpc_signature_int__string_string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_remove_repo_tokens_by_account,
                                     "seafile_remove_repo_tokens_by_account",
                                     searpc_signature_int__string_string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_set_repo_token,
                                     "seafile_set_repo_token",
                                     searpc_signature_int__string_string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_get_upload_rate,
                                     "seafile_get_upload_rate",
                                     searpc_signature_int__void());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_get_download_rate,
                                     "seafile_get_download_rate",
                                     searpc_signature_int__void());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_destroy_repo,
                                     "seafile_destroy_repo",
                                     searpc_signature_int__string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_set_repo_property,
                                     "seafile_set_repo_property",
                                     searpc_signature_int__string_string_string());
    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_get_repo_property,
                                     "seafile_get_repo_property",
                                     searpc_signature_string__string_string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_update_repos_server_host,
                                     "seafile_update_repos_server_host",
                                     searpc_signature_int__string_string_string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_disable_auto_sync,
                                     "seafile_disable_auto_sync",
                                     searpc_signature_int__void());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_enable_auto_sync,
                                     "seafile_enable_auto_sync",
                                     searpc_signature_int__void());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_is_auto_sync_enabled,
                                     "seafile_is_auto_sync_enabled",
                                     searpc_signature_int__void());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_gen_default_worktree,
                                     "gen_default_worktree",
                                     searpc_signature_string__string_string());
    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_check_path_for_clone,
                                     "seafile_check_path_for_clone",
                                     searpc_signature_int__string());

    /* clone means sync with existing folder, download means sync to a new folder. */
    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_clone,
                                     "seafile_clone",
        searpc_signature_string__string_int_string_string_string_string_string_string_string_string_string_string_int_string());
    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_download,
                                     "seafile_download",
        searpc_signature_string__string_int_string_string_string_string_string_string_string_string_string_string_int_string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_cancel_clone_task,
                                     "seafile_cancel_clone_task",
                                     searpc_signature_int__string());
    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_remove_clone_task,
                                     "seafile_remove_clone_task",
                                     searpc_signature_int__string());
    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_get_clone_tasks,
                                     "seafile_get_clone_tasks",
                                     searpc_signature_objlist__void());
    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_sync,
                                     "seafile_sync",
                                     searpc_signature_int__string_string());
    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_get_repo_list,
                                     "seafile_get_repo_list",
                                     searpc_signature_objlist__int_int());
    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_get_repo,
                                     "seafile_get_repo",
                                     searpc_signature_object__string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_get_repo_sync_task,
                                     "seafile_get_repo_sync_task",
                                     searpc_signature_object__string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_find_transfer_task,
                                     "seafile_find_transfer_task",
                                     searpc_signature_object__string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_get_path_sync_status,
                                     "seafile_get_path_sync_status",
                                     searpc_signature_string__string_string_int());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_mark_file_locked,
                                     "seafile_mark_file_locked",
                                     searpc_signature_int__string_string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_mark_file_unlocked,
                                     "seafile_mark_file_unlocked",
                                     searpc_signature_int__string_string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_generate_magic_and_random_key,
                                     "seafile_generate_magic_and_random_key",
                                     searpc_signature_object__int_string_string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_get_server_property,
                                     "seafile_get_server_property",
                                     searpc_signature_string__string_string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_set_server_property,
                                     "seafile_set_server_property",
                                     searpc_signature_int__string_string_string());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_get_file_sync_errors,
                                     "seafile_get_file_sync_errors",
                                     searpc_signature_objlist__int_int());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_get_sync_notification,
                                     "seafile_get_sync_notification",
                                     searpc_signature_json__void());

    searpc_server_register_function ("seafile-rpcserver",
                                     seafile_shutdown,
                                     "seafile_shutdown",
                                     searpc_signature_int__void());

    /* Need to run in a thread since diff may take long. */
    searpc_server_register_function ("seafile-threaded-rpcserver",
                                     seafile_diff,
                                     "seafile_diff",
                                     searpc_signature_objlist__string_string_string_int());
}