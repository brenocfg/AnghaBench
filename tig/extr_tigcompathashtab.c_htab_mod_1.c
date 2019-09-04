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
typedef  int hashval_t ;

/* Variables and functions */

__attribute__((used)) static inline hashval_t
htab_mod_1 (hashval_t x, hashval_t y, hashval_t inv, int shift)
{
  /* The multiplicative inverses computed above are for 32-bit types, and
     requires that we be able to compute a highpart multiply.  */
#ifdef UNSIGNED_64BIT_TYPE
  __extension__ typedef UNSIGNED_64BIT_TYPE ull;
  if (sizeof (hashval_t) * CHAR_BIT <= 32)
    {
      hashval_t t1, t2, t3, t4, q, r;

      t1 = ((ull)x * inv) >> 32;
      t2 = x - t1;
      t3 = t2 >> 1;
      t4 = t1 + t3;
      q  = t4 >> shift;
      r  = x - (q * y);

      return r;
    }
#endif

  /* Otherwise just use the native division routines.  */
  return x % y;
}