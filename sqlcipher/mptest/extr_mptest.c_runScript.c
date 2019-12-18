#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zError ;
typedef  int /*<<< orphan*/  zCmd ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sResult ;
typedef  int /*<<< orphan*/  azArg ;
struct TYPE_8__ {int iTrace; int bIgnoreSqlErrors; int /*<<< orphan*/  nTest; int /*<<< orphan*/  db; } ;
struct TYPE_7__ {int n; int /*<<< orphan*/  z; } ;
typedef  TYPE_1__ String ;

/* Variables and functions */
 scalar_t__ ISSPACE (char) ; 
 int MX_ARG ; 
 int SQLITE_ROW ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  booleanValue (char*) ; 
 int /*<<< orphan*/  errorMessage (char*,int,char*,...) ; 
 int /*<<< orphan*/  evalSql (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int extractToken (char*,int,char*,int) ; 
 int /*<<< orphan*/  filenameTail (char*) ; 
 int findEnd (char*,int*) ; 
 scalar_t__ findEndif (char*,int,int*) ; 
 int /*<<< orphan*/  finishScript (int,int,int) ; 
 TYPE_5__ g ; 
 int /*<<< orphan*/  isDirSep (char) ; 
 int /*<<< orphan*/  isalpha (char) ; 
 int /*<<< orphan*/  logMessage (char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * prepareSql (char*,int,char*) ; 
 char* readFile (char*) ; 
 int /*<<< orphan*/  runSql (char*,...) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,...) ; 
 int /*<<< orphan*/  sqlite3_sleep (int) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int,char*) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_strglob (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  startClient (int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  stringFree (TYPE_1__*) ; 
 int /*<<< orphan*/  stringReset (TYPE_1__*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  test_breakpoint () ; 
 int tokenLength (char*,int*) ; 
 int /*<<< orphan*/  waitForClient (int,int,char*) ; 

__attribute__((used)) static void runScript(
  int iClient,       /* The client number, or 0 for the master */
  int taskId,        /* The task ID for clients.  0 for master */
  char *zScript,     /* Text of the script */
  char *zFilename    /* File from which script was read. */
){
  int lineno = 1;
  int prevLine = 1;
  int ii = 0;
  int iBegin = 0;
  int n, c, j;
  int len;
  int nArg;
  String sResult;
  char zCmd[30];
  char zError[1000];
  char azArg[MX_ARG][100];

  memset(&sResult, 0, sizeof(sResult));
  stringReset(&sResult);
  while( (c = zScript[ii])!=0 ){
    prevLine = lineno;
    len = tokenLength(zScript+ii, &lineno);
    if( ISSPACE(c) || (c=='/' && zScript[ii+1]=='*') ){
      ii += len;
      continue;
    }
    if( c!='-' || zScript[ii+1]!='-' || !isalpha(zScript[ii+2]) ){
      ii += len;
      continue;
    }

    /* Run any prior SQL before processing the new --command */
    if( ii>iBegin ){
      char *zSql = sqlite3_mprintf("%.*s", ii-iBegin, zScript+iBegin);
      evalSql(&sResult, zSql);
      sqlite3_free(zSql);
      iBegin = ii + len;
    }

    /* Parse the --command */
    if( g.iTrace>=2 ) logMessage("%.*s", len, zScript+ii);
    n = extractToken(zScript+ii+2, len-2, zCmd, sizeof(zCmd));
    for(nArg=0; n<len-2 && nArg<MX_ARG; nArg++){
      while( n<len-2 && ISSPACE(zScript[ii+2+n]) ){ n++; }
      if( n>=len-2 ) break;
      n += extractToken(zScript+ii+2+n, len-2-n,
                        azArg[nArg], sizeof(azArg[nArg]));
    }
    for(j=nArg; j<MX_ARG; j++) azArg[j++][0] = 0;

    /*
    **  --sleep N
    **
    ** Pause for N milliseconds
    */
    if( strcmp(zCmd, "sleep")==0 ){
      sqlite3_sleep(atoi(azArg[0]));
    }else 

    /*
    **   --exit N
    **
    ** Exit this process.  If N>0 then exit without shutting down
    ** SQLite.  (In other words, simulate a crash.)
    */
    if( strcmp(zCmd, "exit")==0 ){
      int rc = atoi(azArg[0]);
      finishScript(iClient, taskId, 1);
      if( rc==0 ) sqlite3_close(g.db);
      exit(rc);
    }else

    /*
    **   --testcase NAME
    **
    ** Begin a new test case.  Announce in the log that the test case
    ** has begun.
    */
    if( strcmp(zCmd, "testcase")==0 ){
      if( g.iTrace==1 ) logMessage("%.*s", len - 1, zScript+ii);
      stringReset(&sResult);
    }else

    /*
    **   --finish
    **
    ** Mark the current task as having finished, even if it is not.
    ** This can be used in conjunction with --exit to simulate a crash.
    */
    if( strcmp(zCmd, "finish")==0 && iClient>0 ){
      finishScript(iClient, taskId, 1);
    }else

    /*
    **  --reset
    **
    ** Reset accumulated results back to an empty string
    */
    if( strcmp(zCmd, "reset")==0 ){
      stringReset(&sResult);
    }else

    /*
    **  --match ANSWER...
    **
    ** Check to see if output matches ANSWER.  Report an error if not.
    */
    if( strcmp(zCmd, "match")==0 ){
      int jj;
      char *zAns = zScript+ii;
      for(jj=7; jj<len-1 && ISSPACE(zAns[jj]); jj++){}
      zAns += jj;
      if( len-jj-1!=sResult.n || strncmp(sResult.z, zAns, len-jj-1) ){
        errorMessage("line %d of %s:\nExpected [%.*s]\n     Got [%s]",
          prevLine, zFilename, len-jj-1, zAns, sResult.z);
      }
      g.nTest++;
      stringReset(&sResult);
    }else

    /*
    **  --glob ANSWER...
    **  --notglob ANSWER....
    **
    ** Check to see if output does or does not match the glob pattern
    ** ANSWER.
    */
    if( strcmp(zCmd, "glob")==0 || strcmp(zCmd, "notglob")==0 ){
      int jj;
      char *zAns = zScript+ii;
      char *zCopy;
      int isGlob = (zCmd[0]=='g');
      for(jj=9-3*isGlob; jj<len-1 && ISSPACE(zAns[jj]); jj++){}
      zAns += jj;
      zCopy = sqlite3_mprintf("%.*s", len-jj-1, zAns);
      if( (sqlite3_strglob(zCopy, sResult.z)==0)^isGlob ){
        errorMessage("line %d of %s:\nExpected [%s]\n     Got [%s]",
          prevLine, zFilename, zCopy, sResult.z);
      }
      sqlite3_free(zCopy);
      g.nTest++;
      stringReset(&sResult);
    }else

    /*
    **  --output
    **
    ** Output the result of the previous SQL.
    */
    if( strcmp(zCmd, "output")==0 ){
      logMessage("%s", sResult.z);
    }else

    /*
    **  --source FILENAME
    **
    ** Run a subscript from a separate file.
    */
    if( strcmp(zCmd, "source")==0 ){
      char *zNewFile, *zNewScript;
      char *zToDel = 0;
      zNewFile = azArg[0];
      if( !isDirSep(zNewFile[0]) ){
        int k;
        for(k=(int)strlen(zFilename)-1; k>=0 && !isDirSep(zFilename[k]); k--){}
        if( k>0 ){
          zNewFile = zToDel = sqlite3_mprintf("%.*s/%s", k,zFilename,zNewFile);
        }
      }
      zNewScript = readFile(zNewFile);
      if( g.iTrace ) logMessage("begin script [%s]\n", zNewFile);
      runScript(0, 0, zNewScript, zNewFile);
      sqlite3_free(zNewScript);
      if( g.iTrace ) logMessage("end script [%s]\n", zNewFile);
      sqlite3_free(zToDel);
    }else

    /*
    **  --print MESSAGE....
    **
    ** Output the remainder of the line to the log file
    */
    if( strcmp(zCmd, "print")==0 ){
      int jj;
      for(jj=7; jj<len && ISSPACE(zScript[ii+jj]); jj++){}
      logMessage("%.*s", len-jj, zScript+ii+jj);
    }else

    /*
    **  --if EXPR
    **
    ** Skip forward to the next matching --endif or --else if EXPR is false.
    */
    if( strcmp(zCmd, "if")==0 ){
      int jj, rc;
      sqlite3_stmt *pStmt;
      for(jj=4; jj<len && ISSPACE(zScript[ii+jj]); jj++){}
      pStmt = prepareSql("SELECT %.*s", len-jj, zScript+ii+jj);
      rc = sqlite3_step(pStmt);
      if( rc!=SQLITE_ROW || sqlite3_column_int(pStmt, 0)==0 ){
        ii += findEndif(zScript+ii+len, 1, &lineno);
      }
      sqlite3_finalize(pStmt);
    }else

    /*
    **  --else
    **
    ** This command can only be encountered if currently inside an --if that
    ** is true.  Skip forward to the next matching --endif.
    */
    if( strcmp(zCmd, "else")==0 ){
      ii += findEndif(zScript+ii+len, 0, &lineno);
    }else

    /*
    **  --endif
    **
    ** This command can only be encountered if currently inside an --if that
    ** is true or an --else of a false if.  This is a no-op.
    */
    if( strcmp(zCmd, "endif")==0 ){
      /* no-op */
    }else

    /*
    **  --start CLIENT
    **
    ** Start up the given client.
    */
    if( strcmp(zCmd, "start")==0 && iClient==0 ){
      int iNewClient = atoi(azArg[0]);
      if( iNewClient>0 ){
        startClient(iNewClient);
      }
    }else

    /*
    **  --wait CLIENT TIMEOUT
    **
    ** Wait until all tasks complete for the given client.  If CLIENT is
    ** "all" then wait for all clients to complete.  Wait no longer than
    ** TIMEOUT milliseconds (default 10,000)
    */
    if( strcmp(zCmd, "wait")==0 && iClient==0 ){
      int iTimeout = nArg>=2 ? atoi(azArg[1]) : 10000;
      sqlite3_snprintf(sizeof(zError),zError,"line %d of %s\n",
                       prevLine, zFilename);
      waitForClient(atoi(azArg[0]), iTimeout, zError);
    }else

    /*
    **  --task CLIENT
    **     <task-content-here>
    **  --end
    **
    ** Assign work to a client.  Start the client if it is not running
    ** already.
    */
    if( strcmp(zCmd, "task")==0 && iClient==0 ){
      int iTarget = atoi(azArg[0]);
      int iEnd;
      char *zTask;
      char *zTName;
      iEnd = findEnd(zScript+ii+len, &lineno);
      if( iTarget<0 ){
        errorMessage("line %d of %s: bad client number: %d",
                     prevLine, zFilename, iTarget);
      }else{
        zTask = sqlite3_mprintf("%.*s", iEnd, zScript+ii+len);
        if( nArg>1 ){
          zTName = sqlite3_mprintf("%s", azArg[1]);
        }else{
          zTName = sqlite3_mprintf("%s:%d", filenameTail(zFilename), prevLine);
        }
        startClient(iTarget);
        runSql("INSERT INTO task(client,script,name)"
               " VALUES(%d,'%q',%Q)", iTarget, zTask, zTName);
        sqlite3_free(zTask);
        sqlite3_free(zTName);
      }
      iEnd += tokenLength(zScript+ii+len+iEnd, &lineno);
      len += iEnd;
      iBegin = ii+len;
    }else

    /*
    **  --breakpoint
    **
    ** This command calls "test_breakpoint()" which is a routine provided
    ** as a convenient place to set a debugger breakpoint.
    */
    if( strcmp(zCmd, "breakpoint")==0 ){
      test_breakpoint();
    }else

    /*
    **  --show-sql-errors BOOLEAN
    **
    ** Turn display of SQL errors on and off.
    */
    if( strcmp(zCmd, "show-sql-errors")==0 ){
      g.bIgnoreSqlErrors = nArg>=1 ? !booleanValue(azArg[0]) : 1;
    }else


    /* error */{
      errorMessage("line %d of %s: unknown command --%s",
                   prevLine, zFilename, zCmd);
    }
    ii += len;
  }
  if( iBegin<ii ){
    char *zSql = sqlite3_mprintf("%.*s", ii-iBegin, zScript+iBegin);
    runSql(zSql);
    sqlite3_free(zSql);
  }
  stringFree(&sResult);
}