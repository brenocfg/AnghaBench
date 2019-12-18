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
typedef  scalar_t__ sqlite3_int64 ;

/* Variables and functions */
 int LARGEST_INT64 ; 
 scalar_t__ SMALLEST_INT64 ; 
 int /*<<< orphan*/  assert (int) ; 
 int totypeCompare2pow63 (char const*) ; 
 scalar_t__ totypeIsspace (char const) ; 

__attribute__((used)) static int totypeAtoi64(const char *zNum, sqlite3_int64 *pNum, int length){
  sqlite3_uint64 u = 0;
  int neg = 0; /* assume positive */
  int i;
  int c = 0;
  int nonNum = 0;
  const char *zStart;
  const char *zEnd = zNum + length;

  while( zNum<zEnd && totypeIsspace(*zNum) ) zNum++;
  if( zNum<zEnd ){
    if( *zNum=='-' ){
      neg = 1;
      zNum++;
    }else if( *zNum=='+' ){
      zNum++;
    }
  }
  zStart = zNum;
  while( zNum<zEnd && zNum[0]=='0' ){ zNum++; } /* Skip leading zeros. */
  for(i=0; &zNum[i]<zEnd && (c=zNum[i])>='0' && c<='9'; i++){
    u = u*10 + c - '0';
  }
  if( u>LARGEST_INT64 ){
    *pNum = SMALLEST_INT64;
  }else if( neg ){
    *pNum = -(sqlite3_int64)u;
  }else{
    *pNum = (sqlite3_int64)u;
  }
  if( (c!=0 && &zNum[i]<zEnd) || (i==0 && zStart==zNum) || i>19 || nonNum ){
    /* zNum is empty or contains non-numeric text or is longer
    ** than 19 digits (thus guaranteeing that it is too large) */
    return 1;
  }else if( i<19 ){
    /* Less than 19 digits, so we know that it fits in 64 bits */
    assert( u<=LARGEST_INT64 );
    return 0;
  }else{
    /* zNum is a 19-digit numbers.  Compare it against 9223372036854775808. */
    c = totypeCompare2pow63(zNum);
    if( c<0 ){
      /* zNum is less than 9223372036854775808 so it fits */
      assert( u<=LARGEST_INT64 );
      return 0;
    }else if( c>0 ){
      /* zNum is greater than 9223372036854775808 so it overflows */
      return 1;
    }else{
      /* zNum is exactly 9223372036854775808.  Fits if negative.  The
      ** special case 2 overflow if positive */
      assert( u-1==LARGEST_INT64 );
      assert( (*pNum)==SMALLEST_INT64 );
      return neg ? 0 : 2;
    }
  }
}