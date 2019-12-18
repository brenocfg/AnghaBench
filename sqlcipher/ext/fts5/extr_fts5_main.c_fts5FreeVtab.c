#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pConfig; int /*<<< orphan*/  pIndex; } ;
struct TYPE_6__ {TYPE_1__ p; int /*<<< orphan*/  pStorage; } ;
typedef  TYPE_2__ Fts5FullTable ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3Fts5ConfigFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3Fts5IndexClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3Fts5StorageClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 

__attribute__((used)) static void fts5FreeVtab(Fts5FullTable *pTab){
  if( pTab ){
    sqlite3Fts5IndexClose(pTab->p.pIndex);
    sqlite3Fts5StorageClose(pTab->pStorage);
    sqlite3Fts5ConfigFree(pTab->p.pConfig);
    sqlite3_free(pTab);
  }
}