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
struct TYPE_3__ {int /*<<< orphan*/  zName; int /*<<< orphan*/  zDb; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ Fts5Config ;

/* Variables and functions */
 int SQLITE_OK ; 
 int fts5ExecPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,char const*) ; 

__attribute__((used)) static void fts5StorageRenameOne(
  Fts5Config *pConfig,            /* Current FTS5 configuration */
  int *pRc,                       /* IN/OUT: Error code */
  const char *zTail,              /* Tail of table name e.g. "data", "config" */
  const char *zName               /* New name of FTS5 table */
){
  if( *pRc==SQLITE_OK ){
    *pRc = fts5ExecPrintf(pConfig->db, 0, 
        "ALTER TABLE %Q.'%q_%s' RENAME TO '%q_%s';",
        pConfig->zDb, pConfig->zName, zTail, zName, zTail
    );
  }
}