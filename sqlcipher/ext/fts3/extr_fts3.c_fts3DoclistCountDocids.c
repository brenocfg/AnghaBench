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
 int /*<<< orphan*/  fts3PoslistCopy (int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static int fts3DoclistCountDocids(char *aList, int nList){
  int nDoc = 0;                   /* Return value */
  if( aList ){
    char *aEnd = &aList[nList];   /* Pointer to one byte after EOF */
    char *p = aList;              /* Cursor */
    while( p<aEnd ){
      nDoc++;
      while( (*p++)&0x80 );     /* Skip docid varint */
      fts3PoslistCopy(0, &p);   /* Skip over position list */
    }
  }

  return nDoc;
}