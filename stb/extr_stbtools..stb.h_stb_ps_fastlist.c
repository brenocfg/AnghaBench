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
struct TYPE_7__ {int size; void** table; } ;
typedef  TYPE_1__ stb_ps_hash ;
struct TYPE_8__ {void** p; } ;
typedef  TYPE_2__ stb_ps_bucket ;
struct TYPE_9__ {int count; void** p; } ;
typedef  TYPE_3__ stb_ps_array ;
typedef  int /*<<< orphan*/  stb_ps ;

/* Variables and functions */
 TYPE_3__* GetArray (int /*<<< orphan*/ *) ; 
 TYPE_2__* GetBucket (int /*<<< orphan*/ *) ; 
 TYPE_1__* GetHash (int /*<<< orphan*/ *) ; 
 int STB_BUCKET_SIZE ; 
#define  STB_ps_array 131 
#define  STB_ps_bucket 130 
#define  STB_ps_direct 129 
#define  STB_ps_hash 128 

void ** stb_ps_fastlist(stb_ps *ps, int *count)
{
   static void *storage;

    switch (3 & (int)(size_t) ps) {
      case STB_ps_direct:
         if (ps == NULL) { *count = 0; return NULL; }
         storage = ps;
         *count = 1;
         return &storage;
      case STB_ps_bucket: {
         stb_ps_bucket *b = GetBucket(ps);
         *count = STB_BUCKET_SIZE;
         return b->p;
      }
      case STB_ps_array: {
         stb_ps_array *a = GetArray(ps);
         *count = a->count;
         return a->p;
      }
      case STB_ps_hash: {
         stb_ps_hash *h = GetHash(ps);
         *count = h->size;
         return h->table;
      }
   }
   return NULL; /* NOTREACHED */
}