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
typedef  int /*<<< orphan*/  lsm_db ;
typedef  int /*<<< orphan*/  OomTest ;

/* Variables and functions */
 int strlen (char const*) ; 
 int /*<<< orphan*/  testOomFetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int,void*,int,int*) ; 

__attribute__((used)) static void testOomFetchStr(
  OomTest *pOom,
  lsm_db *pDb,
  const char *zKey,
  const char *zVal,
  int *pRc
){
  int nKey = strlen(zKey);
  int nVal = strlen(zVal);
  testOomFetch(pOom, pDb, (void *)zKey, nKey, (void *)zVal, nVal, pRc);
}