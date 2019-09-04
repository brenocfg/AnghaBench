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
struct HelloTypeObject {int /*<<< orphan*/  len; struct HelloTypeNode* head; } ;
struct HelloTypeNode {struct HelloTypeNode* next; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  RedisModuleIO ;

/* Variables and functions */
 int /*<<< orphan*/  RedisModule_SaveSigned (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_SaveUnsigned (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void HelloTypeRdbSave(RedisModuleIO *rdb, void *value) {
    struct HelloTypeObject *hto = value;
    struct HelloTypeNode *node = hto->head;
    RedisModule_SaveUnsigned(rdb,hto->len);
    while(node) {
        RedisModule_SaveSigned(rdb,node->value);
        node = node->next;
    }
}