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
 int snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int testFormatSize(char *aBuf, int nBuf, i64 nByte){
  int res;
  if( nByte<(1<<10) ){
    res = snprintf(aBuf, nBuf, "%d byte", (int)nByte);
  }else if( nByte<(1<<20) ){
    res = snprintf(aBuf, nBuf, "%dK", (int)(nByte/(1<<10)));
  }else{
    res = snprintf(aBuf, nBuf, "%dM", (int)(nByte/(1<<20)));
  }
  return res;
}