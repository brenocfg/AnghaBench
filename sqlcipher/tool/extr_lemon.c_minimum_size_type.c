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

__attribute__((used)) static const char *minimum_size_type(int lwr, int upr, int *pnByte){
  const char *zType = "int";
  int nByte = 4;
  if( lwr>=0 ){
    if( upr<=255 ){
      zType = "unsigned char";
      nByte = 1;
    }else if( upr<65535 ){
      zType = "unsigned short int";
      nByte = 2;
    }else{
      zType = "unsigned int";
      nByte = 4;
    }
  }else if( lwr>=-127 && upr<=127 ){
    zType = "signed char";
    nByte = 1;
  }else if( lwr>=-32767 && upr<32767 ){
    zType = "short";
    nByte = 2;
  }
  if( pnByte ) *pnByte = nByte;
  return zType;
}