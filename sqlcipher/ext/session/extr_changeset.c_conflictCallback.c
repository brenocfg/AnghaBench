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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_changeset_iter ;

/* Variables and functions */
#define  SQLITE_CHANGESET_CONFLICT 135 
#define  SQLITE_CHANGESET_CONSTRAINT 134 
#define  SQLITE_CHANGESET_DATA 133 
#define  SQLITE_CHANGESET_FOREIGN_KEY 132 
#define  SQLITE_CHANGESET_NOTFOUND 131 
 int SQLITE_CHANGESET_OMIT ; 
#define  SQLITE_DELETE 130 
#define  SQLITE_INSERT 129 
#define  SQLITE_UPDATE 128 
 int /*<<< orphan*/  nConflict ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  renderValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3changeset_new (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqlite3changeset_old (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqlite3changeset_op (int /*<<< orphan*/ *,char const**,int*,int*,int*) ; 
 int /*<<< orphan*/  sqlite3changeset_pk (int /*<<< orphan*/ *,unsigned char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int conflictCallback(
  void *pCtx,
  int eConflict,
  sqlite3_changeset_iter *pIter
){
  int op, bIndirect, nCol, i;
  const char *zTab;
  unsigned char *abPK;
  const char *zType = "";
  const char *zOp = "";
  const char *zSep = " ";

  nConflict++;
  sqlite3changeset_op(pIter, &zTab, &nCol, &op, &bIndirect);
  sqlite3changeset_pk(pIter, &abPK, 0);
  switch( eConflict ){
    case SQLITE_CHANGESET_DATA:         zType = "DATA";         break;
    case SQLITE_CHANGESET_NOTFOUND:     zType = "NOTFOUND";     break;
    case SQLITE_CHANGESET_CONFLICT:     zType = "PRIMARY KEY";  break;
    case SQLITE_CHANGESET_FOREIGN_KEY:  zType = "FOREIGN KEY";  break;
    case SQLITE_CHANGESET_CONSTRAINT:   zType = "CONSTRAINT";   break;
  }
  switch( op ){
    case SQLITE_UPDATE:     zOp = "UPDATE of";     break;
    case SQLITE_INSERT:     zOp = "INSERT into";   break;
    case SQLITE_DELETE:     zOp = "DELETE from";   break;
  }
  printf("%s conflict on %s table %s with primary key", zType, zOp, zTab);
  for(i=0; i<nCol; i++){
    sqlite3_value *pVal;
    if( abPK[i]==0 ) continue;
    printf("%s", zSep);
    if( op==SQLITE_INSERT ){
      sqlite3changeset_new(pIter, i, &pVal);
    }else{
      sqlite3changeset_old(pIter, i, &pVal);
    }
    renderValue(pVal);
    zSep = ",";
  }
  printf("\n");
  return SQLITE_CHANGESET_OMIT;
}