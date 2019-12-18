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

__attribute__((used)) static void print_decode_line(
  unsigned char *aData,      /* Content being decoded */
  int ofst, int nByte,       /* Start and size of decode */
  int asHex,                 /* If true, output value as hex */
  const char *zMsg           /* Message to append */
){
  int i, j;
  int val = aData[ofst];
  char zBuf[100];
  sprintf(zBuf, " %03x: %02x", ofst, aData[ofst]);
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
  if( asHex ){
    sprintf(&zBuf[i], "  0x%08x", val);
  }else{
    sprintf(&zBuf[i], "   %9d", val);
  }
  printf("%s  %s\n", zBuf, zMsg);
}