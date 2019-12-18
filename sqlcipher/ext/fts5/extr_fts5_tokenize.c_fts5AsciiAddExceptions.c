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
struct TYPE_3__ {unsigned char* aTokenChar; } ;
typedef  TYPE_1__ AsciiTokenizer ;

/* Variables and functions */

__attribute__((used)) static void fts5AsciiAddExceptions(
  AsciiTokenizer *p, 
  const char *zArg, 
  int bTokenChars
){
  int i;
  for(i=0; zArg[i]; i++){
    if( (zArg[i] & 0x80)==0 ){
      p->aTokenChar[(int)zArg[i]] = (unsigned char)bTokenChars;
    }
  }
}