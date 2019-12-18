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
 int /*<<< orphan*/  printf (char*,char*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static unsigned print_decode_line(
  const unsigned char *aData,  /* Content being decoded */
  int ofst, int nByte,         /* Start and size of decode */
  const char *zMsg             /* Message to append */
){
  int i, j;
  unsigned val = aData[ofst];
  char zBuf[100];
  sprintf(zBuf, " %05x: %02x", ofst, aData[ofst]);
  i = (int)strlen(zBuf);
  for(j=1; j<4; j++){
    if( j>=nByte ){
      sprintf(&zBuf[i], "   ");
    }else{
      sprintf(&zBuf[i], " %02x", aData[ofst+j]);
      val = val*256 + aData[ofst+j];
    }
    i += (int)strlen(&zBuf[i]);
  }
  sprintf(&zBuf[i], "   %10u", val);
  printf("%s  %s\n", zBuf, zMsg);
  return val;
}