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
typedef  int /*<<< orphan*/  FileSystem ;

/* Variables and functions */
 int LSM_MIN (int,int) ; 
 int lsmFsPageSize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int keyszToSkip(FileSystem *pFS, int nKey){
  int nPgsz;                /* Nominal database page size */
  nPgsz = lsmFsPageSize(pFS);
  return LSM_MIN(((nKey * 4) / nPgsz), 3);
}