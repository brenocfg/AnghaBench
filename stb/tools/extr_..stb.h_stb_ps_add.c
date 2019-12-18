#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t stb_uint32 ;
struct TYPE_14__ {void** p; int count; size_t mask; void** table; int count_deletes; int grow_threshhold; int size; int rehash_threshhold; } ;
typedef  TYPE_1__ stb_ps_hash ;
struct TYPE_15__ {int /*<<< orphan*/ ** p; } ;
typedef  TYPE_2__ stb_ps_bucket ;
typedef  TYPE_1__ stb_ps_array ;
typedef  int /*<<< orphan*/  stb_ps ;

/* Variables and functions */
 int /*<<< orphan*/ * EncodeArray (TYPE_1__*) ; 
 int /*<<< orphan*/ * EncodeBucket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EncodeHash (TYPE_1__*) ; 
 TYPE_1__* GetArray (int /*<<< orphan*/ *) ; 
 TYPE_2__* GetBucket (int /*<<< orphan*/ *) ; 
 TYPE_1__* GetHash (int /*<<< orphan*/ *) ; 
 int STB_BUCKET_SIZE ; 
 void* STB_DEL ; 
#define  STB_ps_array 131 
#define  STB_ps_bucket 130 
#define  STB_ps_direct 129 
#define  STB_ps_hash 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (void**,TYPE_2__*,int) ; 
 scalar_t__ realloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stb_bucket_create2 (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  stb_bucket_free (TYPE_2__*) ; 
 size_t stb_hashptr (void*) ; 
 int stb_log2_ceil (int) ; 
 int stb_ps_array_max ; 
 int /*<<< orphan*/  stb_ps_empty (size_t) ; 
 int stb_ps_fastlist_valid (void*) ; 
 int /*<<< orphan*/  stb_ps_find (int /*<<< orphan*/ *,void*) ; 
 TYPE_1__* stb_ps_makehash (int,int,void**) ; 
 int stb_rehash (size_t) ; 

stb_ps *  stb_ps_add   (stb_ps *ps, void *value)
{
   #ifdef STB_DEBUG
   assert(!stb_ps_find(ps,value));
   #endif
   if (value == NULL) return ps; // ignore NULL adds to avoid bad breakage
    assert((3 & (int)(size_t) value) == STB_ps_direct);
   assert(stb_ps_fastlist_valid(value));
   assert(value != STB_DEL);     // STB_DEL is less likely

    switch (3 & (int)(size_t) ps) {
      case STB_ps_direct:
         if (ps == NULL) return (stb_ps *) value;
         return EncodeBucket(stb_bucket_create2(ps,value));

      case STB_ps_bucket: {
         stb_ps_bucket *b = GetBucket(ps);
         stb_ps_array  *a;
         assert(STB_BUCKET_SIZE == 4);
         if (b->p[0] == NULL) { b->p[0] = value; return ps; }
         if (b->p[1] == NULL) { b->p[1] = value; return ps; }
         if (b->p[2] == NULL) { b->p[2] = value; return ps; }
         if (b->p[3] == NULL) { b->p[3] = value; return ps; }
         a = (stb_ps_array *) malloc(sizeof(*a) + 7 * sizeof(a->p[0])); // 8 slots, must be 2^k
         memcpy(a->p, b, sizeof(*b));
         a->p[4] = value;
         a->count = 5;
         stb_bucket_free(b);
         return EncodeArray(a);
      }

      case STB_ps_array: {
         stb_ps_array *a = GetArray(ps);
         if (a->count == stb_ps_array_max) {
            // promote from array to hash
            stb_ps_hash *h = stb_ps_makehash(2 << stb_log2_ceil(a->count), a->count, a->p);
            free(a);
            return stb_ps_add(EncodeHash(h), value);
         }
         // do we need to resize the array? the array doubles in size when it
         // crosses a power-of-two
         if ((a->count & (a->count-1))==0) {
            int newsize = a->count*2;
            // clamp newsize to max if:
            //    1. it's larger than max
            //    2. newsize*1.5 is larger than max (to avoid extra resizing)
            if (newsize + a->count > stb_ps_array_max)
               newsize = stb_ps_array_max;
            a = (stb_ps_array *) realloc(a, sizeof(*a) + (newsize-1) * sizeof(a->p[0]));
         }
         a->p[a->count++] = value;
         return EncodeArray(a);
      }
      case STB_ps_hash: {
         stb_ps_hash *h = GetHash(ps);
         stb_uint32 hash = stb_hashptr(value);
         stb_uint32 n = hash & h->mask;
         void **t = h->table;
         // find first NULL or STB_DEL entry
          if (!stb_ps_empty((size_t)t[n])) {
            stb_uint32 s = stb_rehash(hash) | 1;
            do {
               n = (n + s) & h->mask;
            } while (!stb_ps_empty((size_t)t[n]));
         }
         if (t[n] == STB_DEL)
            -- h->count_deletes;
         t[n] = value;
         ++ h->count;
         if (h->count == h->grow_threshhold) {
            stb_ps_hash *h2 = stb_ps_makehash(h->size*2, h->size, t);
            free(h);
            return EncodeHash(h2);
         }
         if (h->count + h->count_deletes == h->rehash_threshhold) {
            stb_ps_hash *h2 = stb_ps_makehash(h->size, h->size, t);
            free(h);
            return EncodeHash(h2);
         }
         return ps;
      }
   }
   return NULL; /* NOTREACHED */
}