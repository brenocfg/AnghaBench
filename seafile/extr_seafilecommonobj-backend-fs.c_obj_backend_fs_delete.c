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
 int SEAF_PATH_MAX ; 
 int /*<<< orphan*/  g_unlink (char*) ; 
 int /*<<< orphan*/  id_to_path (int /*<<< orphan*/ ,char const*,char*,char const*,int) ; 

__attribute__((used)) static void
obj_backend_fs_delete (ObjBackend *bend,
                       const char *repo_id,
                       int version,
                       const char *obj_id)
{
    char path[SEAF_PATH_MAX];

    id_to_path (bend->priv, obj_id, path, repo_id, version);
    g_unlink (path);
}