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
typedef  int /*<<< orphan*/  zBuf ;
typedef  int /*<<< orphan*/  vfstrace_info ;

/* Variables and functions */
#define  SQLITE_ABORT 174 
#define  SQLITE_BUSY 173 
#define  SQLITE_BUSY_RECOVERY 172 
#define  SQLITE_CANTOPEN 171 
#define  SQLITE_CANTOPEN_NOTEMPDIR 170 
#define  SQLITE_CONSTRAINT 169 
#define  SQLITE_CORRUPT 168 
#define  SQLITE_EMPTY 167 
#define  SQLITE_ERROR 166 
#define  SQLITE_FULL 165 
#define  SQLITE_INTERRUPT 164 
#define  SQLITE_IOERR 163 
#define  SQLITE_IOERR_ACCESS 162 
#define  SQLITE_IOERR_BLOCKED 161 
#define  SQLITE_IOERR_CHECKRESERVEDLOCK 160 
#define  SQLITE_IOERR_CLOSE 159 
#define  SQLITE_IOERR_CONVPATH 158 
#define  SQLITE_IOERR_DELETE 157 
#define  SQLITE_IOERR_DIR_CLOSE 156 
#define  SQLITE_IOERR_DIR_FSYNC 155 
#define  SQLITE_IOERR_FSTAT 154 
#define  SQLITE_IOERR_FSYNC 153 
#define  SQLITE_IOERR_GETTEMPPATH 152 
#define  SQLITE_IOERR_LOCK 151 
#define  SQLITE_IOERR_NOMEM 150 
#define  SQLITE_IOERR_RDLOCK 149 
#define  SQLITE_IOERR_READ 148 
#define  SQLITE_IOERR_SEEK 147 
#define  SQLITE_IOERR_SHMLOCK 146 
#define  SQLITE_IOERR_SHMMAP 145 
#define  SQLITE_IOERR_SHMOPEN 144 
#define  SQLITE_IOERR_SHMSIZE 143 
#define  SQLITE_IOERR_SHORT_READ 142 
#define  SQLITE_IOERR_TRUNCATE 141 
#define  SQLITE_IOERR_UNLOCK 140 
#define  SQLITE_IOERR_WRITE 139 
#define  SQLITE_LOCKED_SHAREDCACHE 138 
#define  SQLITE_MISMATCH 137 
#define  SQLITE_MISUSE 136 
#define  SQLITE_NOLFS 135 
#define  SQLITE_NOMEM 134 
#define  SQLITE_OK 133 
#define  SQLITE_PERM 132 
#define  SQLITE_PROTOCOL 131 
#define  SQLITE_READONLY 130 
#define  SQLITE_READONLY_DBMOVED 129 
#define  SQLITE_SCHEMA 128 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int) ; 
 int /*<<< orphan*/  vfstrace_printf (int /*<<< orphan*/ *,char const*,char*) ; 

