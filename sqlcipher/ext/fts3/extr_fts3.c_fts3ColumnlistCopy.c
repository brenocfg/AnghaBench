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
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static void fts3ColumnlistCopy(char **pp, char **ppPoslist){
  char *pEnd = *ppPoslist;
  char c = 0;

  /* A column-list is terminated by either a 0x01 or 0x00 byte that is
  ** not part of a multi-byte varint.
  */
  while( 0xFE & (*pEnd | c) ){
    c = *pEnd++ & 0x80;
    testcase( c!=0 && ((*pEnd)&0xfe)==0 );
  }
  if( pp ){
    int n = (int)(pEnd - *ppPoslist);
    char *p = *pp;
    memcpy(p, *ppPoslist, n);
    p += n;
    *pp = p;
  }
  *ppPoslist = pEnd;
}