#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ eContent; scalar_t__ bColumnsize; } ;
struct TYPE_6__ {TYPE_2__* pConfig; } ;
typedef  TYPE_1__ Fts5Storage ;
typedef  TYPE_2__ Fts5Config ;

/* Variables and functions */
 scalar_t__ FTS5_CONTENT_NORMAL ; 
 int /*<<< orphan*/  fts5StorageRenameOne (TYPE_2__*,int*,char*,char const*) ; 
 int sqlite3Fts5StorageSync (TYPE_1__*) ; 

int sqlite3Fts5StorageRename(Fts5Storage *pStorage, const char *zName){
  Fts5Config *pConfig = pStorage->pConfig;
  int rc = sqlite3Fts5StorageSync(pStorage);

  fts5StorageRenameOne(pConfig, &rc, "data", zName);
  fts5StorageRenameOne(pConfig, &rc, "idx", zName);
  fts5StorageRenameOne(pConfig, &rc, "config", zName);
  if( pConfig->bColumnsize ){
    fts5StorageRenameOne(pConfig, &rc, "docsize", zName);
  }
  if( pConfig->eContent==FTS5_CONTENT_NORMAL ){
    fts5StorageRenameOne(pConfig, &rc, "content", zName);
  }
  return rc;
}