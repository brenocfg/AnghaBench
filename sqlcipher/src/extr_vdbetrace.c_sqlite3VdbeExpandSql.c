#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zBase ;
typedef  int /*<<< orphan*/  utf8 ;
typedef  scalar_t__ u8 ;
struct TYPE_19__ {int nVdbeExec; int /*<<< orphan*/ * aLimit; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_20__ {int nVar; TYPE_5__* aVar; TYPE_2__* db; } ;
typedef  TYPE_3__ Vdbe ;
struct TYPE_18__ {int i; int r; int nZero; } ;
struct TYPE_22__ {int flags; int* z; int n; TYPE_1__ u; TYPE_2__* db; } ;
struct TYPE_21__ {scalar_t__ accError; scalar_t__ nAlloc; } ;
typedef  TYPE_4__ StrAccum ;
typedef  TYPE_5__ Mem ;

/* Variables and functions */
 scalar_t__ ENC (TYPE_2__*) ; 
 int MEM_Blob ; 
 int MEM_Int ; 
 int MEM_Null ; 
 int MEM_Real ; 
 int MEM_Str ; 
 int MEM_Zero ; 
 size_t SQLITE_LIMIT_LENGTH ; 
 scalar_t__ SQLITE_NOMEM ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int SQLITE_TRACE_SIZE_LIMIT ; 
 scalar_t__ SQLITE_UTF8 ; 
 int /*<<< orphan*/  assert (int) ; 
 int findNextHostParameter (char const*,int*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3GetInt32 (char const*,int*) ; 
 int sqlite3Isdigit (char const) ; 
 char* sqlite3StrAccumFinish (TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3StrAccumInit (TYPE_4__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int sqlite3Strlen30 (char const*) ; 
 scalar_t__ sqlite3VdbeChangeEncoding (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3VdbeMemRelease (TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3VdbeMemSetStr (TYPE_5__*,int*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeParameterIndex (TYPE_3__*,char const*,int) ; 
 int /*<<< orphan*/  sqlite3_str_append (TYPE_4__*,char const*,int) ; 
 int /*<<< orphan*/  sqlite3_str_appendf (TYPE_4__*,char*,int,...) ; 
 int /*<<< orphan*/  sqlite3_str_reset (TYPE_4__*) ; 
 int /*<<< orphan*/  testcase (int) ; 

char *sqlite3VdbeExpandSql(
  Vdbe *p,                 /* The prepared statement being evaluated */
  const char *zRawSql      /* Raw text of the SQL statement */
){
  sqlite3 *db;             /* The database connection */
  int idx = 0;             /* Index of a host parameter */
  int nextIndex = 1;       /* Index of next ? host parameter */
  int n;                   /* Length of a token prefix */
  int nToken;              /* Length of the parameter token */
  int i;                   /* Loop counter */
  Mem *pVar;               /* Value of a host parameter */
  StrAccum out;            /* Accumulate the output here */
#ifndef SQLITE_OMIT_UTF16
  Mem utf8;                /* Used to convert UTF16 into UTF8 for display */
#endif
  char zBase[100];         /* Initial working space */

  db = p->db;
  sqlite3StrAccumInit(&out, 0, zBase, sizeof(zBase), 
                      db->aLimit[SQLITE_LIMIT_LENGTH]);
  if( db->nVdbeExec>1 ){
    while( *zRawSql ){
      const char *zStart = zRawSql;
      while( *(zRawSql++)!='\n' && *zRawSql );
      sqlite3_str_append(&out, "-- ", 3);
      assert( (zRawSql - zStart) > 0 );
      sqlite3_str_append(&out, zStart, (int)(zRawSql-zStart));
    }
  }else if( p->nVar==0 ){
    sqlite3_str_append(&out, zRawSql, sqlite3Strlen30(zRawSql));
  }else{
    while( zRawSql[0] ){
      n = findNextHostParameter(zRawSql, &nToken);
      assert( n>0 );
      sqlite3_str_append(&out, zRawSql, n);
      zRawSql += n;
      assert( zRawSql[0] || nToken==0 );
      if( nToken==0 ) break;
      if( zRawSql[0]=='?' ){
        if( nToken>1 ){
          assert( sqlite3Isdigit(zRawSql[1]) );
          sqlite3GetInt32(&zRawSql[1], &idx);
        }else{
          idx = nextIndex;
        }
      }else{
        assert( zRawSql[0]==':' || zRawSql[0]=='$' ||
                zRawSql[0]=='@' || zRawSql[0]=='#' );
        testcase( zRawSql[0]==':' );
        testcase( zRawSql[0]=='$' );
        testcase( zRawSql[0]=='@' );
        testcase( zRawSql[0]=='#' );
        idx = sqlite3VdbeParameterIndex(p, zRawSql, nToken);
        assert( idx>0 );
      }
      zRawSql += nToken;
      nextIndex = idx + 1;
      assert( idx>0 && idx<=p->nVar );
      pVar = &p->aVar[idx-1];
      if( pVar->flags & MEM_Null ){
        sqlite3_str_append(&out, "NULL", 4);
      }else if( pVar->flags & MEM_Int ){
        sqlite3_str_appendf(&out, "%lld", pVar->u.i);
      }else if( pVar->flags & MEM_Real ){
        sqlite3_str_appendf(&out, "%!.15g", pVar->u.r);
      }else if( pVar->flags & MEM_Str ){
        int nOut;  /* Number of bytes of the string text to include in output */
#ifndef SQLITE_OMIT_UTF16
        u8 enc = ENC(db);
        if( enc!=SQLITE_UTF8 ){
          memset(&utf8, 0, sizeof(utf8));
          utf8.db = db;
          sqlite3VdbeMemSetStr(&utf8, pVar->z, pVar->n, enc, SQLITE_STATIC);
          if( SQLITE_NOMEM==sqlite3VdbeChangeEncoding(&utf8, SQLITE_UTF8) ){
            out.accError = SQLITE_NOMEM;
            out.nAlloc = 0;
          }
          pVar = &utf8;
        }
#endif
        nOut = pVar->n;
#ifdef SQLITE_TRACE_SIZE_LIMIT
        if( nOut>SQLITE_TRACE_SIZE_LIMIT ){
          nOut = SQLITE_TRACE_SIZE_LIMIT;
          while( nOut<pVar->n && (pVar->z[nOut]&0xc0)==0x80 ){ nOut++; }
        }
#endif    
        sqlite3_str_appendf(&out, "'%.*q'", nOut, pVar->z);
#ifdef SQLITE_TRACE_SIZE_LIMIT
        if( nOut<pVar->n ){
          sqlite3_str_appendf(&out, "/*+%d bytes*/", pVar->n-nOut);
        }
#endif
#ifndef SQLITE_OMIT_UTF16
        if( enc!=SQLITE_UTF8 ) sqlite3VdbeMemRelease(&utf8);
#endif
      }else if( pVar->flags & MEM_Zero ){
        sqlite3_str_appendf(&out, "zeroblob(%d)", pVar->u.nZero);
      }else{
        int nOut;  /* Number of bytes of the blob to include in output */
        assert( pVar->flags & MEM_Blob );
        sqlite3_str_append(&out, "x'", 2);
        nOut = pVar->n;
#ifdef SQLITE_TRACE_SIZE_LIMIT
        if( nOut>SQLITE_TRACE_SIZE_LIMIT ) nOut = SQLITE_TRACE_SIZE_LIMIT;
#endif
        for(i=0; i<nOut; i++){
          sqlite3_str_appendf(&out, "%02x", pVar->z[i]&0xff);
        }
        sqlite3_str_append(&out, "'", 1);
#ifdef SQLITE_TRACE_SIZE_LIMIT
        if( nOut<pVar->n ){
          sqlite3_str_appendf(&out, "/*+%d bytes*/", pVar->n-nOut);
        }
#endif
      }
    }
  }
  if( out.accError ) sqlite3_str_reset(&out);
  return sqlite3StrAccumFinish(&out);
}