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
struct TYPE_3__ {int /*<<< orphan*/  priv; } ;
typedef  TYPE_1__ ObjBackend ;

/* Variables and functions */
 int SEAF_PATH_MAX ; 
 scalar_t__ create_parent_path (char*) ; 
 int /*<<< orphan*/  id_to_path (int /*<<< orphan*/ ,char const*,char*,char const*,int) ; 
 scalar_t__ save_obj_contents (char*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,char const*) ; 

__attribute__((used)) static int
obj_backend_fs_write (ObjBackend *bend,
                      const char *repo_id,
                      int version,
                      const char *obj_id,
                      void *data,
                      int len,
                      gboolean need_sync)
{
    char path[SEAF_PATH_MAX];

    id_to_path (bend->priv, obj_id, path, repo_id, version);

    /* GTimeVal s, e; */

    /* g_get_current_time (&s); */

    if (create_parent_path (path) < 0) {
        seaf_warning ("[obj backend] Failed to create path for obj %s:%s.\n",
                      repo_id, obj_id);
        return -1;
    }

    if (save_obj_contents (path, data, len, need_sync) < 0) {
        seaf_warning ("[obj backend] Failed to write obj %s:%s.\n",
                      repo_id, obj_id);
        return -1;
    }

    /* g_get_current_time (&e); */

    /* seaf_message ("write obj time: %ldus.\n", */
    /*               ((e.tv_sec*1000000+e.tv_usec) - (s.tv_sec*1000000+s.tv_usec))); */

    return 0;
}