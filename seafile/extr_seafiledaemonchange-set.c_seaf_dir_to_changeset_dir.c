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
struct TYPE_3__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  dir_id; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ SeafDir ;
typedef  int /*<<< orphan*/  ChangeSetDir ;

/* Variables and functions */
 int /*<<< orphan*/ * changeset_dir_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ChangeSetDir *
seaf_dir_to_changeset_dir (SeafDir *seaf_dir)
{
    return changeset_dir_new (seaf_dir->version, seaf_dir->dir_id, seaf_dir->entries);
}