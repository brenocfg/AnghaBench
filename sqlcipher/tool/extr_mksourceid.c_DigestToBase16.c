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

__attribute__((used)) static void DigestToBase16(unsigned char *digest, char *zBuf, int nByte){
  static const char zEncode[] = "0123456789abcdef";
  int ix;

  for(ix=0; ix<nByte; ix++){
    *zBuf++ = zEncode[(*digest>>4)&0xf];
    *zBuf++ = zEncode[*digest++ & 0xf];
  }
  *zBuf = '\0';
}