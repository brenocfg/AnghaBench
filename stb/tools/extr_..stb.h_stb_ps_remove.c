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
struct TYPE_14__ {int count; void** p; size_t mask; void** table; int size; int shrink_threshhold; int /*<<< orphan*/  count_deletes; } ;
typedef  TYPE_1__ stb_ps_hash ;
struct TYPE_15__ {void** p; } ;
typedef  TYPE_2__ stb_ps_bucket ;
typedef  TYPE_1__ stb_ps_array ;
typedef  void stb_ps ;

/* Variables and functions */
 void* EncodeArray (TYPE_1__*) ; 
 void* EncodeBucket (TYPE_2__*) ; 
 void* EncodeHash (TYPE_1__*) ; 
 TYPE_1__* GetArray (void*) ; 
 TYPE_2__* GetBucket (void*) ; 
 TYPE_1__* GetHash (void*) ; 
 int STB_BUCKET_SIZE ; 
 void* STB_DEL ; 
#define  STB_ps_array 131 
#define  STB_ps_bucket 130 
#define  STB_ps_direct 129 
#define  STB_ps_hash 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 TYPE_2__* stb_bucket_create3 (void**) ; 
 int /*<<< orphan*/  stb_bucket_free (TYPE_2__*) ; 
 size_t stb_hashptr (void*) ; 
 int stb_log2_floor (int) ; 
 int stb_ps_array_max ; 
 int /*<<< orphan*/  stb_ps_empty (size_t) ; 
 int stb_ps_find (void*,void*) ; 
 TYPE_1__* stb_ps_makehash (int,int,void**) ; 
 int stb_rehash (size_t) ; 

stb_ps *stb_ps_remove(stb_ps *ps, void *value)
{
   #ifdef STB_DEBUG
   assert(stb_ps_find(ps, value));
   #endif
    assert((3 & (int)(size_t) value) == STB_ps_direct);
   if (value == NULL) return ps; // ignore NULL removes to avoid bad breakage
    switch (3 & (int)(size_t) ps) {
      case STB_ps_direct:
         return ps == value ? NULL : ps;
      case STB_ps_bucket: {
         stb_ps_bucket *b = GetBucket(ps);
         int count=0;
         assert(STB_BUCKET_SIZE == 4);
         if (b->p[0] == value) b->p[0] = NULL; else count += (b->p[0] != NULL);
         if (b->p[1] == value) b->p[1] = NULL; else count += (b->p[1] != NULL);
         if (b->p[2] == value) b->p[2] = NULL; else count += (b->p[2] != NULL);
         if (b->p[3] == value) b->p[3] = NULL; else count += (b->p[3] != NULL);
         if (count == 1) { // shrink bucket at size 1
            value = b->p[0];
            if (value == NULL) value = b->p[1];
            if (value == NULL) value = b->p[2];
            if (value == NULL) value = b->p[3];
            assert(value != NULL);
            stb_bucket_free(b);
            return (stb_ps *) value; // return STB_ps_direct of value
         }
         return ps;
      }
      case STB_ps_array: {
         stb_ps_array *a = GetArray(ps);
         int i;
         for (i=0; i < a->count; ++i) {
            if (a->p[i] == value) {
               a->p[i] = a->p[--a->count];
               if (a->count == 3) { // shrink to bucket!
                  stb_ps_bucket *b = stb_bucket_create3(a->p);
                  free(a);
                  return EncodeBucket(b);
               }
               return ps;
            }
         }
         return ps;
      }
      case STB_ps_hash: {
         stb_ps_hash *h = GetHash(ps);
         stb_uint32 hash = stb_hashptr(value);
         stb_uint32 s, n = hash & h->mask;
         void **t = h->table;
         if (t[n] != value) {
            s = stb_rehash(hash) | 1;
            do {
               n = (n + s) & h->mask;
            } while (t[n] != value);
         }
         t[n] = STB_DEL;
         -- h->count;
         ++ h->count_deletes;
         // should we shrink down to an array?
         if (h->count < stb_ps_array_max) {
            int n = 1 << stb_log2_floor(stb_ps_array_max);
            if (h->count < n) {
               stb_ps_array *a = (stb_ps_array *) malloc(sizeof(*a) + (n-1) * sizeof(a->p[0]));
               int i,j=0;
               for (i=0; i < h->size; ++i)
                    if (!stb_ps_empty((size_t)t[i]))
                     a->p[j++] = t[i];
               assert(j == h->count);
               a->count = j;
               free(h);
               return EncodeArray(a);
            }
         }
         if (h->count == h->shrink_threshhold) {
            stb_ps_hash *h2 = stb_ps_makehash(h->size >> 1, h->size, t);
            free(h);
            return EncodeHash(h2);
         }
         return ps;
      }
   }
   return ps; /* NOTREACHED */
}