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
 int /*<<< orphan*/  GETVARINT_INIT (int,unsigned char const*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  GETVARINT_STEP (int,unsigned char const*,int,int,int,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 

int sqlite3Fts3GetVarint32(const char *p, int *pi){
  const unsigned char *ptr = (const unsigned char*)p;
  u32 a;

#ifndef fts3GetVarint32
  GETVARINT_INIT(a, ptr, 0,  0x00,     0x80, *pi, 1);
#else
  a = (*ptr++);
  assert( a & 0x80 );
#endif

  GETVARINT_STEP(a, ptr, 7,  0x7F,     0x4000, *pi, 2);
  GETVARINT_STEP(a, ptr, 14, 0x3FFF,   0x200000, *pi, 3);
  GETVARINT_STEP(a, ptr, 21, 0x1FFFFF, 0x10000000, *pi, 4);
  a = (a & 0x0FFFFFFF );
  *pi = (int)(a | ((u32)(*ptr & 0x07) << 28));
  assert( 0==(a & 0x80000000) );
  assert( *pi>=0 );
  return 5;
}