#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* stbds_temp ;
struct TYPE_10__ {int mode; } ;
struct TYPE_8__ {scalar_t__ used_count; scalar_t__ used_count_threshold; int slot_count; TYPE_3__ string; TYPE_2__* storage; int /*<<< orphan*/  tombstone_count; int /*<<< orphan*/  slot_count_log2; int /*<<< orphan*/  seed; } ;
typedef  TYPE_1__ stbds_hash_index ;
struct TYPE_9__ {size_t* hash; scalar_t__* index; } ;
typedef  TYPE_2__ stbds_hash_bucket ;
typedef  int ptrdiff_t ;
struct TYPE_11__ {int length; TYPE_1__* hash_table; } ;

/* Variables and functions */
 void* STBDS_ARR_TO_HASH (void*,size_t) ; 
 int /*<<< orphan*/  STBDS_ASSERT (int) ; 
 int STBDS_BUCKET_LENGTH ; 
 size_t STBDS_BUCKET_MASK ; 
 size_t STBDS_BUCKET_SHIFT ; 
 int /*<<< orphan*/  STBDS_FREE (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* STBDS_HASH_TO_ARR (void*,size_t) ; 
 int STBDS_HM_STRING ; 
 scalar_t__ STBDS_INDEX_DELETED ; 
#define  STBDS_SH_ARENA 129 
#define  STBDS_SH_STRDUP 128 
 int /*<<< orphan*/  STBDS_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 size_t stbds_arrcap (void*) ; 
 void* stbds_arrgrowf (void*,size_t,int,int) ; 
 scalar_t__ stbds_arrlen (void*) ; 
 size_t stbds_hash_bytes (void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stbds_hash_grow ; 
 int /*<<< orphan*/  stbds_hash_probes ; 
 size_t stbds_hash_string (char*,int /*<<< orphan*/ ) ; 
 TYPE_6__* stbds_header (void*) ; 
 scalar_t__ stbds_is_key_equal (void*,size_t,void*,size_t,int,scalar_t__) ; 
 TYPE_1__* stbds_make_hash_index (size_t,TYPE_1__*) ; 
 size_t stbds_probe_position (size_t,int,int /*<<< orphan*/ ) ; 
 char* stbds_stralloc (TYPE_3__*,char*) ; 
 char* stbds_strdup (char*) ; 

void *stbds_hmput_key(void *a, size_t elemsize, void *key, size_t keysize, int mode)
{
  void *raw_a;
  stbds_hash_index *table;

  if (a == NULL) {
    a = stbds_arrgrowf(0, elemsize, 0, 1);
    memset(a, 0, elemsize);
    stbds_header(a)->length += 1;
    // adjust a to point AFTER the default element
    a = STBDS_ARR_TO_HASH(a,elemsize);
  }

  // adjust a to point to the default element
  raw_a = a;
  a = STBDS_HASH_TO_ARR(a,elemsize);

  table = (stbds_hash_index *) stbds_header(a)->hash_table;

  if (table == NULL || table->used_count >= table->used_count_threshold) {
    stbds_hash_index *nt;
    size_t slot_count;

    slot_count = (table == NULL) ? STBDS_BUCKET_LENGTH : table->slot_count*2;
    nt = stbds_make_hash_index(slot_count, table);
    if (table) {
      STBDS_FREE(NULL, table);
    }
    stbds_header(a)->hash_table = table = nt;
    STBDS_STATS(++stbds_hash_grow);
  }

  // we iterate hash table explicitly because we want to track if we saw a tombstone
  {
    size_t hash = mode >= STBDS_HM_STRING ? stbds_hash_string((char*)key,table->seed) : stbds_hash_bytes(key, keysize,table->seed);
    size_t step = STBDS_BUCKET_LENGTH;
    size_t limit,i;
    size_t pos;
    ptrdiff_t tombstone = -1;
    stbds_hash_bucket *bucket;

    // stored hash values are forbidden from being 0, so we can detect empty slots to early out quickly
    if (hash < 2) hash += 2;

    pos = stbds_probe_position(hash, table->slot_count, table->slot_count_log2);

    for (;;) {
      STBDS_STATS(++stbds_hash_probes);
      bucket = &table->storage[pos >> STBDS_BUCKET_SHIFT];

      // start searching from pos to end of bucket
      for (i=pos & STBDS_BUCKET_MASK; i < STBDS_BUCKET_LENGTH; ++i) {
        if (bucket->hash[i] == hash) {
          if (stbds_is_key_equal(raw_a, elemsize, key, keysize, mode, bucket->index[i])) {
            stbds_temp(a) = bucket->index[i];
            return STBDS_ARR_TO_HASH(a,elemsize);
          }
        } else if (bucket->hash[i] == 0) {
          pos = (pos & ~STBDS_BUCKET_MASK) + i;
          goto found_empty_slot;
        } else if (tombstone < 0) {
          if (bucket->index[i] == STBDS_INDEX_DELETED)
            tombstone = (ptrdiff_t) ((pos & ~STBDS_BUCKET_MASK) + i);
        }
      }

      // search from beginning of bucket to pos
      limit = pos & STBDS_BUCKET_MASK;
      for (i = 0; i < limit; ++i) {
        if (bucket->hash[i] == hash) {
          if (stbds_is_key_equal(raw_a, elemsize, key, keysize, mode, bucket->index[i])) {
            stbds_temp(a) = bucket->index[i];
            return STBDS_ARR_TO_HASH(a,elemsize);
          }
        } else if (bucket->hash[i] == 0) {
          pos = (pos & ~STBDS_BUCKET_MASK) + i;
          goto found_empty_slot;
        } else if (tombstone < 0) {
          if (bucket->index[i] == STBDS_INDEX_DELETED)
            tombstone = (ptrdiff_t) ((pos & ~STBDS_BUCKET_MASK) + i);
        }
      }

      // quadratic probing
      pos += step;
      step += STBDS_BUCKET_LENGTH;
      pos &= (table->slot_count-1);
    }
   found_empty_slot:
    if (tombstone >= 0) {
      pos = tombstone;
      --table->tombstone_count;
    }
    ++table->used_count;

    {
      ptrdiff_t i = (ptrdiff_t) stbds_arrlen(a);
    // we want to do stbds_arraddn(1), but we can't use the macros since we don't have something of the right type
      if ((size_t) i+1 > stbds_arrcap(a))
        *(void **) &a = stbds_arrgrowf(a, elemsize, 1, 0);
      raw_a = STBDS_ARR_TO_HASH(a,elemsize);

      STBDS_ASSERT((size_t) i+1 <= stbds_arrcap(a));
      stbds_header(a)->length = i+1;
      bucket = &table->storage[pos >> STBDS_BUCKET_SHIFT];
      bucket->hash[pos & STBDS_BUCKET_MASK] = hash;
      bucket->index[pos & STBDS_BUCKET_MASK] = i-1;
      stbds_temp(a) = i-1;

      switch (table->string.mode) {
         case STBDS_SH_STRDUP: *(char **) ((char *) a + elemsize*i) = stbds_strdup((char*) key); break;
         case STBDS_SH_ARENA:  *(char **) ((char *) a + elemsize*i) = stbds_stralloc(&table->string, (char*)key); break;
         default:              *(char **) ((char *) a + elemsize*i) = (char *) key; break;
      }
    }
    return STBDS_ARR_TO_HASH(a,elemsize);
  }
}