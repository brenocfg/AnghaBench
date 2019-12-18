#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_4__ {scalar_t__ status; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ DiffEntry ;

/* Variables and functions */
 scalar_t__ DIFF_STATUS_ADDED ; 
 scalar_t__ DIFF_STATUS_DELETED ; 
 scalar_t__ DIFF_STATUS_DIR_ADDED ; 
 scalar_t__ DIFF_STATUS_DIR_DELETED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static gboolean
is_redundant_empty_dir (DiffEntry *de_dir, DiffEntry *de_file)
{
    int dir_len;

    if (de_dir->status == DIFF_STATUS_DIR_ADDED &&
        de_file->status == DIFF_STATUS_DELETED)
    {
        dir_len = strlen (de_dir->name);
        if (strlen (de_file->name) > dir_len &&
            strncmp (de_dir->name, de_file->name, dir_len) == 0)
            return TRUE;
    }

    if (de_dir->status == DIFF_STATUS_DIR_DELETED &&
        de_file->status == DIFF_STATUS_ADDED)
    {
        dir_len = strlen (de_dir->name);
        if (strlen (de_file->name) > dir_len &&
            strncmp (de_dir->name, de_file->name, dir_len) == 0)
            return TRUE;
    }

    return FALSE;
}