#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_5__ {int /*<<< orphan*/  seaf_dir; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  G_FILE_TEST_IS_DIR ; 
 int /*<<< orphan*/  TRUE ; 
 char* g_build_filename (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ g_file_test (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 TYPE_2__* seaf ; 

__attribute__((used)) static gboolean
repo_block_store_exists (SeafRepo *repo)
{
    gboolean ret;
    char *store_path = g_build_filename (seaf->seaf_dir, "storage", "blocks",
                                         repo->id, NULL);
    if (g_file_test (store_path, G_FILE_TEST_IS_DIR))
        ret = TRUE;
    else
        ret = FALSE;
    g_free (store_path);
    return ret;
}