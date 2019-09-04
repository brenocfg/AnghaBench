#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; scalar_t__ usage_start; int /*<<< orphan*/  stripes_end; int /*<<< orphan*/  stripes_start; scalar_t__ limit_end; scalar_t__ limit_start; int /*<<< orphan*/  convert; int /*<<< orphan*/  vrange_end; int /*<<< orphan*/  vrange_start; int /*<<< orphan*/  drange_end; int /*<<< orphan*/  drange_start; int /*<<< orphan*/  devid; int /*<<< orphan*/  usage_end; int /*<<< orphan*/  profiles; } ;
typedef  TYPE_1__ btrfs_balance_opts ;
typedef  void* UINT32 ;
struct TYPE_6__ {scalar_t__ usage_start; scalar_t__ limit_start; int /*<<< orphan*/  flags; int /*<<< orphan*/  stripes_end; int /*<<< orphan*/  stripes_start; scalar_t__ limit; void* limit_end; int /*<<< orphan*/  convert; int /*<<< orphan*/  vrange_end; int /*<<< orphan*/  vrange_start; int /*<<< orphan*/  drange_end; int /*<<< orphan*/  drange_start; int /*<<< orphan*/  devid; int /*<<< orphan*/  usage; int /*<<< orphan*/  usage_end; int /*<<< orphan*/  profiles; } ;
typedef  TYPE_2__ BALANCE_ARGS ;

/* Variables and functions */
 int /*<<< orphan*/  BALANCE_ARGS_FLAGS_CONVERT ; 
 int /*<<< orphan*/  BALANCE_ARGS_FLAGS_DEVID ; 
 int /*<<< orphan*/  BALANCE_ARGS_FLAGS_DRANGE ; 
 int /*<<< orphan*/  BALANCE_ARGS_FLAGS_LIMIT ; 
 int /*<<< orphan*/  BALANCE_ARGS_FLAGS_LIMIT_RANGE ; 
 int /*<<< orphan*/  BALANCE_ARGS_FLAGS_PROFILES ; 
 int /*<<< orphan*/  BALANCE_ARGS_FLAGS_SOFT ; 
 int /*<<< orphan*/  BALANCE_ARGS_FLAGS_STRIPES_RANGE ; 
 int /*<<< orphan*/  BALANCE_ARGS_FLAGS_USAGE ; 
 int /*<<< orphan*/  BALANCE_ARGS_FLAGS_USAGE_RANGE ; 
 int /*<<< orphan*/  BALANCE_ARGS_FLAGS_VRANGE ; 
 int BTRFS_BALANCE_OPTS_CONVERT ; 
 int BTRFS_BALANCE_OPTS_DEVID ; 
 int BTRFS_BALANCE_OPTS_DRANGE ; 
 int BTRFS_BALANCE_OPTS_LIMIT ; 
 int BTRFS_BALANCE_OPTS_PROFILES ; 
 int BTRFS_BALANCE_OPTS_SOFT ; 
 int BTRFS_BALANCE_OPTS_STRIPES ; 
 int BTRFS_BALANCE_OPTS_USAGE ; 
 int BTRFS_BALANCE_OPTS_VRANGE ; 

__attribute__((used)) static void copy_balance_args(btrfs_balance_opts* opts, BALANCE_ARGS* args) {
    if (opts->flags & BTRFS_BALANCE_OPTS_PROFILES) {
        args->profiles = opts->profiles;
        args->flags |= BALANCE_ARGS_FLAGS_PROFILES;
    }

    if (opts->flags & BTRFS_BALANCE_OPTS_USAGE) {
        if (args->usage_start == 0) {
            args->flags |= BALANCE_ARGS_FLAGS_USAGE_RANGE;
            args->usage_start = opts->usage_start;
            args->usage_end = opts->usage_end;
        } else {
            args->flags |= BALANCE_ARGS_FLAGS_USAGE;
            args->usage = opts->usage_end;
        }
    }

    if (opts->flags & BTRFS_BALANCE_OPTS_DEVID) {
        args->devid = opts->devid;
        args->flags |= BALANCE_ARGS_FLAGS_DEVID;
    }

    if (opts->flags & BTRFS_BALANCE_OPTS_DRANGE) {
        args->drange_start = opts->drange_start;
        args->drange_end = opts->drange_end;
        args->flags |= BALANCE_ARGS_FLAGS_DRANGE;
    }

    if (opts->flags & BTRFS_BALANCE_OPTS_VRANGE) {
        args->vrange_start = opts->vrange_start;
        args->vrange_end = opts->vrange_end;
        args->flags |= BALANCE_ARGS_FLAGS_VRANGE;
    }

    if (opts->flags & BTRFS_BALANCE_OPTS_CONVERT) {
        args->convert = opts->convert;
        args->flags |= BALANCE_ARGS_FLAGS_CONVERT;

        if (opts->flags & BTRFS_BALANCE_OPTS_SOFT)
            args->flags |= BALANCE_ARGS_FLAGS_SOFT;
    }

    if (opts->flags & BTRFS_BALANCE_OPTS_LIMIT) {
        if (args->limit_start == 0) {
            args->flags |= BALANCE_ARGS_FLAGS_LIMIT_RANGE;
            args->limit_start = (UINT32)opts->limit_start;
            args->limit_end = (UINT32)opts->limit_end;
        } else {
            args->flags |= BALANCE_ARGS_FLAGS_LIMIT;
            args->limit = opts->limit_end;
        }
    }

    if (opts->flags & BTRFS_BALANCE_OPTS_STRIPES) {
        args->stripes_start = opts->stripes_start;
        args->stripes_end = opts->stripes_end;
        args->flags |= BALANCE_ARGS_FLAGS_STRIPES_RANGE;
    }
}