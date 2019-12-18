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
struct TYPE_3__ {int /*<<< orphan*/  priv; } ;
typedef  TYPE_1__ ObjBackend ;

/* Variables and functions */
 int /*<<< orphan*/  CreateHardLink (char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  G_FILE_TEST_EXISTS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int SEAF_PATH_MAX ; 
 scalar_t__ create_parent_path (char*) ; 
 scalar_t__ errno ; 
 scalar_t__ g_file_test (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  id_to_path (int /*<<< orphan*/ ,char const*,char*,char const*,int) ; 
 int link (char*,char*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char*,char const*,...) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static int
obj_backend_fs_copy (ObjBackend *bend,
                     const char *src_repo_id,
                     int src_version,
                     const char *dst_repo_id,
                     int dst_version,
                     const char *obj_id)
{
    char src_path[SEAF_PATH_MAX];
    char dst_path[SEAF_PATH_MAX];

    id_to_path (bend->priv, obj_id, src_path, src_repo_id, src_version);
    id_to_path (bend->priv, obj_id, dst_path, dst_repo_id, dst_version);

    if (g_file_test (dst_path, G_FILE_TEST_EXISTS))
        return 0;

    if (create_parent_path (dst_path) < 0) {
        seaf_warning ("Failed to create dst path %s for obj %s.\n",
                      dst_path, obj_id);
        return -1;
    }

#ifdef WIN32
    if (!CreateHardLink (dst_path, src_path, NULL)) {
        seaf_warning ("Failed to link %s to %s: %lu.\n",
                      src_path, dst_path, GetLastError());
        return -1;
    }
    return 0;
#else
    int ret = link (src_path, dst_path);
    if (ret < 0 && errno != EEXIST) {
        seaf_warning ("Failed to link %s to %s: %s.\n",
                      src_path, dst_path, strerror(errno));
        return -1;
    }
    return ret;
#endif
}