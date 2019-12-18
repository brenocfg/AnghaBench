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
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_2__ {int /*<<< orphan*/  pConfig; } ;
typedef  TYPE_1__ Fts5Table ;
typedef  int /*<<< orphan*/  Fts5FullTable ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts5FreeVtab (int /*<<< orphan*/ *) ; 
 int sqlite3Fts5DropAll (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5DestroyMethod(sqlite3_vtab *pVtab){
  Fts5Table *pTab = (Fts5Table*)pVtab;
  int rc = sqlite3Fts5DropAll(pTab->pConfig);
  if( rc==SQLITE_OK ){
    fts5FreeVtab((Fts5FullTable*)pVtab);
  }
  return rc;
}