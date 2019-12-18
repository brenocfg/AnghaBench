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

int sqlite3Fts5IndexCharlenToBytelen(
  const char *p, 
  int nByte, 
  int nChar
){
  int n = 0;
  int i;
  for(i=0; i<nChar; i++){
    if( n>=nByte ) return 0;      /* Input contains fewer than nChar chars */
    if( (unsigned char)p[n++]>=0xc0 ){
      while( (p[n] & 0xc0)==0x80 ){
        n++;
        if( n>=nByte ) break;
      }
    }
  }
  return n;
}