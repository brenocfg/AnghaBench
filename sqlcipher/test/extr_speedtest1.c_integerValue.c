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
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  aMult ;

/* Variables and functions */
 int /*<<< orphan*/  fatal_error (char*) ; 
 int hexDigitValue (char const) ; 
 scalar_t__ isdigit (char const) ; 
 scalar_t__ sqlite3_stricmp (char*,char const*) ; 

__attribute__((used)) static int integerValue(const char *zArg){
  sqlite3_int64 v = 0;
  static const struct { char *zSuffix; int iMult; } aMult[] = {
    { "KiB", 1024 },
    { "MiB", 1024*1024 },
    { "GiB", 1024*1024*1024 },
    { "KB",  1000 },
    { "MB",  1000000 },
    { "GB",  1000000000 },
    { "K",   1000 },
    { "M",   1000000 },
    { "G",   1000000000 },
  };
  int i;
  int isNeg = 0;
  if( zArg[0]=='-' ){
    isNeg = 1;
    zArg++;
  }else if( zArg[0]=='+' ){
    zArg++;
  }
  if( zArg[0]=='0' && zArg[1]=='x' ){
    int x;
    zArg += 2;
    while( (x = hexDigitValue(zArg[0]))>=0 ){
      v = (v<<4) + x;
      zArg++;
    }
  }else{
    while( isdigit(zArg[0]) ){
      v = v*10 + zArg[0] - '0';
      zArg++;
    }
  }
  for(i=0; i<sizeof(aMult)/sizeof(aMult[0]); i++){
    if( sqlite3_stricmp(aMult[i].zSuffix, zArg)==0 ){
      v *= aMult[i].iMult;
      break;
    }
  }
  if( v>0x7fffffff ) fatal_error("parameter too large - max 2147483648");
  return (int)(isNeg? -v : v);
}