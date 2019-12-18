#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zBuf ;
struct TYPE_8__ {int /*<<< orphan*/  zVfsName; } ;
typedef  TYPE_2__ vfstrace_info ;
struct TYPE_9__ {int /*<<< orphan*/  zFName; TYPE_6__* pReal; TYPE_2__* pInfo; } ;
typedef  TYPE_3__ vfstrace_file ;
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_10__ {TYPE_1__* pMethods; } ;
struct TYPE_7__ {int (* xFileControl ) (TYPE_6__*,int,void*) ;} ;

/* Variables and functions */
#define  SQLITE_FCNTL_CHUNK_SIZE 141 
#define  SQLITE_FCNTL_FILE_POINTER 140 
#define  SQLITE_FCNTL_LOCKSTATE 139 
#define  SQLITE_FCNTL_OVERWRITE 138 
#define  SQLITE_FCNTL_PERSIST_WAL 137 
#define  SQLITE_FCNTL_PRAGMA 136 
#define  SQLITE_FCNTL_SIZE_HINT 135 
#define  SQLITE_FCNTL_SYNC_OMITTED 134 
#define  SQLITE_FCNTL_TEMPFILENAME 133 
#define  SQLITE_FCNTL_VFSNAME 132 
#define  SQLITE_FCNTL_WIN32_AV_RETRY 131 
#define  SQLITE_GET_LOCKPROXYFILE 130 
#define  SQLITE_LAST_ERRNO 129 
 int SQLITE_OK ; 
#define  SQLITE_SET_LOCKPROXYFILE 128 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,...) ; 
 int stub1 (TYPE_6__*,int,void*) ; 
 int /*<<< orphan*/  vfstrace_print_errcode (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  vfstrace_printf (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int vfstraceFileControl(sqlite3_file *pFile, int op, void *pArg){
  vfstrace_file *p = (vfstrace_file *)pFile;
  vfstrace_info *pInfo = p->pInfo;
  int rc;
  char zBuf[100];
  char *zOp;
  switch( op ){
    case SQLITE_FCNTL_LOCKSTATE:    zOp = "LOCKSTATE";          break;
    case SQLITE_GET_LOCKPROXYFILE:  zOp = "GET_LOCKPROXYFILE";  break;
    case SQLITE_SET_LOCKPROXYFILE:  zOp = "SET_LOCKPROXYFILE";  break;
    case SQLITE_LAST_ERRNO:         zOp = "LAST_ERRNO";         break;
    case SQLITE_FCNTL_SIZE_HINT: {
      sqlite3_snprintf(sizeof(zBuf), zBuf, "SIZE_HINT,%lld",
                       *(sqlite3_int64*)pArg);
      zOp = zBuf;
      break;
    }
    case SQLITE_FCNTL_CHUNK_SIZE: {
      sqlite3_snprintf(sizeof(zBuf), zBuf, "CHUNK_SIZE,%d", *(int*)pArg);
      zOp = zBuf;
      break;
    }
    case SQLITE_FCNTL_FILE_POINTER: zOp = "FILE_POINTER";       break;
    case SQLITE_FCNTL_SYNC_OMITTED: zOp = "SYNC_OMITTED";       break;
    case SQLITE_FCNTL_WIN32_AV_RETRY: zOp = "WIN32_AV_RETRY";   break;
    case SQLITE_FCNTL_PERSIST_WAL:  zOp = "PERSIST_WAL";        break;
    case SQLITE_FCNTL_OVERWRITE:    zOp = "OVERWRITE";          break;
    case SQLITE_FCNTL_VFSNAME:      zOp = "VFSNAME";            break;
    case SQLITE_FCNTL_TEMPFILENAME: zOp = "TEMPFILENAME";       break;
    case 0xca093fa0:                zOp = "DB_UNCHANGED";       break;
    case SQLITE_FCNTL_PRAGMA: {
      const char *const* a = (const char*const*)pArg;
      sqlite3_snprintf(sizeof(zBuf), zBuf, "PRAGMA,[%s,%s]",a[1],a[2]);
      zOp = zBuf;
      break;
    }
    default: {
      sqlite3_snprintf(sizeof zBuf, zBuf, "%d", op);
      zOp = zBuf;
      break;
    }
  }
  vfstrace_printf(pInfo, "%s.xFileControl(%s,%s)",
                  pInfo->zVfsName, p->zFName, zOp);
  rc = p->pReal->pMethods->xFileControl(p->pReal, op, pArg);
  vfstrace_print_errcode(pInfo, " -> %s\n", rc);
  if( op==SQLITE_FCNTL_VFSNAME && rc==SQLITE_OK ){
    *(char**)pArg = sqlite3_mprintf("vfstrace.%s/%z",
                                    pInfo->zVfsName, *(char**)pArg);
  }
  if( (op==SQLITE_FCNTL_PRAGMA || op==SQLITE_FCNTL_TEMPFILENAME)
   && rc==SQLITE_OK && *(char**)pArg ){
    vfstrace_printf(pInfo, "%s.xFileControl(%s,%s) returns %s",
                    pInfo->zVfsName, p->zFName, zOp, *(char**)pArg);
  }
  return rc;
}