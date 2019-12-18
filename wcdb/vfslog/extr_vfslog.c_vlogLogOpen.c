#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_mutex ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_7__ {int nFilename; char* zFilename; int lastReadOfs; int lastWriteOfs; int /*<<< orphan*/  nRef; struct TYPE_7__* pNext; struct TYPE_7__** ppPrev; void* gzMutex; scalar_t__ gzOut; scalar_t__ tmpOut; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ VLogLog ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SQLITE_MUTEX_FAST ; 
 int /*<<< orphan*/  SQLITE_MUTEX_STATIC_MASTER ; 
 TYPE_1__* allLogs ; 
 char* alloca (int) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 scalar_t__ fopen (char*,char*) ; 
 int fread (char*,int,int,scalar_t__) ; 
 scalar_t__ fseek (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gzclose (scalar_t__) ; 
 scalar_t__ gzopen (char*,char*) ; 
 int /*<<< orphan*/  gzwrite (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 TYPE_1__* sqlite3_malloc (int) ; 
 void* sqlite3_mutex_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_mutex_free (void*) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int,char const*) ; 
 scalar_t__ sqlite3_strglob (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  vlogDefaultLogFlags ; 

__attribute__((used)) static VLogLog *vlogLogOpen(const char *zFilename)
{
    int nName = (int) strlen(zFilename);
    int fileType = 0;
    sqlite3_mutex *pMutex;
    VLogLog *pLog, *pTemp;
    if (nName > 4 && strcmp(zFilename + nName - 4, "-wal") == 0) {
        nName -= 4;
        fileType = 1; /* wal */
    }

    if (nName > 8 && strcmp(zFilename + nName - 8, "-journal") == 0) {
        nName -= 8;
        fileType = 1; /* journal */
    } else if (nName > 12 &&
               sqlite3_strglob("-mj??????9??", zFilename + nName - 12) == 0) {
        return 0; /* Do not log master journal files */
    }

    pTemp = sqlite3_malloc(sizeof(*pLog) * 2 + nName + 60);
    if (pTemp == 0)
        return 0;
    pMutex = sqlite3_mutex_alloc(SQLITE_MUTEX_STATIC_MASTER);
    sqlite3_mutex_enter(pMutex);
    for (pLog = allLogs; pLog; pLog = pLog->pNext) {
        if (pLog->nFilename == nName &&
            !memcmp(pLog->zFilename, zFilename, nName)) {
            break;
        }
    }

    if (pLog == 0) {
        pLog = pTemp;
        pTemp = 0;
        memset(pLog, 0, sizeof(*pLog) * 2);
        pLog->zFilename = (char *) &pLog[2];
        sqlite3_snprintf(nName + 60, pLog->zFilename, "%.*s-vfslog", nName,
                         zFilename);

        char *tmpName = alloca(nName + 60);
        sqlite3_snprintf(nName + 60, tmpName, "%.*s-vfslo1", nName, zFilename);

        pLog->tmpOut = fopen(tmpName, "ab+");
        pLog->gzOut = gzopen(pLog->zFilename, "ab");
        pLog->gzMutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
        if (!pLog->tmpOut || !pLog->gzOut || !pLog->gzMutex) {
            if (pLog->tmpOut)
                fclose(pLog->tmpOut);
            if (pLog->gzOut)
                gzclose(pLog->gzOut);
            if (pLog->gzMutex)
                sqlite3_mutex_free(pLog->gzMutex);

            sqlite3_mutex_leave(pMutex);
            sqlite3_free(pLog);
            return 0;
        }

        /* Flush existing content in tmpOut to gzOut */
        if (fseek(pLog->tmpOut, 0, SEEK_END) > 0) {
            fseek(pLog->tmpOut, 0, SEEK_SET);
            char buf[1024];
            int ret;
            while ((ret = fread(buf, 1, sizeof(buf), pLog->tmpOut)) >= 0) {
                gzwrite(pLog->gzOut, buf, ret);
            }
            fseek(pLog->tmpOut, 0, SEEK_END);
        }

        pLog->nFilename = nName;
        pLog->flags = vlogDefaultLogFlags;
        pLog[1].tmpOut = pLog[0].tmpOut;
        pLog[1].gzOut = pLog[0].gzOut;
        pLog[1].gzMutex = pLog[0].gzMutex;
        pLog->ppPrev = &allLogs;
        if (allLogs)
            allLogs->ppPrev = &pLog->pNext;
        pLog->pNext = allLogs;
        allLogs = pLog;
    }
    sqlite3_mutex_leave(pMutex);
    if (pTemp) {
        sqlite3_free(pTemp);
    }
    if (pLog)
        pLog += fileType;
    pLog->nRef++;

    pLog->lastReadOfs = -1;
    pLog->lastWriteOfs = -1;
    return pLog;
}