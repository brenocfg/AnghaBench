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
 int /*<<< orphan*/  copy_file (char*,char const*,int) ; 
 int /*<<< orphan*/  testFree (char*) ; 
 char* testMallocPrintf (char*,char const*,...) ; 

void testRestoreDb(const char *zFile, const char *zAux){
  char *zLog = testMallocPrintf("%s-%s", zFile, zAux);
  char *zFileSave = testMallocPrintf("%s-save", zFile);
  char *zLogSave = testMallocPrintf("%s-%s-save", zFile, zAux);

  copy_file(zFileSave, zFile, 1);
  copy_file(zLogSave, zLog, 0);

  testFree(zLog); testFree(zFileSave); testFree(zLogSave);
}