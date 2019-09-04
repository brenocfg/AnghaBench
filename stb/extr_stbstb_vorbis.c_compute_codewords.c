#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  available ;
struct TYPE_4__ {scalar_t__ sorted_entries; } ;
typedef  TYPE_1__ Codebook ;

/* Variables and functions */
 int FALSE ; 
 int NO_CODE ; 
 int TRUE ; 
 int /*<<< orphan*/  add_entry (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bit_reverse (scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int compute_codewords(Codebook *c, uint8 *len, int n, uint32 *values)
{
   int i,k,m=0;
   uint32 available[32];

   memset(available, 0, sizeof(available));
   // find the first entry
   for (k=0; k < n; ++k) if (len[k] < NO_CODE) break;
   if (k == n) { assert(c->sorted_entries == 0); return TRUE; }
   // add to the list
   add_entry(c, 0, k, m++, len[k], values);
   // add all available leaves
   for (i=1; i <= len[k]; ++i)
      available[i] = 1U << (32-i);
   // note that the above code treats the first case specially,
   // but it's really the same as the following code, so they
   // could probably be combined (except the initial code is 0,
   // and I use 0 in available[] to mean 'empty')
   for (i=k+1; i < n; ++i) {
      uint32 res;
      int z = len[i], y;
      if (z == NO_CODE) continue;
      // find lowest available leaf (should always be earliest,
      // which is what the specification calls for)
      // note that this property, and the fact we can never have
      // more than one free leaf at a given level, isn't totally
      // trivial to prove, but it seems true and the assert never
      // fires, so!
      while (z > 0 && !available[z]) --z;
      if (z == 0) { return FALSE; }
      res = available[z];
      assert(z >= 0 && z < 32);
      available[z] = 0;
      add_entry(c, bit_reverse(res), i, m++, len[i], values);
      // propagate availability up the tree
      if (z != len[i]) {
         assert(len[i] >= 0 && len[i] < 32);
         for (y=len[i]; y > z; --y) {
            assert(available[y] == 0);
            available[y] = res + (1 << (32-y));
         }
      }
   }
   return TRUE;
}