#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct SLConn {scalar_t__ fd; int /*<<< orphan*/  iLog; } ;
struct TYPE_2__ {scalar_t__* zPrefix; char* zIdx; int /*<<< orphan*/  bReuse; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ENVIRONMENT_VARIABLE1_NAME ; 
 int /*<<< orphan*/  ENVIRONMENT_VARIABLE2_NAME ; 
 int /*<<< orphan*/  SQLITE_IOERR ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 void* fopen (char*,char*) ; 
 int /*<<< orphan*/  getProcessId () ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/  sqlite3_log (int /*<<< orphan*/ ,char*) ; 
 char* sqlite3_mprintf (char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,...) ; 
 TYPE_1__ sqllogglobal ; 
 int strlen (char*) ; 

__attribute__((used)) static void sqllogOpenlog(struct SLConn *p){
  /* If the log file has not yet been opened, open it now. */
  if( p->fd==0 ){
    char *zLog;

    /* If it is still NULL, have global.zPrefix point to a copy of 
    ** environment variable $ENVIRONMENT_VARIABLE1_NAME.  */
    if( sqllogglobal.zPrefix[0]==0 ){
      FILE *fd;
      char *zVar = getenv(ENVIRONMENT_VARIABLE1_NAME);
      if( zVar==0 || strlen(zVar)+10>=(sizeof(sqllogglobal.zPrefix)) ) return;
      sqlite3_snprintf(sizeof(sqllogglobal.zPrefix), sqllogglobal.zPrefix,
                        "%s/sqllog_%05d", zVar, getProcessId());
      sqlite3_snprintf(sizeof(sqllogglobal.zIdx), sqllogglobal.zIdx,
                        "%s.idx", sqllogglobal.zPrefix);
      if( getenv(ENVIRONMENT_VARIABLE2_NAME) ){
        sqllogglobal.bReuse = atoi(getenv(ENVIRONMENT_VARIABLE2_NAME));
      }
      fd = fopen(sqllogglobal.zIdx, "w");
      if( fd ) fclose(fd);
    }

    /* Open the log file */
    zLog = sqlite3_mprintf("%s_%05d.sql", sqllogglobal.zPrefix, p->iLog);
    p->fd = fopen(zLog, "w");
    sqlite3_free(zLog);
    if( p->fd==0 ){
      sqlite3_log(SQLITE_IOERR, "sqllogOpenlog(): Failed to open log file");
    }
  }
}