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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * link; } ;
typedef  TYPE_1__ clusterNode ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 TYPE_1__* clusterLookupNode (char const*) ; 
 int /*<<< orphan*/  clusterSendModule (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 

int clusterSendModuleMessageToTarget(const char *target, uint64_t module_id, uint8_t type, unsigned char *payload, uint32_t len) {
    clusterNode *node = NULL;

    if (target != NULL) {
        node = clusterLookupNode(target);
        if (node == NULL || node->link == NULL) return C_ERR;
    }

    clusterSendModule(target ? node->link : NULL,
                      module_id, type, payload, len);
    return C_OK;
}