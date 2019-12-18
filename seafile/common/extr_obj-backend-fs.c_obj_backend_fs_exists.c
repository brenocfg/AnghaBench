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
typedef  int /*<<< orphan*/  SeafStat ;
typedef  TYPE_1__ ObjBackend ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SEAF_PATH_MAX ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  id_to_path (int /*<<< orphan*/ ,char const*,char*,char const*,int) ; 
 scalar_t__ seaf_stat (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static gboolean
obj_backend_fs_exists (ObjBackend *bend,
                       const char *repo_id,
                       int version,
                       const char *obj_id)
{
    char path[SEAF_PATH_MAX];
    SeafStat st;

    id_to_path (bend->priv, obj_id, path, repo_id, version);

    if (seaf_stat (path, &st) == 0)
        return TRUE;

    return FALSE;
}