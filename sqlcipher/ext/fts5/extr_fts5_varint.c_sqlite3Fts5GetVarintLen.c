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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

int sqlite3Fts5GetVarintLen(u32 iVal){
#if 0
  if( iVal<(1 << 7 ) ) return 1;
#endif
  assert( iVal>=(1 << 7) );
  if( iVal<(1 << 14) ) return 2;
  if( iVal<(1 << 21) ) return 3;
  if( iVal<(1 << 28) ) return 4;
  return 5;
}