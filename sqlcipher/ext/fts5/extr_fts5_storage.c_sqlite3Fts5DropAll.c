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
struct TYPE_3__ {scalar_t__ eContent; int /*<<< orphan*/  zName; int /*<<< orphan*/  zDb; int /*<<< orphan*/  db; scalar_t__ bColumnsize; } ;
typedef  TYPE_1__ Fts5Config ;

/* Variables and functions */
 scalar_t__ FTS5_CONTENT_NORMAL ; 
 int SQLITE_OK ; 
 int fts5ExecPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

int sqlite3Fts5DropAll(Fts5Config *pConfig){
  int rc = fts5ExecPrintf(pConfig->db, 0, 
      "DROP TABLE IF EXISTS %Q.'%q_data';"
      "DROP TABLE IF EXISTS %Q.'%q_idx';"
      "DROP TABLE IF EXISTS %Q.'%q_config';",
      pConfig->zDb, pConfig->zName,
      pConfig->zDb, pConfig->zName,
      pConfig->zDb, pConfig->zName
  );
  if( rc==SQLITE_OK && pConfig->bColumnsize ){
    rc = fts5ExecPrintf(pConfig->db, 0, 
        "DROP TABLE IF EXISTS %Q.'%q_docsize';",
        pConfig->zDb, pConfig->zName
    );
  }
  if( rc==SQLITE_OK && pConfig->eContent==FTS5_CONTENT_NORMAL ){
    rc = fts5ExecPrintf(pConfig->db, 0, 
        "DROP TABLE IF EXISTS %Q.'%q_content';",
        pConfig->zDb, pConfig->zName
    );
  }
  return rc;
}