#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char* sds ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
typedef  TYPE_2__ clusterManagerNode ;
struct TYPE_5__ {int /*<<< orphan*/  backup_dir; } ;
struct TYPE_7__ {TYPE_1__ cluster_manager_command; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__ config ; 
 char* sdscat (char*,char*) ; 
 char* sdscatprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sdslen (char*) ; 
 char* sdsnew (int /*<<< orphan*/ ) ; 

__attribute__((used)) static sds clusterManagerGetNodeRDBFilename(clusterManagerNode *node) {
    assert(config.cluster_manager_command.backup_dir);
    sds filename = sdsnew(config.cluster_manager_command.backup_dir);
    if (filename[sdslen(filename) - 1] != '/')
        filename = sdscat(filename, "/");
    filename = sdscatprintf(filename, "redis-node-%s-%d-%s.rdb", node->ip,
                            node->port, node->name);
    return filename;
}