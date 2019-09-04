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
struct TYPE_7__ {int count; } ;
typedef  TYPE_1__ stb_ps_hash ;
struct TYPE_8__ {int /*<<< orphan*/ ** p; } ;
typedef  TYPE_2__ stb_ps_bucket ;
struct TYPE_9__ {int count; } ;
typedef  TYPE_3__ stb_ps_array ;
typedef  int /*<<< orphan*/  stb_ps ;

/* Variables and functions */
 TYPE_3__* GetArray (int /*<<< orphan*/ *) ; 
 TYPE_2__* GetBucket (int /*<<< orphan*/ *) ; 
 TYPE_1__* GetHash (int /*<<< orphan*/ *) ; 
#define  STB_ps_array 131 
#define  STB_ps_bucket 130 
#define  STB_ps_direct 129 
#define  STB_ps_hash 128 

int stb_ps_count (stb_ps *ps)
{
    switch (3 & (int)(size_t) ps) {
      case STB_ps_direct:
         return ps != NULL;
      case STB_ps_bucket: {
         stb_ps_bucket *b = GetBucket(ps);
         return (b->p[0] != NULL) + (b->p[1] != NULL) +
                (b->p[2] != NULL) + (b->p[3] != NULL);
      }
      case STB_ps_array: {
         stb_ps_array *a = GetArray(ps);
         return a->count;
      }
      case STB_ps_hash: {
         stb_ps_hash *h = GetHash(ps);
         return h->count;
      }
   }
   return 0;
}