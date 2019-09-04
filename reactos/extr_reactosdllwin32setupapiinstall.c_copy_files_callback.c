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
struct files_callback_info {int /*<<< orphan*/  copy_flags; scalar_t__ layout; int /*<<< orphan*/  src_root; int /*<<< orphan*/  queue; } ;
typedef  char* PCWSTR ;
typedef  scalar_t__ HINF ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  SetupQueueCopySectionW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupQueueDefaultCopyW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL copy_files_callback( HINF hinf, PCWSTR field, void *arg )
{
    struct files_callback_info *info = arg;

    if (field[0] == '@')  /* special case: copy single file */
        SetupQueueDefaultCopyW( info->queue, info->layout ? info->layout : hinf, info->src_root, NULL, field+1, info->copy_flags );
    else
        SetupQueueCopySectionW( info->queue, info->src_root, info->layout ? info->layout : hinf, hinf, field, info->copy_flags );
    return TRUE;
}