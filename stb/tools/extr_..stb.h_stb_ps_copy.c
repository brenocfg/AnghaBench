#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  table; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ stb_ps_hash ;
typedef  int /*<<< orphan*/  stb_ps_bucket ;
struct TYPE_9__ {int count; int /*<<< orphan*/ * p; } ;
typedef  TYPE_2__ stb_ps_array ;
typedef  int /*<<< orphan*/  stb_ps ;

/* Variables and functions */
 int /*<<< orphan*/ * EncodeArray (TYPE_2__*) ; 
 int /*<<< orphan*/ * EncodeBucket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EncodeHash (TYPE_1__*) ; 
 TYPE_2__* GetArray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetBucket (int /*<<< orphan*/ *) ; 
 TYPE_1__* GetHash (int /*<<< orphan*/ *) ; 
#define  STB_ps_array 131 
#define  STB_ps_bucket 130 
#define  STB_ps_direct 129 
#define  STB_ps_hash 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int stb_ps_array_max ; 
 TYPE_1__* stb_ps_makehash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

stb_ps *stb_ps_copy(stb_ps *ps)
{
   int i;
   // not a switch: order based on expected performance/power-law distribution
    switch (3 & (int)(size_t) ps) {
      case STB_ps_direct: return ps;
      case STB_ps_bucket: {
         stb_ps_bucket *n = (stb_ps_bucket *) malloc(sizeof(*n));
         *n = *GetBucket(ps);
         return EncodeBucket(n);
      }
      case STB_ps_array: {
         stb_ps_array *a = GetArray(ps);
         stb_ps_array *n = (stb_ps_array *) malloc(sizeof(*n) + stb_ps_array_max * sizeof(n->p[0]));
         n->count = a->count;
         for (i=0; i < a->count; ++i)
            n->p[i] = a->p[i];
         return EncodeArray(n);
      }
      case STB_ps_hash: {
         stb_ps_hash *h = GetHash(ps);
         stb_ps_hash *n = stb_ps_makehash(h->size, h->size, h->table);
         return EncodeHash(n);
      }
   }
   assert(0); /* NOTREACHED */
   return NULL;
}