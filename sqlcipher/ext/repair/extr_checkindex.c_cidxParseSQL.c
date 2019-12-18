#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* zExpr; } ;
struct TYPE_4__ {void* zWhere; TYPE_2__* aCol; } ;
typedef  TYPE_1__ CidxIndex ;
typedef  int /*<<< orphan*/  CidxCursor ;
typedef  TYPE_2__ CidxColumn ;

/* Variables and functions */
 int CIDX_PARSE_CLOSE ; 
 int CIDX_PARSE_COMMA ; 
 int CIDX_PARSE_EOF ; 
 int CIDX_PARSE_OPEN ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  cidxCursorError (int /*<<< orphan*/ *,char*,char const*) ; 
 int cidxFindNext (char const*,char const**,int*) ; 
 void* cidxMprintf (int*,char*,...) ; 
 scalar_t__ cidx_isident (char const) ; 
 scalar_t__ cidx_isspace (char const) ; 
 scalar_t__ sqlite3_strnicmp (char const*,char*,int) ; 

__attribute__((used)) static int cidxParseSQL(CidxCursor *pCsr, CidxIndex *pIdx, const char *zSql){
  const char *z = zSql;
  const char *z1;
  int e;
  int rc = SQLITE_OK;
  int nParen = 1;
  int bDoNotTrim = 0;
  CidxColumn *pCol = pIdx->aCol;

  e = cidxFindNext(z, &z, &bDoNotTrim);
  if( e!=CIDX_PARSE_OPEN ) goto parse_error;
  z1 = z+1;
  z++;
  while( nParen>0 ){
    e = cidxFindNext(z, &z, &bDoNotTrim);
    if( e==CIDX_PARSE_EOF ) goto parse_error;
    if( (e==CIDX_PARSE_COMMA || e==CIDX_PARSE_CLOSE) && nParen==1 ){
      const char *z2 = z;
      if( pCol->zExpr ) goto parse_error;

      if( bDoNotTrim==0 ){
        while( cidx_isspace(z[-1]) ) z--;
        if( !sqlite3_strnicmp(&z[-3], "asc", 3) && 0==cidx_isident(z[-4]) ){
          z -= 3;
          while( cidx_isspace(z[-1]) ) z--;
        }else
          if( !sqlite3_strnicmp(&z[-4], "desc", 4) && 0==cidx_isident(z[-5]) ){
            z -= 4;
            while( cidx_isspace(z[-1]) ) z--;
          }
        while( cidx_isspace(z1[0]) ) z1++;
      }

      pCol->zExpr = cidxMprintf(&rc, "%.*s", z-z1, z1);
      pCol++;
      z = z1 = z2+1;
    }
    if( e==CIDX_PARSE_OPEN ) nParen++;
    if( e==CIDX_PARSE_CLOSE ) nParen--;
    z++;
  }

  /* Search for a WHERE clause */
  cidxFindNext(z, &z, 0);
  if( 0==sqlite3_strnicmp(z, "where", 5) ){
    pIdx->zWhere = cidxMprintf(&rc, "%s\n", &z[5]);
  }else if( z[0]!='\0' ){
    goto parse_error;
  }

  return rc;

 parse_error:
  cidxCursorError(pCsr, "Parse error in: %s", zSql);
  return SQLITE_ERROR;
}