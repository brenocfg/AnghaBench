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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_3__ {scalar_t__ file_format; int /*<<< orphan*/  enc; int /*<<< orphan*/  fkeyHash; int /*<<< orphan*/  trigHash; int /*<<< orphan*/  idxHash; int /*<<< orphan*/  tblHash; } ;
typedef  TYPE_1__ Schema ;
typedef  int /*<<< orphan*/  Btree ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 scalar_t__ sqlite3BtreeSchema (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3DbMallocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3HashInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3OomFault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3SchemaClear ; 

Schema *sqlite3SchemaGet(sqlite3 *db, Btree *pBt){
  Schema * p;
  if( pBt ){
    p = (Schema *)sqlite3BtreeSchema(pBt, sizeof(Schema), sqlite3SchemaClear);
  }else{
    p = (Schema *)sqlite3DbMallocZero(0, sizeof(Schema));
  }
  if( !p ){
    sqlite3OomFault(db);
  }else if ( 0==p->file_format ){
    sqlite3HashInit(&p->tblHash);
    sqlite3HashInit(&p->idxHash);
    sqlite3HashInit(&p->trigHash);
    sqlite3HashInit(&p->fkeyHash);
    p->enc = SQLITE_UTF8;
  }
  return p;
}