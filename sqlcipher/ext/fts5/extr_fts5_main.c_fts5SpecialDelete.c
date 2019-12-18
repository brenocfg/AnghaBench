#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_3__ {int /*<<< orphan*/  pStorage; } ;
typedef  TYPE_1__ Fts5FullTable ;

/* Variables and functions */
 int SQLITE_INTEGER ; 
 int SQLITE_OK ; 
 int sqlite3Fts5StorageDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 int sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts5SpecialDelete(
  Fts5FullTable *pTab, 
  sqlite3_value **apVal
){
  int rc = SQLITE_OK;
  int eType1 = sqlite3_value_type(apVal[1]);
  if( eType1==SQLITE_INTEGER ){
    sqlite3_int64 iDel = sqlite3_value_int64(apVal[1]);
    rc = sqlite3Fts5StorageDelete(pTab->pStorage, iDel, &apVal[2]);
  }
  return rc;
}