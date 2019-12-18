#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sds ;
struct TYPE_2__ {int /*<<< orphan*/ * errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  clusterManagerLogErr (char*,char*) ; 
 TYPE_1__ cluster_manager ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * listCreate () ; 

__attribute__((used)) static void clusterManagerOnError(sds err) {
    if (cluster_manager.errors == NULL)
        cluster_manager.errors = listCreate();
    listAddNodeTail(cluster_manager.errors, err);
    clusterManagerLogErr("%s\n", (char *) err);
}