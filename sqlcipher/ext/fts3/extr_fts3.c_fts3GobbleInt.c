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
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 

__attribute__((used)) static int fts3GobbleInt(const char **pp, int *pnOut){
  const int MAX_NPREFIX = 10000000;
  const char *p;                  /* Iterator pointer */
  int nInt = 0;                   /* Output value */

  for(p=*pp; p[0]>='0' && p[0]<='9'; p++){
    nInt = nInt * 10 + (p[0] - '0');
    if( nInt>MAX_NPREFIX ){
      nInt = 0;
      break;
    }
  }
  if( p==*pp ) return SQLITE_ERROR;
  *pnOut = nInt;
  *pp = p;
  return SQLITE_OK;
}