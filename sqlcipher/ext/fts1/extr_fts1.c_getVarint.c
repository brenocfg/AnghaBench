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
typedef  int sqlite_uint64 ;
typedef  scalar_t__ sqlite_int64 ;

/* Variables and functions */
 int VARINT_MAX ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int getVarint(const char *p, sqlite_int64 *v){
  const unsigned char *q = (const unsigned char *) p;
  sqlite_uint64 x = 0, y = 1;
  while( (*q & 0x80) == 0x80 ){
    x += y * (*q++ & 0x7f);
    y <<= 7;
    if( q - (unsigned char *)p >= VARINT_MAX ){  /* bad data */
      assert( 0 );
      return 0;
    }
  }
  x += y * (*q++);
  *v = (sqlite_int64) x;
  return (int) (q - (unsigned char *)p);
}