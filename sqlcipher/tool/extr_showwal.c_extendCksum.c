#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bSwap; scalar_t__ s0; scalar_t__ s1; } ;
typedef  TYPE_1__ Cksum ;

/* Variables and functions */
 int getInt32 (unsigned char*) ; 
 unsigned int swab32 (unsigned int) ; 

__attribute__((used)) static void extendCksum(
  Cksum *pCksum,
  unsigned char *aData,
  unsigned int nByte,
  int bInit
){
  unsigned int *a32;
  if( bInit ){
    int a = 0;
    *((char*)&a) = 1;
    if( a==1 ){
      /* Host is little-endian */
      pCksum->bSwap = getInt32(aData)!=0x377f0682;
    }else{
      /* Host is big-endian */
      pCksum->bSwap = getInt32(aData)!=0x377f0683;
    }
    pCksum->s0 = 0;
    pCksum->s1 = 0;
  }
  a32 = (unsigned int*)aData;
  while( nByte>0 ){
    unsigned int x0 = a32[0];
    unsigned int x1 = a32[1];
    if( pCksum->bSwap ){
      x0 = swab32(x0);
      x1 = swab32(x1);
    }
    pCksum->s0 += x0 + pCksum->s1;
    pCksum->s1 += x1 + pCksum->s0;
    nByte -= 8;
    a32 += 2;
  }
}