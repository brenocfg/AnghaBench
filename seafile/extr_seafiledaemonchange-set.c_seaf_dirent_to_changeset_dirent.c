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
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  modifier; int /*<<< orphan*/  mtime; int /*<<< orphan*/  name; int /*<<< orphan*/  mode; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ SeafDirent ;
typedef  int /*<<< orphan*/  ChangeSetDirent ;

/* Variables and functions */
 int /*<<< orphan*/ * changeset_dirent_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ChangeSetDirent *
seaf_dirent_to_changeset_dirent (SeafDirent *seaf_dent)
{
    return changeset_dirent_new (seaf_dent->id, seaf_dent->mode, seaf_dent->name,
                                 seaf_dent->mtime, seaf_dent->modifier, seaf_dent->size);
}