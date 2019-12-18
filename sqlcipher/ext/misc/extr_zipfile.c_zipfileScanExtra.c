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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;

/* Variables and functions */
#define  ZIPFILE_EXTRA_TIMESTAMP 128 
 int /*<<< orphan*/  zipfileGetU32 (int*) ; 
 int zipfileRead16 (int*) ; 

__attribute__((used)) static int zipfileScanExtra(u8 *aExtra, int nExtra, u32 *pmTime){
  int ret = 0;
  u8 *p = aExtra;
  u8 *pEnd = &aExtra[nExtra];

  while( p<pEnd ){
    u16 id = zipfileRead16(p);
    u16 nByte = zipfileRead16(p);

    switch( id ){
      case ZIPFILE_EXTRA_TIMESTAMP: {
        u8 b = p[0];
        if( b & 0x01 ){     /* 0x01 -> modtime is present */
          *pmTime = zipfileGetU32(&p[1]);
          ret = 1;
        }
        break;
      }
    }

    p += nByte;
  }
  return ret;
}