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
typedef  int /*<<< orphan*/  ShmHeader ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * testMalloc (int) ; 
 char* testMallocPrintf (char*,char const*) ; 
 int /*<<< orphan*/  testReadFile (char*,int /*<<< orphan*/ ,void*,int,int*) ; 

__attribute__((used)) static ShmHeader *getShmHeader(const char *zDb){
  int rc = 0;
  char *zShm = testMallocPrintf("%s-shm", zDb);
  ShmHeader *pHdr;

  pHdr = testMalloc(sizeof(ShmHeader));
  testReadFile(zShm, 0, (void *)pHdr, sizeof(ShmHeader), &rc);
  assert( rc==0 );

  return pHdr;
}