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
 int sqlite3Fts3PutVarint (char*,int) ; 

__attribute__((used)) static int fts3PutColNumber(char **pp, int iCol){
  int n = 0;                      /* Number of bytes written */
  if( iCol ){
    char *p = *pp;                /* Output pointer */
    n = 1 + sqlite3Fts3PutVarint(&p[1], iCol);
    *p = 0x01;
    *pp = &p[n];
  }
  return n;
}