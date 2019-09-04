#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int input_size; int length; int depth; int /*<<< orphan*/  input; scalar_t__ inherited_storage; } ;
typedef  TYPE_1__ table ;
struct TYPE_8__ {scalar_t__ size; size_t path; } ;
typedef  TYPE_2__ result ;

/* Variables and functions */
 int CLUSTERSIZECOUNT ; 
 int MODECOUNT ; 
 TYPE_1__ pack_for_mode (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb_arr_free (int /*<<< orphan*/ ) ; 
 scalar_t__ stb_max (scalar_t__,scalar_t__) ; 

result pack_table(table *t, size_t path, int min_storage)
{
   int i;
   result best;
   best.size = t->inherited_storage + t->input_size * t->length;
   best.path = path;

   if ((int) t->inherited_storage > min_storage) {
      best.size = stb_max(best.size, t->inherited_storage);
      return best;
   }

   if (t->length <= 256 || t->depth >= 4) {
      //printf("%08x: %7d\n", best.path, best.size);
      return best;
   }

   path <<= 7;
   for (i=0; i < MODECOUNT * CLUSTERSIZECOUNT; ++i) {
      table newtab;
      result r;
      newtab = pack_for_mode(t, i, 0);
      r = pack_table(&newtab, path+i+1, min_storage);
      if (r.size < best.size)
         best = r;
      stb_arr_free(newtab.input);
      //printf("Size: %6d + %6d\n", newtab.inherited_storage, newtab.input_size * newtab.length);
   }
   return best;
}