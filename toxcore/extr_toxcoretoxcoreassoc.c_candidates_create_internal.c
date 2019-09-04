#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  pos_check ;
typedef  size_t hash_t ;
struct TYPE_7__ {TYPE_2__* list; } ;
typedef  TYPE_1__ candidates_bucket ;
typedef  size_t bucket_t ;
struct TYPE_9__ {size_t const candidates_bucket_size; TYPE_1__* candidates; } ;
struct TYPE_8__ {int /*<<< orphan*/  heard_at; int /*<<< orphan*/  seen_at; int /*<<< orphan*/  used_at; int /*<<< orphan*/  hash; } ;
typedef  TYPE_2__ Client_entry ;
typedef  TYPE_3__ Assoc ;

/* Variables and functions */
 size_t BAD ; 
 int /*<<< orphan*/  BAD_NODE_TIMEOUT ; 
 int /*<<< orphan*/  CANDIDATES_HEARD_TIMEOUT ; 
 int /*<<< orphan*/  CANDIDATES_SEEN_TIMEOUT ; 
 size_t HASH_COLLIDE_COUNT ; 
 size_t SEENB_HEARDG ; 
 size_t SEENG ; 
 size_t USED ; 
 size_t candidates_id_bucket (TYPE_3__ const*,int const*) ; 
 size_t hash_collide (TYPE_3__ const*,size_t) ; 
 int /*<<< orphan*/  is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint8_t candidates_create_internal(const Assoc *assoc, hash_t const hash, const uint8_t *id, uint8_t seen,
        uint8_t used, bucket_t *bucketptr, size_t *posptr)
{
    if (!assoc || !id || !bucketptr ||  !posptr)
        return 0;

    bucket_t bucket = candidates_id_bucket(assoc, id);
    candidates_bucket *cnd_bckt = &assoc->candidates[bucket];

    size_t coll, pos = hash % assoc->candidates_bucket_size, check;
    size_t pos_check[6];

    memset(pos_check, 0, sizeof(pos_check));

    for (coll = 0; coll < HASH_COLLIDE_COUNT; pos = hash_collide(assoc, pos) , coll++) {
        Client_entry *entry = &cnd_bckt->list[pos];

        /* unset */
        if (!entry->hash) {
            *bucketptr = bucket;
            *posptr = pos;

            return 1;
        }

        /* 0. bad
         * 1. seen bad, heard good
         * 2. seen good
         * 3. used */
        // enumerated lists are superior to magic numbers
        if (!is_timeout(entry->used_at, BAD_NODE_TIMEOUT))
            check = USED;
        else if (!is_timeout(entry->seen_at, CANDIDATES_SEEN_TIMEOUT))
            check = SEENG;
        else if (!is_timeout(entry->heard_at, CANDIDATES_HEARD_TIMEOUT))
            check = SEENB_HEARDG;
        else
            check = BAD;

        if (!pos_check[check])
            pos_check[check] = pos + 1;
    }

    /* used > seen > heard > bad */
    size_t i, pos_max = used ? USED : (seen ? SEENG : SEENB_HEARDG);

    for (i = 0; i < pos_max; i++)
        if (pos_check[i]) {
            *bucketptr = bucket;
            *posptr = pos_check[i] - 1;

            return 1;
        }

    return 0;
}