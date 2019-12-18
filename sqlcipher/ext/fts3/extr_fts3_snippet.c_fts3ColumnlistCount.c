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

__attribute__((used)) static int fts3ColumnlistCount(char **ppCollist){
  char *pEnd = *ppCollist;
  char c = 0;
  int nEntry = 0;

  /* A column-list is terminated by either a 0x01 or 0x00. */
  while( 0xFE & (*pEnd | c) ){
    c = *pEnd++ & 0x80;
    if( !c ) nEntry++;
  }

  *ppCollist = pEnd;
  return nEntry;
}