__attribute__((used)) static void vfstrace_print_errcode(
  vfstrace_info *pInfo,
  const char *zFormat,
  int rc
){
  char zBuf[50];
  char *zVal;
  switch( rc ){
    case SQLITE_OK:         zVal = "SQLITE_OK";          break;
    case SQLITE_ERROR:      zVal = "SQLITE_ERROR";       break;
    case SQLITE_PERM:       zVal = "SQLITE_PERM";        break;
    case SQLITE_ABORT:      zVal = "SQLITE_ABORT";       break;
    case SQLITE_BUSY:       zVal = "SQLITE_BUSY";        break;
    case SQLITE_NOMEM:      zVal = "SQLITE_NOMEM";       break;
    case SQLITE_READONLY:   zVal = "SQLITE_READONLY";    break;
    case SQLITE_INTERRUPT:  zVal = "SQLITE_INTERRUPT";   break;
    case SQLITE_IOERR:      zVal = "SQLITE_IOERR";       break;
    case SQLITE_CORRUPT:    zVal = "SQLITE_CORRUPT";     break;
    case SQLITE_FULL:       zVal = "SQLITE_FULL";        break;
    case SQLITE_CANTOPEN:   zVal = "SQLITE_CANTOPEN";    break;
    case SQLITE_PROTOCOL:   zVal = "SQLITE_PROTOCOL";    break;
    case SQLITE_EMPTY:      zVal = "SQLITE_EMPTY";       break;
    case SQLITE_SCHEMA:     zVal = "SQLITE_SCHEMA";      break;
    case SQLITE_CONSTRAINT: zVal = "SQLITE_CONSTRAINT";  break;
    case SQLITE_MISMATCH:   zVal = "SQLITE_MISMATCH";    break;
    case SQLITE_MISUSE:     zVal = "SQLITE_MISUSE";      break;
    case SQLITE_NOLFS:      zVal = "SQLITE_NOLFS";       break;
    case SQLITE_IOERR_READ:         zVal = "SQLITE_IOERR_READ";         break;
    case SQLITE_IOERR_SHORT_READ:   zVal = "SQLITE_IOERR_SHORT_READ";   break;
    case SQLITE_IOERR_WRITE:        zVal = "SQLITE_IOERR_WRITE";        break;
    case SQLITE_IOERR_FSYNC:        zVal = "SQLITE_IOERR_FSYNC";        break;
    case SQLITE_IOERR_DIR_FSYNC:    zVal = "SQLITE_IOERR_DIR_FSYNC";    break;
    case SQLITE_IOERR_TRUNCATE:     zVal = "SQLITE_IOERR_TRUNCATE";     break;
    case SQLITE_IOERR_FSTAT:        zVal = "SQLITE_IOERR_FSTAT";        break;
    case SQLITE_IOERR_UNLOCK:       zVal = "SQLITE_IOERR_UNLOCK";       break;
    case SQLITE_IOERR_RDLOCK:       zVal = "SQLITE_IOERR_RDLOCK";       break;
    case SQLITE_IOERR_DELETE:       zVal = "SQLITE_IOERR_DELETE";       break;
    case SQLITE_IOERR_BLOCKED:      zVal = "SQLITE_IOERR_BLOCKED";      break;
    case SQLITE_IOERR_NOMEM:        zVal = "SQLITE_IOERR_NOMEM";        break;
    case SQLITE_IOERR_ACCESS:       zVal = "SQLITE_IOERR_ACCESS";       break;
    case SQLITE_IOERR_CHECKRESERVEDLOCK:
                               zVal = "SQLITE_IOERR_CHECKRESERVEDLOCK"; break;
    case SQLITE_IOERR_LOCK:         zVal = "SQLITE_IOERR_LOCK";         break;
    case SQLITE_IOERR_CLOSE:        zVal = "SQLITE_IOERR_CLOSE";        break;
    case SQLITE_IOERR_DIR_CLOSE:    zVal = "SQLITE_IOERR_DIR_CLOSE";    break;
    case SQLITE_IOERR_SHMOPEN:      zVal = "SQLITE_IOERR_SHMOPEN";      break;
    case SQLITE_IOERR_SHMSIZE:      zVal = "SQLITE_IOERR_SHMSIZE";      break;
    case SQLITE_IOERR_SHMLOCK:      zVal = "SQLITE_IOERR_SHMLOCK";      break;
    case SQLITE_IOERR_SHMMAP:       zVal = "SQLITE_IOERR_SHMMAP";       break;
    case SQLITE_IOERR_SEEK:         zVal = "SQLITE_IOERR_SEEK";         break;
    case SQLITE_IOERR_GETTEMPPATH:  zVal = "SQLITE_IOERR_GETTEMPPATH";  break;
    case SQLITE_IOERR_CONVPATH:     zVal = "SQLITE_IOERR_CONVPATH";     break;
    case SQLITE_READONLY_DBMOVED:   zVal = "SQLITE_READONLY_DBMOVED";   break;
    case SQLITE_LOCKED_SHAREDCACHE: zVal = "SQLITE_LOCKED_SHAREDCACHE"; break;
    case SQLITE_BUSY_RECOVERY:      zVal = "SQLITE_BUSY_RECOVERY";      break;
    case SQLITE_CANTOPEN_NOTEMPDIR: zVal = "SQLITE_CANTOPEN_NOTEMPDIR"; break;
    default: {
       sqlite3_snprintf(sizeof(zBuf), zBuf, "%d", rc);
       zVal = zBuf;
       break;
    }
  }
  vfstrace_printf(pInfo, zFormat, zVal);
}