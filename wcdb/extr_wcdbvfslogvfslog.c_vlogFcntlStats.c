#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lastJournalWriteOffset; int /*<<< orphan*/  lastJournalReadOffset; int /*<<< orphan*/  lastMainWriteOffset; int /*<<< orphan*/  lastMainReadOffset; } ;
typedef  TYPE_1__ VLogStat ;
struct TYPE_7__ {scalar_t__ nFilename; int /*<<< orphan*/  gzMutex; int /*<<< orphan*/  lastWriteOfs; int /*<<< orphan*/  lastReadOfs; } ;
typedef  TYPE_2__ VLogLog ;
struct TYPE_8__ {TYPE_2__* pLog; } ;
typedef  TYPE_3__ VLogFile ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlogFcntlStats(VLogFile *p, VLogStat *stats)
{
    VLogLog *pLog = p->pLog;

    /* Ensure we are operating on the main DB file. */
    if (p->pLog->nFilename == 0)
        return SQLITE_ERROR;

    sqlite3_mutex_enter(pLog->gzMutex);
    stats->lastMainReadOffset = pLog->lastReadOfs;
    stats->lastMainWriteOffset = pLog->lastWriteOfs;

    /* Move to the journal file. */
    pLog++;
    stats->lastJournalReadOffset = pLog->lastReadOfs;
    stats->lastJournalWriteOffset = pLog->lastWriteOfs;
    sqlite3_mutex_leave(pLog->gzMutex);

    return SQLITE_OK;
}