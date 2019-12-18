#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  modifier; int /*<<< orphan*/  mode; int /*<<< orphan*/  mtime; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  modifier; int /*<<< orphan*/  mode; int /*<<< orphan*/  mtime; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  SeafFSManager ;
typedef  TYPE_1__ SeafDirent ;
typedef  int /*<<< orphan*/  GList ;
typedef  TYPE_2__ DiffEntry ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_STATUS_ADDED ; 
 int /*<<< orphan*/  DIFF_STATUS_DIR_ADDED ; 
 int /*<<< orphan*/  DIFF_TYPE_COMMITS ; 
 int /*<<< orphan*/  EMPTY_SHA1 ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* diff_entry_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,char const*) ; 
 int /*<<< orphan*/ * g_list_prepend (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  g_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hex_to_rawdata (int /*<<< orphan*/ ,unsigned char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean
expand_dir_added_cb (SeafFSManager *mgr,
                     const char *path,
                     SeafDirent *dent,
                     void *user_data,
                     gboolean *stop)
{
    GList **expanded = user_data;
    DiffEntry *de = NULL;
    unsigned char sha1[20];

    hex_to_rawdata (dent->id, sha1, 20);

    if (S_ISDIR(dent->mode) && strcmp(dent->id, EMPTY_SHA1) == 0)
        de = diff_entry_new (DIFF_TYPE_COMMITS, DIFF_STATUS_DIR_ADDED, sha1, path);
    else if (S_ISREG(dent->mode))
        de = diff_entry_new (DIFF_TYPE_COMMITS, DIFF_STATUS_ADDED, sha1, path);

    if (de) {
        de->mtime = dent->mtime;
        de->mode = dent->mode;
        de->modifier = g_strdup(dent->modifier);
        de->size = dent->size;
        *expanded = g_list_prepend (*expanded, de);
    }

    return TRUE;
}