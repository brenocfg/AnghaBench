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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3Fts5GetVarint (unsigned char const*,scalar_t__*) ; 

int sqlite3Fts5GetVarint32(const unsigned char *p, u32 *v){
  u32 a,b;

  /* The 1-byte case. Overwhelmingly the most common. */
  a = *p;
  /* a: p0 (unmasked) */
  if (!(a&0x80))
  {
    /* Values between 0 and 127 */
    *v = a;
    return 1;
  }

  /* The 2-byte case */
  p++;
  b = *p;
  /* b: p1 (unmasked) */
  if (!(b&0x80))
  {
    /* Values between 128 and 16383 */
    a &= 0x7f;
    a = a<<7;
    *v = a | b;
    return 2;
  }

  /* The 3-byte case */
  p++;
  a = a<<14;
  a |= *p;
  /* a: p0<<14 | p2 (unmasked) */
  if (!(a&0x80))
  {
    /* Values between 16384 and 2097151 */
    a &= (0x7f<<14)|(0x7f);
    b &= 0x7f;
    b = b<<7;
    *v = a | b;
    return 3;
  }

  /* A 32-bit varint is used to store size information in btrees.
  ** Objects are rarely larger than 2MiB limit of a 3-byte varint.
  ** A 3-byte varint is sufficient, for example, to record the size
  ** of a 1048569-byte BLOB or string.
  **
  ** We only unroll the first 1-, 2-, and 3- byte cases.  The very
  ** rare larger cases can be handled by the slower 64-bit varint
  ** routine.
  */
  {
    u64 v64;
    u8 n;
    p -= 2;
    n = sqlite3Fts5GetVarint(p, &v64);
    *v = ((u32)v64) & 0x7FFFFFFF;
    assert( n>3 && n<=9 );
    return n;
  }
}