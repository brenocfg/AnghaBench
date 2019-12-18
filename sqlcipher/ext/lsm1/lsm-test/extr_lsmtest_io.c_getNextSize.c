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
typedef  int i64 ;

/* Variables and functions */
 scalar_t__ safe_isdigit (char) ; 

__attribute__((used)) static i64 getNextSize(char *zIn, char **pzOut, int *pRc){
  i64 iRet = 0;
  if( *pRc==0 ){
    char *z = zIn;

    if( !safe_isdigit(*z) ){
      *pRc = 1;
      return 0;
    }

    /* Process digits */
    while( safe_isdigit(*z) ){
      iRet = iRet*10 + (*z - '0');
      z++;
    }

    /* Process suffix */
    switch( *z ){
      case 'k': case 'K':
        iRet = iRet * 1024;
        z++;
        break;

      case 'm': case 'M':
        iRet = iRet * 1024 * 1024;
        z++;
        break;

      case 'g': case 'G':
        iRet = iRet * 1024 * 1024 * 1024;
        z++;
        break;
    }

    if( pzOut ) *pzOut = z;
  }
  return iRet;
}