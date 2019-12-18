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
 int SQLITE4_ERROR ; 
 int SQLITE4_OK ; 

__attribute__((used)) static int testParseInt(const char *z, int *piVal){
  int i = 0;
  const char *p = z;

  while( *p>='0' && *p<='9' ){
    i = i*10 + (*p - '0');
    p++;
  }
  if( *p=='K' || *p=='k' ){
    i = i * 1024;
    p++;
  }else if( *p=='M' || *p=='m' ){
    i = i * 1024 * 1024;
    p++;
  }

  if( *p ) return SQLITE4_ERROR;
  *piVal = i;
  return SQLITE4_OK;
}