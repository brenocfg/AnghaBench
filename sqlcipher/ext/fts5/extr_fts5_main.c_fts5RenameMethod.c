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
struct TYPE_2__ {int /*<<< orphan*/  pStorage; } ;
typedef  TYPE_1__ Fts5FullTable ;

/* Variables and functions */
 int sqlite3Fts5StorageRename (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int fts5RenameMethod(
  sqlite3_vtab *pVtab,            /* Virtual table handle */
  const char *zName               /* New name of table */
){
  Fts5FullTable *pTab = (Fts5FullTable*)pVtab;
  return sqlite3Fts5StorageRename(pTab->pStorage, zName);
}