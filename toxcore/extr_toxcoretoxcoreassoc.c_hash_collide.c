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
typedef  int uint64_t ;
typedef  int hash_t ;
struct TYPE_3__ {int candidates_bucket_size; } ;
typedef  TYPE_1__ Assoc ;

/* Variables and functions */
 int HASH_COLLIDE_PRIME ; 

__attribute__((used)) static hash_t hash_collide(const Assoc *assoc, hash_t hash)
{
    uint64_t hash64 = hash % assoc->candidates_bucket_size;
    hash64 = (hash64 * HASH_COLLIDE_PRIME) % assoc->candidates_bucket_size;

    hash_t retval = hash64;

    /* this should never happen when CANDIDATES_TO_KEEP is prime and hash not a multiple
     * (id_hash() checks for a multiple and returns a different hash in that case)
     *
     * ( 1 .. (prime - 1) is a group over multiplication and every number has its inverse
     *   in the group, so no multiplication should ever end on zero as long neither
     *   of the two factors was zero-equivalent )
     *
     * BUT: because the usage of the word "never" invokes Murphy's law, catch it */
    if (!retval) {
#ifdef DEBUG
        fprintf(stderr, "assoc::hash_collide: hash %u, bucket size %u => %u!", hash, (uint)assoc->candidates_bucket_size,
                retval);
        assert(retval != 0);
#endif
        retval = 1;
    }

    return retval;
}