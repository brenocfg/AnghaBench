#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ cluster_manager_command; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_MANAGER_CMD_FLAG_FIX ; 
 int clusterManagerCommandCheck (int,char**) ; 
 TYPE_2__ config ; 

__attribute__((used)) static int clusterManagerCommandFix(int argc, char **argv) {
    config.cluster_manager_command.flags |= CLUSTER_MANAGER_CMD_FLAG_FIX;
    return clusterManagerCommandCheck(argc, argv);
}