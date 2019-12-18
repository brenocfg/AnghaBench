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

/* Variables and functions */
 int SQLITE_OK ; 
 int fuzzCorrupt () ; 
 int fuzzGetVarint (int*,int*) ; 

__attribute__((used)) static int fuzzChangeSize(u8 *p, int *pSz){
  u8 eType = p[0];
  switch( eType ){
    case 0x00:                    /* undefined */
    case 0x05:                    /* null */
      *pSz = 1;
      break;

    case 0x01:                    /* integer */
    case 0x02:                    /* real */
      *pSz = 9;
      break;

    case 0x03:                    /* text */
    case 0x04: {                  /* blob */
      int nTxt;
      int sz;
      sz = fuzzGetVarint(&p[1], &nTxt);
      *pSz = 1 + sz + nTxt;
      break;
    }

    default:
      return fuzzCorrupt();
  }
  return SQLITE_OK;
}