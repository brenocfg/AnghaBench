#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* ip; int port; float weight; scalar_t__ balance; scalar_t__ replicas_count; scalar_t__ importing_count; scalar_t__ migrating_count; int /*<<< orphan*/ * importing; int /*<<< orphan*/ * migrating; int /*<<< orphan*/ * friends; scalar_t__ dirty; int /*<<< orphan*/ * replicate; int /*<<< orphan*/ * flags_str; scalar_t__ flags; scalar_t__ ping_recv; scalar_t__ ping_sent; scalar_t__ current_epoch; int /*<<< orphan*/ * name; int /*<<< orphan*/ * context; } ;
typedef  TYPE_1__ clusterManagerNode ;

/* Variables and functions */
 int /*<<< orphan*/  clusterManagerNodeResetSlots (TYPE_1__*) ; 
 TYPE_1__* zmalloc (int) ; 

__attribute__((used)) static clusterManagerNode *clusterManagerNewNode(char *ip, int port) {
    clusterManagerNode *node = zmalloc(sizeof(*node));
    node->context = NULL;
    node->name = NULL;
    node->ip = ip;
    node->port = port;
    node->current_epoch = 0;
    node->ping_sent = 0;
    node->ping_recv = 0;
    node->flags = 0;
    node->flags_str = NULL;
    node->replicate = NULL;
    node->dirty = 0;
    node->friends = NULL;
    node->migrating = NULL;
    node->importing = NULL;
    node->migrating_count = 0;
    node->importing_count = 0;
    node->replicas_count = 0;
    node->weight = 1.0f;
    node->balance = 0;
    clusterManagerNodeResetSlots(node);
    return node;
}