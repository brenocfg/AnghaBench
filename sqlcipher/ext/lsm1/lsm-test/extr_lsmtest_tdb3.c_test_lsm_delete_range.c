#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_2__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ LsmDb ;

/* Variables and functions */
 int lsm_delete_range (int /*<<< orphan*/ ,void*,int,void*,int) ; 

__attribute__((used)) static int test_lsm_delete_range(
  TestDb *pTestDb, 
  void *pKey1, int nKey1,
  void *pKey2, int nKey2
){
  LsmDb *pDb = (LsmDb *)pTestDb;
  return lsm_delete_range(pDb->db, pKey1, nKey1, pKey2, nKey2);
}