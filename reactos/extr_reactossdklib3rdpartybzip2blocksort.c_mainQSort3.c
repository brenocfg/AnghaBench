#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ UInt32 ;
typedef  int /*<<< orphan*/  UInt16 ;
typedef  scalar_t__ UChar ;
typedef  scalar_t__ Int32 ;

/* Variables and functions */
 int /*<<< orphan*/  AssertD (int,char*) ; 
 int /*<<< orphan*/  AssertH (int,int) ; 
 scalar_t__ MAIN_QSORT_DEPTH_THRESH ; 
 scalar_t__ MAIN_QSORT_SMALL_THRESH ; 
 int MAIN_QSORT_STACK_SIZE ; 
 scalar_t__ True ; 
 int /*<<< orphan*/  mainSimpleSort (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ mmed3 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ mmin (scalar_t__,scalar_t__) ; 
 scalar_t__ mnextsize (int) ; 
 int /*<<< orphan*/  mnextswap (int,int) ; 
 int /*<<< orphan*/  mpop (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mpush (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mswap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mvswap (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static
void mainQSort3 ( UInt32* ptr,
                  UChar*  block,
                  UInt16* quadrant,
                  Int32   nblock,
                  Int32   loSt, 
                  Int32   hiSt, 
                  Int32   dSt,
                  Int32*  budget )
{
   Int32 unLo, unHi, ltLo, gtHi, n, m, med;
   Int32 sp, lo, hi, d;

   Int32 stackLo[MAIN_QSORT_STACK_SIZE];
   Int32 stackHi[MAIN_QSORT_STACK_SIZE];
   Int32 stackD [MAIN_QSORT_STACK_SIZE];

   Int32 nextLo[3];
   Int32 nextHi[3];
   Int32 nextD [3];

   sp = 0;
   mpush ( loSt, hiSt, dSt );

   while (sp > 0) {

      AssertH ( sp < MAIN_QSORT_STACK_SIZE - 2, 1001 );

      mpop ( lo, hi, d );
      if (hi - lo < MAIN_QSORT_SMALL_THRESH || 
          d > MAIN_QSORT_DEPTH_THRESH) {
         mainSimpleSort ( ptr, block, quadrant, nblock, lo, hi, d, budget );
         if (*budget < 0) return;
         continue;
      }

      med = (Int32) 
            mmed3 ( block[ptr[ lo         ]+d],
                    block[ptr[ hi         ]+d],
                    block[ptr[ (lo+hi)>>1 ]+d] );

      unLo = ltLo = lo;
      unHi = gtHi = hi;

      while (True) {
         while (True) {
            if (unLo > unHi) break;
            n = ((Int32)block[ptr[unLo]+d]) - med;
            if (n == 0) { 
               mswap(ptr[unLo], ptr[ltLo]); 
               ltLo++; unLo++; continue; 
            };
            if (n >  0) break;
            unLo++;
         }
         while (True) {
            if (unLo > unHi) break;
            n = ((Int32)block[ptr[unHi]+d]) - med;
            if (n == 0) { 
               mswap(ptr[unHi], ptr[gtHi]); 
               gtHi--; unHi--; continue; 
            };
            if (n <  0) break;
            unHi--;
         }
         if (unLo > unHi) break;
         mswap(ptr[unLo], ptr[unHi]); unLo++; unHi--;
      }

      AssertD ( unHi == unLo-1, "mainQSort3(2)" );

      if (gtHi < ltLo) {
         mpush(lo, hi, d+1 );
         continue;
      }

      n = mmin(ltLo-lo, unLo-ltLo); mvswap(lo, unLo-n, n);
      m = mmin(hi-gtHi, gtHi-unHi); mvswap(unLo, hi-m+1, m);

      n = lo + unLo - ltLo - 1;
      m = hi - (gtHi - unHi) + 1;

      nextLo[0] = lo;  nextHi[0] = n;   nextD[0] = d;
      nextLo[1] = m;   nextHi[1] = hi;  nextD[1] = d;
      nextLo[2] = n+1; nextHi[2] = m-1; nextD[2] = d+1;

      if (mnextsize(0) < mnextsize(1)) mnextswap(0,1);
      if (mnextsize(1) < mnextsize(2)) mnextswap(1,2);
      if (mnextsize(0) < mnextsize(1)) mnextswap(0,1);

      AssertD (mnextsize(0) >= mnextsize(1), "mainQSort3(8)" );
      AssertD (mnextsize(1) >= mnextsize(2), "mainQSort3(9)" );

      mpush (nextLo[0], nextHi[0], nextD[0]);
      mpush (nextLo[1], nextHi[1], nextD[1]);
      mpush (nextLo[2], nextHi[2], nextD[2]);
   }
}