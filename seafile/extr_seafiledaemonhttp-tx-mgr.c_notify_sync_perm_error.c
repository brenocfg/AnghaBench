#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  repo_name; int /*<<< orphan*/  repo_id; } ;
typedef  TYPE_1__ HttpTxTask ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_ERROR_ID_PERM_NOT_SYNCABLE ; 
 int /*<<< orphan*/  send_file_sync_error_notification (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
notify_sync_perm_error (HttpTxTask *task, const char *unsyncable_path)
{

    send_file_sync_error_notification (task->repo_id, task->repo_name,
                                       unsyncable_path, SYNC_ERROR_ID_PERM_NOT_SYNCABLE);

}