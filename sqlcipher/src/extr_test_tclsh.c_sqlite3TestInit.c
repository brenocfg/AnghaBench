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
struct rlimit {int /*<<< orphan*/  rlim_max; int /*<<< orphan*/  rlim_cur; } ;
typedef  int /*<<< orphan*/  Tcl_Interp ;
typedef  int /*<<< orphan*/  Tcl_CmdInfo ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_CORE ; 
 int /*<<< orphan*/  Tcl_CreateObjCommand (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Tcl_GetCommandInfo (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  load_testfixture_extensions ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

const char *sqlite3TestInit(Tcl_Interp *interp){
  extern int Sqlite3_Init(Tcl_Interp*);
  extern int Sqliteconfig_Init(Tcl_Interp*);
  extern int Sqlitetest1_Init(Tcl_Interp*);
  extern int Sqlitetest2_Init(Tcl_Interp*);
  extern int Sqlitetest3_Init(Tcl_Interp*);
  extern int Sqlitetest4_Init(Tcl_Interp*);
  extern int Sqlitetest5_Init(Tcl_Interp*);
  extern int Sqlitetest6_Init(Tcl_Interp*);
  extern int Sqlitetest7_Init(Tcl_Interp*);
  extern int Sqlitetest8_Init(Tcl_Interp*);
  extern int Sqlitetest9_Init(Tcl_Interp*);
  extern int Sqlitetestasync_Init(Tcl_Interp*);
  extern int Sqlitetest_autoext_Init(Tcl_Interp*);
  extern int Sqlitetest_blob_Init(Tcl_Interp*);
  extern int Sqlitetest_demovfs_Init(Tcl_Interp *);
  extern int Sqlitetest_func_Init(Tcl_Interp*);
  extern int Sqlitetest_hexio_Init(Tcl_Interp*);
  extern int Sqlitetest_init_Init(Tcl_Interp*);
  extern int Sqlitetest_malloc_Init(Tcl_Interp*);
  extern int Sqlitetest_mutex_Init(Tcl_Interp*);
  extern int Sqlitetestschema_Init(Tcl_Interp*);
  extern int Sqlitetestsse_Init(Tcl_Interp*);
  extern int Sqlitetesttclvar_Init(Tcl_Interp*);
  extern int Sqlitetestfs_Init(Tcl_Interp*);
  extern int SqlitetestThread_Init(Tcl_Interp*);
  extern int SqlitetestOnefile_Init();
  extern int SqlitetestOsinst_Init(Tcl_Interp*);
  extern int Sqlitetestbackup_Init(Tcl_Interp*);
  extern int Sqlitetestintarray_Init(Tcl_Interp*);
  extern int Sqlitetestvfs_Init(Tcl_Interp *);
  extern int Sqlitetestrtree_Init(Tcl_Interp*);
  extern int Sqlitequota_Init(Tcl_Interp*);
  extern int Sqlitemultiplex_Init(Tcl_Interp*);
  extern int SqliteSuperlock_Init(Tcl_Interp*);
  extern int SqlitetestSyscall_Init(Tcl_Interp*);
#if defined(SQLITE_ENABLE_SESSION) && defined(SQLITE_ENABLE_PREUPDATE_HOOK)
  extern int TestSession_Init(Tcl_Interp*);
#endif
  extern int Md5_Init(Tcl_Interp*);
  extern int Fts5tcl_Init(Tcl_Interp *);
  extern int SqliteRbu_Init(Tcl_Interp*);
  extern int Sqlitetesttcl_Init(Tcl_Interp*);
#if defined(SQLITE_ENABLE_FTS3) || defined(SQLITE_ENABLE_FTS4)
  extern int Sqlitetestfts3_Init(Tcl_Interp *interp);
#endif
#ifdef SQLITE_ENABLE_ZIPVFS
  extern int Zipvfs_Init(Tcl_Interp*);
#endif
  extern int TestExpert_Init(Tcl_Interp*);
  extern int Sqlitetest_window_Init(Tcl_Interp *);
  extern int Sqlitetestvdbecov_Init(Tcl_Interp *);

  Tcl_CmdInfo cmdInfo;

  /* Since the primary use case for this binary is testing of SQLite,
  ** be sure to generate core files if we crash */
#if defined(unix)
  { struct rlimit x;
    getrlimit(RLIMIT_CORE, &x);
    x.rlim_cur = x.rlim_max;
    setrlimit(RLIMIT_CORE, &x);
  }
#endif /* unix */

  if( Tcl_GetCommandInfo(interp, "sqlite3", &cmdInfo)==0 ){
    Sqlite3_Init(interp);
  }
#ifdef SQLITE_ENABLE_ZIPVFS
  Zipvfs_Init(interp);
#endif
  Md5_Init(interp);
  Sqliteconfig_Init(interp);
  Sqlitetest1_Init(interp);
  Sqlitetest2_Init(interp);
  Sqlitetest3_Init(interp);
  Sqlitetest4_Init(interp);
  Sqlitetest5_Init(interp);
  Sqlitetest6_Init(interp);
  Sqlitetest7_Init(interp);
  Sqlitetest8_Init(interp);
  Sqlitetest9_Init(interp);
  Sqlitetestasync_Init(interp);
  Sqlitetest_autoext_Init(interp);
  Sqlitetest_blob_Init(interp);
  Sqlitetest_demovfs_Init(interp);
  Sqlitetest_func_Init(interp);
  Sqlitetest_hexio_Init(interp);
  Sqlitetest_init_Init(interp);
  Sqlitetest_malloc_Init(interp);
  Sqlitetest_mutex_Init(interp);
  Sqlitetestschema_Init(interp);
  Sqlitetesttclvar_Init(interp);
  Sqlitetestfs_Init(interp);
  SqlitetestThread_Init(interp);
  SqlitetestOnefile_Init();
  SqlitetestOsinst_Init(interp);
  Sqlitetestbackup_Init(interp);
  Sqlitetestintarray_Init(interp);
  Sqlitetestvfs_Init(interp);
  Sqlitetestrtree_Init(interp);
  Sqlitequota_Init(interp);
  Sqlitemultiplex_Init(interp);
  SqliteSuperlock_Init(interp);
  SqlitetestSyscall_Init(interp);
#if defined(SQLITE_ENABLE_SESSION) && defined(SQLITE_ENABLE_PREUPDATE_HOOK)
  TestSession_Init(interp);
#endif
  Fts5tcl_Init(interp);
  SqliteRbu_Init(interp);
  Sqlitetesttcl_Init(interp);

#if defined(SQLITE_ENABLE_FTS3) || defined(SQLITE_ENABLE_FTS4)
  Sqlitetestfts3_Init(interp);
#endif
  TestExpert_Init(interp);
  Sqlitetest_window_Init(interp);
  Sqlitetestvdbecov_Init(interp);

  Tcl_CreateObjCommand(
      interp, "load_testfixture_extensions", load_testfixture_extensions,0,0
  );
  return 0;
}