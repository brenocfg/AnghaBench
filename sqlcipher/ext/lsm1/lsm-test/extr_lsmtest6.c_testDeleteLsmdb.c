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
 int /*<<< orphan*/  testFree (char*) ; 
 char* testMallocPrintf (char*,char const*) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

void testDeleteLsmdb(const char *zFile){
  char *zLog = testMallocPrintf("%s-log", zFile);
  char *zShm = testMallocPrintf("%s-shm", zFile);
  unlink(zFile);
  unlink(zLog);
  unlink(zShm);
  testFree(zLog);
  testFree(zShm);
}