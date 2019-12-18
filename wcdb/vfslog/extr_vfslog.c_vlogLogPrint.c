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
typedef  int /*<<< orphan*/  z3 ;
typedef  int /*<<< orphan*/  z2 ;
typedef  int /*<<< orphan*/  z1 ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  buf ;
typedef  int VLogOp ;
struct TYPE_3__ {int flags; scalar_t__ zFilename; int /*<<< orphan*/  gzMutex; int /*<<< orphan*/  tmpOut; int /*<<< orphan*/  gzOut; } ;
typedef  TYPE_1__ VLogLog ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ VFSLOG_GZIP_BLOCK_SIZE ; 
 int /*<<< orphan*/ * VLOG_OPNAME ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ftell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftruncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gzflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gzwrite (int /*<<< orphan*/ ,char*,int) ; 
 int snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char*,char*,int) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int,...) ; 

__attribute__((used)) static void vlogLogPrint(VLogLog *pLog,         /* The log file to write into */
                         sqlite3_int64 tStart,  /* Start time of system call */
                         sqlite3_int64 tElapse, /* Elapse time of system call */
                         VLogOp iOp,            /* Type of system call */
                         sqlite3_int64 iArg1,   /* First argument */
                         sqlite3_int64 iArg2,   /* Second argument */
                         const char *zArg3,     /* Third argument */
                         int iRes               /* Result */
                         )
{
    if (!pLog || (pLog->flags & (1 << iOp)) == 0)
        return;

    char z1[40], z2[40], z3[1024];
    if (iArg1 >= 0) {
        sqlite3_snprintf(sizeof(z1), z1, "%lld", iArg1);
    } else {
        z1[0] = 0;
    }
    if (iArg2 >= 0) {
        sqlite3_snprintf(sizeof(z2), z2, "%lld", iArg2);
    } else {
        z2[0] = 0;
    }
    if (zArg3) {
        sqlite3_snprintf(sizeof(z3), z3, "\"%.*w\"", sizeof(z3) - 4, zArg3);
    } else {
        z3[0] = 0;
    }

    char buf[2048];
    int len = snprintf(buf, sizeof(buf), "%lld,%lld,%s,%d,%s,%s,%s,%d\n",
                       tStart, tElapse, VLOG_OPNAME[iOp], pLog->zFilename == 0,
                       z1, z2, z3, iRes);

    sqlite3_mutex_enter(pLog->gzMutex);
    fwrite(buf, 1, len, pLog->tmpOut);
    fflush(pLog->tmpOut);
    gzwrite(pLog->gzOut, buf, len);
    if (ftell(pLog->tmpOut) >= VFSLOG_GZIP_BLOCK_SIZE) {
        gzflush(pLog->gzOut, Z_FINISH);
        fseek(pLog->tmpOut, 0, SEEK_SET);
        ftruncate(fileno(pLog->tmpOut), 0);
    }
    sqlite3_mutex_leave(pLog->gzMutex);
}