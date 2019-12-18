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
typedef  int /*<<< orphan*/  sqlite3_int64 ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3Fts3GetVarint (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts3GetReverseVarint(
  char **pp, 
  char *pStart, 
  sqlite3_int64 *pVal
){
  sqlite3_int64 iVal;
  char *p;

  /* Pointer p now points at the first byte past the varint we are 
  ** interested in. So, unless the doclist is corrupt, the 0x80 bit is
  ** clear on character p[-1]. */
  for(p = (*pp)-2; p>=pStart && *p&0x80; p--);
  p++;
  *pp = p;

  sqlite3Fts3GetVarint(p, &iVal);
  *pVal = iVal;
}