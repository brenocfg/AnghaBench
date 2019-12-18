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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_3__ {int bHasContext; int /*<<< orphan*/  db; void* pNotFound; void* pOpenClose; int /*<<< orphan*/  nMaxOpen; } ;
typedef  TYPE_1__ UnionTab ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int sqlite3_bind_parameter_index (int /*<<< orphan*/ *,char*) ; 
 int sqlite3_bind_text (int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_column_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,...) ; 
 scalar_t__ sqlite3_strnicmp (char*,char*,int) ; 
 int /*<<< orphan*/  unionDequote (char*) ; 
 void* unionPreparePrintf (int*,char**,int /*<<< orphan*/ ,char*,char*,...) ; 
 char* unionStrdup (int*,char const* const) ; 
 scalar_t__ union_isidchar (char) ; 
 scalar_t__ union_isspace (char) ; 

__attribute__((used)) static void unionConfigureVtab(
  int *pRc,                       /* IN/OUT: Error code */
  UnionTab *pTab,                 /* Table to configure */
  sqlite3_stmt *pStmt,            /* SQL statement to find sources */
  int nArg,                       /* Number of entries in azArg[] array */
  const char * const *azArg,      /* Array of arguments to consider */
  char **pzErr                    /* OUT: Error message */
){
  int rc = *pRc;
  int i;
  if( rc==SQLITE_OK ){
    pTab->bHasContext = (sqlite3_column_count(pStmt)>4);
  }
  for(i=0; rc==SQLITE_OK && i<nArg; i++){
    char *zArg = unionStrdup(&rc, azArg[i]);
    if( zArg ){
      int nOpt = 0;               /* Size of option name in bytes */
      char *zOpt;                 /* Pointer to option name */
      char *zVal;                 /* Pointer to value */

      unionDequote(zArg);
      zOpt = zArg;
      while( union_isspace(*zOpt) ) zOpt++;
      zVal = zOpt;
      if( *zVal==':' ) zVal++;
      while( union_isidchar(*zVal) ) zVal++;
      nOpt = (int)(zVal-zOpt);

      while( union_isspace(*zVal) ) zVal++;
      if( *zVal=='=' ){
        zOpt[nOpt] = '\0';
        zVal++;
        while( union_isspace(*zVal) ) zVal++;
        zVal = unionStrdup(&rc, zVal);
        if( zVal ){
          unionDequote(zVal);
          if( zOpt[0]==':' ){
            /* A value to bind to the SQL statement */
            int iParam = sqlite3_bind_parameter_index(pStmt, zOpt);
            if( iParam==0 ){
              *pzErr = sqlite3_mprintf(
                  "swarmvtab: no such SQL parameter: %s", zOpt
              );
              rc = SQLITE_ERROR;
            }else{
              rc = sqlite3_bind_text(pStmt, iParam, zVal, -1, SQLITE_TRANSIENT);
            }
          }else if( nOpt==7 && 0==sqlite3_strnicmp(zOpt, "maxopen", 7) ){
            pTab->nMaxOpen = atoi(zVal);
            if( pTab->nMaxOpen<=0 ){
              *pzErr = sqlite3_mprintf("swarmvtab: illegal maxopen value");
              rc = SQLITE_ERROR;
            }
          }else if( nOpt==7 && 0==sqlite3_strnicmp(zOpt, "missing", 7) ){
            if( pTab->pNotFound ){
              *pzErr = sqlite3_mprintf(
                  "swarmvtab: duplicate \"missing\" option");
              rc = SQLITE_ERROR;
            }else{
              pTab->pNotFound = unionPreparePrintf(&rc, pzErr, pTab->db,
                  "SELECT \"%w\"(?%s)", zVal, pTab->bHasContext ? ",?" : ""
              );
            }
          }else if( nOpt==9 && 0==sqlite3_strnicmp(zOpt, "openclose", 9) ){
            if( pTab->pOpenClose ){
              *pzErr = sqlite3_mprintf(
                  "swarmvtab: duplicate \"openclose\" option");
              rc = SQLITE_ERROR;
            }else{
              pTab->pOpenClose = unionPreparePrintf(&rc, pzErr, pTab->db,
                  "SELECT \"%w\"(?,?%s)", zVal, pTab->bHasContext ? ",?" : ""
              );
            }
          }else{
            *pzErr = sqlite3_mprintf("swarmvtab: unrecognized option: %s",zOpt);
            rc = SQLITE_ERROR;
          }
          sqlite3_free(zVal);
        }
      }else{
        if( i==0 && nArg==1 ){
          pTab->pNotFound = unionPreparePrintf(&rc, pzErr, pTab->db,
              "SELECT \"%w\"(?)", zArg
          );
        }else{
          *pzErr = sqlite3_mprintf( "swarmvtab: parse error: %s", azArg[i]);
          rc = SQLITE_ERROR;
        }
      }
      sqlite3_free(zArg);
    }
  }
  *pRc = rc;
}