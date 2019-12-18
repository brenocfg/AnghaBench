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
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_2__ {scalar_t__ pEntry; int /*<<< orphan*/  iRowid; scalar_t__ pDir; } ;
typedef  TYPE_1__ FsdirCsr ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  closedir (scalar_t__) ; 
 scalar_t__ readdir (scalar_t__) ; 

__attribute__((used)) static int fsdirNext(sqlite3_vtab_cursor *cur){
  FsdirCsr *pCsr = (FsdirCsr*)cur;

  if( pCsr->pDir ){
    pCsr->pEntry = readdir(pCsr->pDir);
    if( pCsr->pEntry==0 ){
      closedir(pCsr->pDir);
      pCsr->pDir = 0;
    }
    pCsr->iRowid++;
  }

  return SQLITE_OK;
}