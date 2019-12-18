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

/* Variables and functions */

__attribute__((used)) static void fts5PorterStep1A(char *aBuf, int *pnBuf){
  int nBuf = *pnBuf;
  if( aBuf[nBuf-1]=='s' ){
    if( aBuf[nBuf-2]=='e' ){
      if( (nBuf>4 && aBuf[nBuf-4]=='s' && aBuf[nBuf-3]=='s') 
       || (nBuf>3 && aBuf[nBuf-3]=='i' )
      ){
        *pnBuf = nBuf-2;
      }else{
        *pnBuf = nBuf-1;
      }
    }
    else if( aBuf[nBuf-2]!='s' ){
      *pnBuf = nBuf-1;
    }
  }
}