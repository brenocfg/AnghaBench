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
struct TYPE_8__ {void** p; } ;
typedef  TYPE_2__ stb_ps_bucket ;
struct TYPE_9__ {int count; void** p; } ;
typedef  TYPE_3__ stb_ps_array ;
typedef  void stb_ps ;

/* Variables and functions */
 TYPE_3__* GetArray (void*) ; 
 TYPE_2__* GetBucket (void*) ; 
 TYPE_1__* GetHash (void*) ; 
 int STB_BUCKET_SIZE ; 
 int STB_FALSE ; 
 int STB_TRUE ; 
#define  STB_ps_array 131 
#define  STB_ps_bucket 130 
#define  STB_ps_direct 129 
#define  STB_ps_hash 128 
 int /*<<< orphan*/  stb_ps_empty (size_t) ; 

int stb_ps_enum(stb_ps *ps, void *data, int (*func)(void *value, void *data))
{
   int i;
    switch (3 & (int)(size_t) ps) {
      case STB_ps_direct:
         if (ps == NULL) return STB_TRUE;
         return func(ps, data);
      case STB_ps_bucket: {
         stb_ps_bucket *b = GetBucket(ps);
         for (i=0; i < STB_BUCKET_SIZE; ++i)
            if (b->p[i] != NULL)
               if (!func(b->p[i], data))
                  return STB_FALSE;
         return STB_TRUE;
      }
      case STB_ps_array: {
         stb_ps_array *a = GetArray(ps);
         for (i=0; i < a->count; ++i)
            if (!func(a->p[i], data))
               return STB_FALSE;
         return STB_TRUE;
      }
      case STB_ps_hash: {
         stb_ps_hash *h = GetHash(ps);
         for (i=0; i < h->count; ++i)
              if (!stb_ps_empty((size_t)h->table[i]))
               if (!func(h->table[i], data))
                  return STB_FALSE;
         return STB_TRUE;
      }
   }
   return STB_TRUE; /* NOTREACHED */
}