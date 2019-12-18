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
struct TYPE_3__ {char* obj_dir; char const* v0_obj_dir; int v0_dir_len; } ;
typedef  TYPE_1__ FsPriv ;

/* Variables and functions */
 int /*<<< orphan*/  SEAF_PATH_MAX ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,char*,char const*) ; 

__attribute__((used)) static void
id_to_path (FsPriv *priv, const char *obj_id, char path[],
            const char *repo_id, int version)
{
    char *pos = path;
    int n;

#if defined MIGRATION || defined SEAFILE_CLIENT
    if (version > 0) {
        n = snprintf (path, SEAF_PATH_MAX, "%s/%s/", priv->obj_dir, repo_id);
        pos += n;
    } else {
        memcpy (pos, priv->v0_obj_dir, priv->v0_dir_len);
        pos[priv->v0_dir_len] = '/';
        pos += priv->v0_dir_len + 1;
    }
#else
    n = snprintf (path, SEAF_PATH_MAX, "%s/%s/", priv->obj_dir, repo_id);
    pos += n;
#endif

    memcpy (pos, obj_id, 2);
    pos[2] = '/';
    pos += 3;

    memcpy (pos, obj_id + 2, 41 - 2);
}