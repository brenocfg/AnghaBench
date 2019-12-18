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
struct HelloTypeObject {int len; struct HelloTypeNode* head; } ;
struct HelloTypeNode {int dummy; } ;

/* Variables and functions */

size_t HelloTypeMemUsage(const void *value) {
    const struct HelloTypeObject *hto = value;
    struct HelloTypeNode *node = hto->head;
    return sizeof(*hto) + sizeof(*node)*hto->len;
}