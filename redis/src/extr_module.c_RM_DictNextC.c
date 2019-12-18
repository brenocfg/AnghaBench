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
struct TYPE_5__ {size_t key_len; void* key; void* data; } ;
struct TYPE_4__ {TYPE_2__ ri; } ;
typedef  TYPE_1__ RedisModuleDictIter ;

/* Variables and functions */
 int /*<<< orphan*/  raxNext (TYPE_2__*) ; 

void *RM_DictNextC(RedisModuleDictIter *di, size_t *keylen, void **dataptr) {
    if (!raxNext(&di->ri)) return NULL;
    if (keylen) *keylen = di->ri.key_len;
    if (dataptr) *dataptr = di->ri.data;
    return di->ri.key;
}