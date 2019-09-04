#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct HelloTypeObject {struct HelloTypeNode* head; } ;
struct HelloTypeNode {struct HelloTypeNode* next; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  RedisModuleDigest ;

/* Variables and functions */
 int /*<<< orphan*/  RedisModule_DigestAddLongLong (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_DigestEndSequence (int /*<<< orphan*/ *) ; 

void HelloTypeDigest(RedisModuleDigest *md, void *value) {
    struct HelloTypeObject *hto = value;
    struct HelloTypeNode *node = hto->head;
    while(node) {
        RedisModule_DigestAddLongLong(md,node->value);
        node = node->next;
    }
    RedisModule_DigestEndSequence(md);
}