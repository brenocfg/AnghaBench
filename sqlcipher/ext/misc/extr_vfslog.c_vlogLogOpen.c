#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zHost ;
typedef  int /*<<< orphan*/  sqlite3_mutex ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_8__ {int nFilename; char* zFilename; scalar_t__ out; int /*<<< orphan*/  nRef; struct TYPE_8__* pNext; struct TYPE_8__** ppPrev; } ;
typedef  TYPE_1__ VLogLog ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_MUTEX_STATIC_MASTER ; 
 TYPE_1__* allLogs ; 
 scalar_t__ fopen (char*,char*) ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 TYPE_1__* sqlite3_malloc64 (int) ; 
 int /*<<< orphan*/ * sqlite3_mutex_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_strglob (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  vlogLogPrint (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlog_time () ; 

__attribute__((used)) static VLogLog *vlogLogOpen(const char *zFilename){
  int nName = (int)strlen(zFilename);
  int isJournal = 0;
  sqlite3_mutex *pMutex;
  VLogLog *pLog, *pTemp;
  sqlite3_int64 tNow = 0;
  if( nName>4 && strcmp(zFilename+nName-4,"-wal")==0 ){
    return 0;  /* Do not log wal files */
  }else
  if( nName>8 && strcmp(zFilename+nName-8,"-journal")==0 ){
    nName -= 8;
    isJournal = 1;
  }else if( nName>12 
         && sqlite3_strglob("-mj??????9??", zFilename+nName-12)==0 ){
    return 0;  /* Do not log master journal files */
  }
  pTemp = sqlite3_malloc64( sizeof(*pLog)*2 + nName + 60 );
  if( pTemp==0 ) return 0;
  pMutex = sqlite3_mutex_alloc(SQLITE_MUTEX_STATIC_MASTER);
  sqlite3_mutex_enter(pMutex);
  for(pLog=allLogs; pLog; pLog=pLog->pNext){
    if( pLog->nFilename==nName && !memcmp(pLog->zFilename, zFilename, nName) ){
      break;
    }
  }
  if( pLog==0 ){
    pLog = pTemp;
    pTemp = 0;
    memset(pLog, 0, sizeof(*pLog)*2);
    pLog->zFilename = (char*)&pLog[2];
    tNow = vlog_time();
    sqlite3_snprintf(nName+60, pLog->zFilename, "%.*s-debuglog-%lld",
                     nName, zFilename, tNow);
    pLog->out = fopen(pLog->zFilename, "a");
    if( pLog->out==0 ){
      sqlite3_mutex_leave(pMutex);
      sqlite3_free(pLog);
      return 0;
    }
    pLog->nFilename = nName;
    pLog[1].out = pLog[0].out;
    pLog->ppPrev = &allLogs;
    if( allLogs ) allLogs->ppPrev = &pLog->pNext;
    pLog->pNext = allLogs;
    allLogs = pLog;
  }
  sqlite3_mutex_leave(pMutex);
  if( pTemp ){
    sqlite3_free(pTemp);
  }else{
#if SQLITE_OS_UNIX
    char zHost[200];
    zHost[0] = 0;
    gethostname(zHost, sizeof(zHost)-1);
    zHost[sizeof(zHost)-1] = 0;
    vlogLogPrint(pLog, tNow, 0, "IDENT", getpid(), -1, zHost, 0);
#endif
  }
  if( pLog && isJournal ) pLog++;
  pLog->nRef++;
  return pLog;
}