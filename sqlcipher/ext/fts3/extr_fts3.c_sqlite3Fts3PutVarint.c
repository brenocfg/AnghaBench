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
typedef  int sqlite_int64 ;

/* Variables and functions */
 int FTS3_VARINT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 

int sqlite3Fts3PutVarint(char *p, sqlite_int64 v){
  unsigned char *q = (unsigned char *) p;
  sqlite_uint64 vu = v;
  do{
    *q++ = (unsigned char) ((vu & 0x7f) | 0x80);
    vu >>= 7;
  }while( vu!=0 );
  q[-1] &= 0x7f;  /* turn off high bit in final byte */
  assert( q - (unsigned char *)p <= FTS3_VARINT_MAX );
  return (int) (q - (unsigned char *)p);
}