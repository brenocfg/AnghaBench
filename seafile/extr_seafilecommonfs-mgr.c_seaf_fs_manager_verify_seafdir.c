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
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_3__ {int /*<<< orphan*/  obj_store; } ;
typedef  TYPE_1__ SeafFSManager ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_SHA1 ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (void*) ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ seaf_obj_store_read_obj (int /*<<< orphan*/ ,char const*,int,char const*,void**,int*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,char const*) ; 
 int /*<<< orphan*/  verify_seafdir (char const*,void*,int,int /*<<< orphan*/ ,int) ; 

gboolean
seaf_fs_manager_verify_seafdir (SeafFSManager *mgr,
                                const char *repo_id,
                                int version,
                                const char *dir_id,
                                gboolean verify_id,
                                gboolean *io_error)
{
    void *data;
    int len;

    if (memcmp (dir_id, EMPTY_SHA1, 40) == 0) {
        return TRUE;
    }

    if (seaf_obj_store_read_obj (mgr->obj_store, repo_id, version,
                                 dir_id, &data, &len) < 0) {
        seaf_warning ("[fs mgr] Failed to read dir %s:%s.\n", repo_id, dir_id);
        *io_error = TRUE;
        return FALSE;
    }

    gboolean ret = verify_seafdir (dir_id, data, len, verify_id, (version > 0));
    g_free (data);

    return ret;
}