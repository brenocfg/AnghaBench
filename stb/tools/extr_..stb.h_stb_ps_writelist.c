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
struct TYPE_7__ {int count; void** table; } ;
typedef  TYPE_1__ stb_ps_hash ;
struct TYPE_8__ {int /*<<< orphan*/ ** p; } ;
typedef  TYPE_2__ stb_ps_bucket ;
struct TYPE_9__ {int /*<<< orphan*/  p; int /*<<< orphan*/  count; } ;
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
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ ,int) ; 
 int stb_min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb_ps_empty (size_t) ; 

int stb_ps_writelist(stb_ps *ps, void **list, int size )
{
   int i,n=0;
    switch (3 & (int)(size_t) ps) {
      case STB_ps_direct:
         if (ps == NULL || size <= 0) return 0;
         list[0] = ps;
         return 1;
      case STB_ps_bucket: {
         stb_ps_bucket *b = GetBucket(ps);
         for (i=0; i < STB_BUCKET_SIZE; ++i)
            if (b->p[i] != NULL && n < size)
               list[n++] = b->p[i];
         return n;
      }
      case STB_ps_array: {
         stb_ps_array *a = GetArray(ps);
         n = stb_min(size, a->count);
         memcpy(list, a->p, sizeof(*list) * n);
         return n;
      }
      case STB_ps_hash: {
         stb_ps_hash *h = GetHash(ps);
         if (size <= 0) return 0;
         for (i=0; i < h->count; ++i) {
             if (!stb_ps_empty((size_t)h->table[i])) {
               list[n++] = h->table[i];
               if (n == size) break;
            }
         }
         return n;
      }
   }
   return 0; /* NOTREACHED */
}