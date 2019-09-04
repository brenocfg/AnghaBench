#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  size_t hash_t ;
struct TYPE_10__ {TYPE_3__* list; } ;
typedef  TYPE_2__ candidates_bucket ;
typedef  size_t bucket_t ;
struct TYPE_12__ {size_t candidates_bucket_size; TYPE_2__* candidates; } ;
struct TYPE_9__ {int /*<<< orphan*/  public_key; } ;
struct TYPE_11__ {size_t hash; TYPE_1__ client; } ;
typedef  TYPE_3__ Client_entry ;
typedef  TYPE_4__ Assoc ;

/* Variables and functions */
 size_t HASH_COLLIDE_COUNT ; 
 size_t candidates_id_bucket (TYPE_4__ const*,int const*) ; 
 size_t hash_collide (TYPE_4__ const*,size_t) ; 
 scalar_t__ id_equal (int /*<<< orphan*/ ,int const*) ; 

__attribute__((used)) static uint8_t candidates_search(const Assoc *assoc, const uint8_t *id, hash_t hash, Client_entry **entryptr)
{
    bucket_t bucket = candidates_id_bucket(assoc, id);
    candidates_bucket *cnd_bckt = &assoc->candidates[bucket];
    size_t coll, pos = hash % assoc->candidates_bucket_size;

    for (coll = 0; coll < HASH_COLLIDE_COUNT; pos = hash_collide(assoc, pos) , coll++) {
        Client_entry *entry = &cnd_bckt->list[pos];

        if (entry->hash == hash)
            if (id_equal(entry->client.public_key, id)) {
                *entryptr = entry;
                return 1;
            }
    }

    *entryptr = NULL;
    return 0;
}