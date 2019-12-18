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
typedef  int /*<<< orphan*/  TestDb ;

/* Variables and functions */
 int strlen (char const*) ; 
 int /*<<< orphan*/  testWrite (int /*<<< orphan*/ *,void*,int,void*,int,int*) ; 

void testWriteStr(
  TestDb *pDb,                    /* Database handle */
  const char *zKey,               /* Key to query database for */
  const char *zVal,               /* Value to write */
  int *pRc                        /* IN/OUT: Error code */
){
  int nVal = (zVal ? strlen(zVal) : 0);
  testWrite(pDb, (void *)zKey, strlen(zKey), (void *)zVal, nVal, pRc);
}