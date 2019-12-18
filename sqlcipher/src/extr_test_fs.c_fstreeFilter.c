#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_5__ {scalar_t__ pVtab; } ;
struct TYPE_7__ {scalar_t__ pStmt; TYPE_1__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ FstreeVtab ;
typedef  TYPE_3__ FstreeCsr ;

/* Variables and functions */
#define  SQLITE_INDEX_CONSTRAINT_GLOB 129 
#define  SQLITE_INDEX_CONSTRAINT_LIKE 128 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  fstreeCloseFd (TYPE_3__*) ; 
 int fstreeNext (int /*<<< orphan*/ *) ; 
 int sqlite3Strlen30 (char*) ; 
 int /*<<< orphan*/  sqlite3_bind_text (scalar_t__,int,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,...) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char const*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_strnicmp (char const*,char*,int) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 char* windirent_getenv (char*) ; 

__attribute__((used)) static int fstreeFilter(
  sqlite3_vtab_cursor *pVtabCursor, 
  int idxNum, const char *idxStr,
  int argc, sqlite3_value **argv
){
  FstreeCsr *pCsr = (FstreeCsr*)pVtabCursor;
  FstreeVtab *pTab = (FstreeVtab*)(pCsr->base.pVtab);
  int rc;
  const char *zSql = 
"WITH r(d) AS ("
"  SELECT CASE WHEN dir=?2 THEN ?3 ELSE dir END || '/' || name "
"    FROM fsdir WHERE dir=?1 AND name NOT LIKE '.%'"
"  UNION ALL"
"  SELECT dir || '/' || name FROM r, fsdir WHERE dir=d AND name NOT LIKE '.%'"
") SELECT d FROM r;";

  char *zRoot;
  int nRoot;
  char *zPrefix;
  int nPrefix;
  const char *zDir;
  int nDir;
  char aWild[2] = { '\0', '\0' };

#if SQLITE_OS_WIN
  const char *zDrive = windirent_getenv("fstreeDrive");
  if( zDrive==0 ){
    zDrive = windirent_getenv("SystemDrive");
  }
  zRoot = sqlite3_mprintf("%s%c", zDrive, '/');
  nRoot = sqlite3Strlen30(zRoot);
  zPrefix = sqlite3_mprintf("%s", zDrive);
  nPrefix = sqlite3Strlen30(zPrefix);
#else
  zRoot = "/";
  nRoot = 1;
  zPrefix = "";
  nPrefix = 0;
#endif

  zDir = zRoot;
  nDir = nRoot;

  fstreeCloseFd(pCsr);
  sqlite3_finalize(pCsr->pStmt);
  pCsr->pStmt = 0;
  rc = sqlite3_prepare_v2(pTab->db, zSql, -1, &pCsr->pStmt, 0);
  if( rc!=SQLITE_OK ) return rc;

  if( idxNum ){
    const char *zQuery = (const char*)sqlite3_value_text(argv[0]);
    switch( idxNum ){
      case SQLITE_INDEX_CONSTRAINT_GLOB:
        aWild[0] = '*';
        aWild[1] = '?';
        break;
      case SQLITE_INDEX_CONSTRAINT_LIKE:
        aWild[0] = '_';
        aWild[1] = '%';
        break;
    }

    if( sqlite3_strnicmp(zQuery, zPrefix, nPrefix)==0 ){
      int i;
      for(i=nPrefix; zQuery[i]; i++){
        if( zQuery[i]==aWild[0] || zQuery[i]==aWild[1] ) break;
        if( zQuery[i]=='/' ) nDir = i;
      }
      zDir = zQuery;
    }
  }
  if( nDir==0 ) nDir = 1;

  sqlite3_bind_text(pCsr->pStmt, 1, zDir, nDir, SQLITE_TRANSIENT);
  sqlite3_bind_text(pCsr->pStmt, 2, zRoot, nRoot, SQLITE_TRANSIENT);
  sqlite3_bind_text(pCsr->pStmt, 3, zPrefix, nPrefix, SQLITE_TRANSIENT);

#if SQLITE_OS_WIN
  sqlite3_free(zPrefix);
  sqlite3_free(zRoot);
#endif

  return fstreeNext(pVtabCursor); 
}