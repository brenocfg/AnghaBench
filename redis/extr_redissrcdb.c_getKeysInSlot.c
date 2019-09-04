#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
struct TYPE_9__ {unsigned char* key; scalar_t__ key_len; } ;
typedef  TYPE_2__ raxIterator ;
struct TYPE_10__ {TYPE_1__* cluster; } ;
struct TYPE_8__ {int /*<<< orphan*/  slots_to_keys; } ;

/* Variables and functions */
 int /*<<< orphan*/ * createStringObject (char*,scalar_t__) ; 
 scalar_t__ raxNext (TYPE_2__*) ; 
 int /*<<< orphan*/  raxSeek (TYPE_2__*,char*,unsigned char*,int) ; 
 int /*<<< orphan*/  raxStart (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raxStop (TYPE_2__*) ; 
 TYPE_3__ server ; 

unsigned int getKeysInSlot(unsigned int hashslot, robj **keys, unsigned int count) {
    raxIterator iter;
    int j = 0;
    unsigned char indexed[2];

    indexed[0] = (hashslot >> 8) & 0xff;
    indexed[1] = hashslot & 0xff;
    raxStart(&iter,server.cluster->slots_to_keys);
    raxSeek(&iter,">=",indexed,2);
    while(count-- && raxNext(&iter)) {
        if (iter.key[0] != indexed[0] || iter.key[1] != indexed[1]) break;
        keys[j++] = createStringObject((char*)iter.key+2,iter.key_len-2);
    }
    raxStop(&iter);
    return j;
}