#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ explain_vtab ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int sqlite3_declare_vtab (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* sqlite3_malloc (int) ; 

__attribute__((used)) static int explainConnect(
  sqlite3 *db,
  void *pAux,
  int argc, const char *const*argv,
  sqlite3_vtab **ppVtab,
  char **pzErr
){
  explain_vtab *pNew;
  int rc;

/* Column numbers */
#define EXPLN_COLUMN_ADDR     0   /* Instruction address */
#define EXPLN_COLUMN_OPCODE   1   /* Opcode */
#define EXPLN_COLUMN_P1       2   /* Operand 1 */
#define EXPLN_COLUMN_P2       3   /* Operand 2 */
#define EXPLN_COLUMN_P3       4   /* Operand 3 */
#define EXPLN_COLUMN_P4       5   /* Operand 4 */
#define EXPLN_COLUMN_P5       6   /* Operand 5 */
#define EXPLN_COLUMN_COMMENT  7   /* Comment */
#define EXPLN_COLUMN_SQL      8   /* SQL that is being explained */


  rc = sqlite3_declare_vtab(db,
     "CREATE TABLE x(addr,opcode,p1,p2,p3,p4,p5,comment,sql HIDDEN)");
  if( rc==SQLITE_OK ){
    pNew = sqlite3_malloc( sizeof(*pNew) );
    *ppVtab = (sqlite3_vtab*)pNew;
    if( pNew==0 ) return SQLITE_NOMEM;
    memset(pNew, 0, sizeof(*pNew));
    pNew->db = db;
  }
  return rc;
}