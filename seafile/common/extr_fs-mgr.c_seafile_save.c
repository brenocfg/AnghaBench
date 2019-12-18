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
typedef  int /*<<< orphan*/  guint8 ;
struct TYPE_7__ {int /*<<< orphan*/  obj_store; } ;
struct TYPE_6__ {int /*<<< orphan*/  file_id; } ;
typedef  TYPE_1__ Seafile ;
typedef  TYPE_2__ SeafFSManager ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 scalar_t__ seaf_obj_store_write_obj (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * seafile_to_data (TYPE_1__*,int*) ; 

int
seafile_save (SeafFSManager *fs_mgr,
              const char *repo_id,
              int version,
              Seafile *file)
{
    guint8 *data;
    int len;
    int ret = 0;

    data = seafile_to_data (file, &len);
    if (!data)
        return -1;

    if (seaf_obj_store_write_obj (fs_mgr->obj_store, repo_id, version, file->file_id,
                                  data, len, FALSE) < 0)
        ret = -1;

    g_free (data);
    return ret;
}