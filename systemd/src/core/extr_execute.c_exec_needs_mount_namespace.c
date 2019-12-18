#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ n_bind_mounts; scalar_t__ n_temporary_filesystems; scalar_t__ protect_system; scalar_t__ protect_home; TYPE_1__* directories; scalar_t__ dynamic_user; int /*<<< orphan*/ * prefix; scalar_t__ mount_apivfs; scalar_t__ root_directory; scalar_t__ protect_control_groups; scalar_t__ protect_kernel_logs; scalar_t__ protect_kernel_modules; scalar_t__ protect_kernel_tunables; scalar_t__ private_mounts; scalar_t__ private_devices; scalar_t__ private_tmp; int /*<<< orphan*/  mount_flags; int /*<<< orphan*/  inaccessible_paths; int /*<<< orphan*/  read_only_paths; int /*<<< orphan*/  read_write_paths; scalar_t__ root_image; } ;
struct TYPE_10__ {scalar_t__ var_tmp_dir; scalar_t__ tmp_dir; } ;
struct TYPE_9__ {int /*<<< orphan*/  paths; } ;
typedef  TYPE_2__ ExecRuntime ;
typedef  TYPE_3__ ExecParameters ;
typedef  size_t ExecDirectoryType ;
typedef  TYPE_3__ ExecContext ;

/* Variables and functions */
 size_t EXEC_DIRECTORY_CACHE ; 
 size_t EXEC_DIRECTORY_LOGS ; 
 size_t EXEC_DIRECTORY_STATE ; 
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MS_SHARED ; 
 scalar_t__ PROTECT_HOME_NO ; 
 scalar_t__ PROTECT_SYSTEM_NO ; 
 size_t _EXEC_DIRECTORY_TYPE_MAX ; 
 int /*<<< orphan*/  assert (TYPE_3__ const*) ; 
 int /*<<< orphan*/  strv_isempty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool exec_needs_mount_namespace(
                const ExecContext *context,
                const ExecParameters *params,
                const ExecRuntime *runtime) {

        assert(context);
        assert(params);

        if (context->root_image)
                return true;

        if (!strv_isempty(context->read_write_paths) ||
            !strv_isempty(context->read_only_paths) ||
            !strv_isempty(context->inaccessible_paths))
                return true;

        if (context->n_bind_mounts > 0)
                return true;

        if (context->n_temporary_filesystems > 0)
                return true;

        if (!IN_SET(context->mount_flags, 0, MS_SHARED))
                return true;

        if (context->private_tmp && runtime && (runtime->tmp_dir || runtime->var_tmp_dir))
                return true;

        if (context->private_devices ||
            context->private_mounts ||
            context->protect_system != PROTECT_SYSTEM_NO ||
            context->protect_home != PROTECT_HOME_NO ||
            context->protect_kernel_tunables ||
            context->protect_kernel_modules ||
            context->protect_kernel_logs ||
            context->protect_control_groups)
                return true;

        if (context->root_directory) {
                ExecDirectoryType t;

                if (context->mount_apivfs)
                        return true;

                for (t = 0; t < _EXEC_DIRECTORY_TYPE_MAX; t++) {
                        if (!params->prefix[t])
                                continue;

                        if (!strv_isempty(context->directories[t].paths))
                                return true;
                }
        }

        if (context->dynamic_user &&
            (!strv_isempty(context->directories[EXEC_DIRECTORY_STATE].paths) ||
             !strv_isempty(context->directories[EXEC_DIRECTORY_CACHE].paths) ||
             !strv_isempty(context->directories[EXEC_DIRECTORY_LOGS].paths)))
                return true;

        return false;
}