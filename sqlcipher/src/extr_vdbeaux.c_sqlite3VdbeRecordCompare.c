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
typedef  int /*<<< orphan*/  UnpackedRecord ;

/* Variables and functions */
 int sqlite3VdbeRecordCompareWithSkip (int,void const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sqlite3VdbeRecordCompare(
  int nKey1, const void *pKey1,   /* Left key */
  UnpackedRecord *pPKey2          /* Right key */
){
  return sqlite3VdbeRecordCompareWithSkip(nKey1, pKey1, pPKey2, 0);
}