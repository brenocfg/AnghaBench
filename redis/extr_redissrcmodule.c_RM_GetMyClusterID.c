#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* cluster; int /*<<< orphan*/  cluster_enabled; } ;
struct TYPE_5__ {TYPE_1__* myself; } ;
struct TYPE_4__ {char const* name; } ;

/* Variables and functions */
 TYPE_3__ server ; 

const char *RM_GetMyClusterID(void) {
    if (!server.cluster_enabled) return NULL;
    return server.cluster->myself->name;
}