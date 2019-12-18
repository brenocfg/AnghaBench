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
typedef  int sqlite3_uint64 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fwrite (unsigned char*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void putsVarint(FILE *out, sqlite3_uint64 v){
  int i, n;
  unsigned char p[12];
  if( v & (((sqlite3_uint64)0xff000000)<<32) ){
    p[8] = (unsigned char)v;
    v >>= 8;
    for(i=7; i>=0; i--){
      p[i] = (unsigned char)((v & 0x7f) | 0x80);
      v >>= 7;
    }
    fwrite(p, 8, 1, out);
  }else{
    n = 9;
    do{
      p[n--] = (unsigned char)((v & 0x7f) | 0x80);
      v >>= 7;
    }while( v!=0 );
    p[9] &= 0x7f;
    fwrite(p+n+1, 9-n, 1, out);
  }
}