#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ dib_raw_t ;
struct TYPE_2__ {int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  HashmapBase ;

/* Variables and functions */
 int DIB_FREE ; 
 scalar_t__ DIB_RAW_FREE ; 
 scalar_t__ DIB_RAW_OVERFLOW ; 
 scalar_t__ _likely_ (int) ; 
 TYPE_1__* bucket_at (int /*<<< orphan*/ *,unsigned int) ; 
 int bucket_distance (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 unsigned int bucket_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned bucket_calculate_dib(HashmapBase *h, unsigned idx, dib_raw_t raw_dib) {
        unsigned initial_bucket;

        if (raw_dib == DIB_RAW_FREE)
                return DIB_FREE;

        if (_likely_(raw_dib < DIB_RAW_OVERFLOW))
                return raw_dib;

        /*
         * Having an overflow DIB value is very unlikely. The hash function
         * would have to be bad. For example, in a table of size 2^24 filled
         * to load factor 0.9 the maximum observed DIB is only about 60.
         * In theory (assuming I used Maxima correctly), for an infinite size
         * hash table with load factor 0.8 the probability of a given entry
         * having DIB > 40 is 1.9e-8.
         * This returns the correct DIB value by recomputing the hash value in
         * the unlikely case. XXX Hitting this case could be a hint to rehash.
         */
        initial_bucket = bucket_hash(h, bucket_at(h, idx)->key);
        return bucket_distance(h, idx, initial_bucket);
}