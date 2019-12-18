#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ robj ;
struct TYPE_7__ {TYPE_1__* cluster; } ;
struct TYPE_5__ {int* slots_keys_count; int /*<<< orphan*/  slots_to_keys; } ;

/* Variables and functions */
 unsigned int keyHashSlot (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  raxInsert (int /*<<< orphan*/ ,unsigned char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raxRemove (int /*<<< orphan*/ ,unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 size_t sdslen (int /*<<< orphan*/ ) ; 
 TYPE_4__ server ; 
 int /*<<< orphan*/  zfree (unsigned char*) ; 
 unsigned char* zmalloc (size_t) ; 

void slotToKeyUpdateKey(robj *key, int add) {
    unsigned int hashslot = keyHashSlot(key->ptr,sdslen(key->ptr));
    unsigned char buf[64];
    unsigned char *indexed = buf;
    size_t keylen = sdslen(key->ptr);

    server.cluster->slots_keys_count[hashslot] += add ? 1 : -1;
    if (keylen+2 > 64) indexed = zmalloc(keylen+2);
    indexed[0] = (hashslot >> 8) & 0xff;
    indexed[1] = hashslot & 0xff;
    memcpy(indexed+2,key->ptr,keylen);
    if (add) {
        raxInsert(server.cluster->slots_to_keys,indexed,keylen+2,NULL,NULL);
    } else {
        raxRemove(server.cluster->slots_to_keys,indexed,keylen+2,NULL);
    }
    if (indexed != buf) zfree(indexed);
}