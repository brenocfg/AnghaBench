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
typedef  int /*<<< orphan*/  BlockUploadTask ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
block_upload_task_free (BlockUploadTask *task)
{
    g_free (task);
}