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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  cx ;
struct TYPE_3__ {char execCnt; int nCb; scalar_t__ mxInterval; int /*<<< orphan*/  db; scalar_t__ iLastCb; scalar_t__ iCutoffTime; } ;
typedef  TYPE_1__ FuzzCtx ;

/* Variables and functions */
 int FUZZ_SHOW_ERRORS ; 
 int FUZZ_SHOW_MAX_DELAY ; 
 int /*<<< orphan*/  SQLITE_DBCONFIG_ENABLE_FKEY ; 
 int /*<<< orphan*/  SQLITE_LIMIT_LENGTH ; 
 int /*<<< orphan*/  SQLITE_LIMIT_VDBE_OP ; 
 int SQLITE_OPEN_CREATE ; 
 int SQLITE_OPEN_MEMORY ; 
 int SQLITE_OPEN_READWRITE ; 
 int /*<<< orphan*/  block_debug_pragmas ; 
 int /*<<< orphan*/  exec_handler ; 
 int mDebug ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  progress_handler ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_complete (char*) ; 
 int /*<<< orphan*/  sqlite3_db_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int*) ; 
 int /*<<< orphan*/  sqlite3_exec (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,char**) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 scalar_t__ sqlite3_initialize () ; 
 int /*<<< orphan*/  sqlite3_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* sqlite3_mprintf (char*,int,char const*) ; 
 int sqlite3_open_v2 (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_progress_handler (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sqlite3_set_authorizer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ timeOfDay () ; 

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  char *zErrMsg = 0;       /* Error message returned by sqlite_exec() */
  uint8_t uSelector;       /* First byte of input data[] */
  int rc;                  /* Return code from various interfaces */
  char *zSql;              /* Zero-terminated copy of data[] */
  FuzzCtx cx;              /* Fuzzing context */

  memset(&cx, 0, sizeof(cx));
  if( size<3 ) return 0;   /* Early out if unsufficient data */

  /* Extract the selector byte from the beginning of the input.  But only
  ** do this if the second byte is a \n.  If the second byte is not \n,
  ** then use a default selector */
  if( data[1]=='\n' ){
    uSelector = data[0];  data += 2; size -= 2;
  }else{
    uSelector = 0xfd;
  }

  /* Open the database connection.  Only use an in-memory database. */
  if( sqlite3_initialize() ) return 0;
  rc = sqlite3_open_v2("fuzz.db", &cx.db,
           SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_MEMORY, 0);
  if( rc ) return 0;

  /* Invoke the progress handler frequently to check to see if we
  ** are taking too long.  The progress handler will return true
  ** (which will block further processing) if more than 10 seconds have
  ** elapsed since the start of the test.
  */
  cx.iLastCb = timeOfDay();
  cx.iCutoffTime = cx.iLastCb + 10000;  /* Now + 10 seconds */
#ifndef SQLITE_OMIT_PROGRESS_CALLBACK
  sqlite3_progress_handler(cx.db, 10, progress_handler, (void*)&cx);
#endif

  /* Set a limit on the maximum size of a prepared statement */
  sqlite3_limit(cx.db, SQLITE_LIMIT_VDBE_OP, 25000);

  /* Set a limit on the maximum length of a string or BLOB.  Without this
  ** limit, fuzzers will invoke randomblob(N) for a large N, and the process
  ** will timeout trying to generate the huge blob */
  sqlite3_limit(cx.db, SQLITE_LIMIT_LENGTH, 50000);

  /* Bit 1 of the selector enables foreign key constraints */
  sqlite3_db_config(cx.db, SQLITE_DBCONFIG_ENABLE_FKEY, uSelector&1, &rc);
  uSelector >>= 1;

  /* Do not allow debugging pragma statements that might cause excess output */
  sqlite3_set_authorizer(cx.db, block_debug_pragmas, 0);

  /* Remaining bits of the selector determine a limit on the number of
  ** output rows */
  cx.execCnt = uSelector + 1;

  /* Run the SQL.  The sqlite_exec() interface expects a zero-terminated
  ** string, so make a copy. */
  zSql = sqlite3_mprintf("%.*s", (int)size, data);
#ifndef SQLITE_OMIT_COMPLETE
  sqlite3_complete(zSql);
#endif
  sqlite3_exec(cx.db, zSql, exec_handler, (void*)&cx, &zErrMsg);

  /* Show any errors */
  if( (mDebug & FUZZ_SHOW_ERRORS)!=0 && zErrMsg ){
    printf("Error: %s\n", zErrMsg);
  }

  /* Cleanup and return */
  sqlite3_free(zErrMsg);
  sqlite3_free(zSql);
  sqlite3_exec(cx.db, "PRAGMA temp_store_directory=''", 0, 0, 0);
  sqlite3_close(cx.db);

  if( mDebug & FUZZ_SHOW_MAX_DELAY ){
    printf("Progress callback count....... %d\n", cx.nCb);
    printf("Max time between callbacks.... %d ms\n", (int)cx.mxInterval);
  }
  return 0;
}