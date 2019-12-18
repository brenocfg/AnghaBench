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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  aOp ;

/* Variables and functions */
 scalar_t__ SQLITE_INTEGER ; 
 int SQLITE_OK ; 
#define  SQLITE_STATUS_MALLOC_SIZE 133 
#define  SQLITE_STATUS_MEMORY_USED 132 
#define  SQLITE_STATUS_PAGECACHE_OVERFLOW 131 
#define  SQLITE_STATUS_PAGECACHE_USED 130 
#define  SQLITE_STATUS_SCRATCH_OVERFLOW 129 
#define  SQLITE_STATUS_SCRATCH_USED 128 
 scalar_t__ SQLITE_TEXT ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,...) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 
 int sqlite3_status (int,int*,int*,int) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static void statusFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  int op = 0, mx, cur, resetFlag, rc;
  if( sqlite3_value_type(argv[0])==SQLITE_INTEGER ){
    op = sqlite3_value_int(argv[0]);
  }else if( sqlite3_value_type(argv[0])==SQLITE_TEXT ){
    int i;
    const char *zName;
    static const struct {
      const char *zName;
      int op;
    } aOp[] = {
      { "MEMORY_USED",         SQLITE_STATUS_MEMORY_USED         },
      { "PAGECACHE_USED",      SQLITE_STATUS_PAGECACHE_USED      },
      { "PAGECACHE_OVERFLOW",  SQLITE_STATUS_PAGECACHE_OVERFLOW  },
      { "SCRATCH_USED",        SQLITE_STATUS_SCRATCH_USED        },
      { "SCRATCH_OVERFLOW",    SQLITE_STATUS_SCRATCH_OVERFLOW    },
      { "MALLOC_SIZE",         SQLITE_STATUS_MALLOC_SIZE         },
    };
    int nOp = sizeof(aOp)/sizeof(aOp[0]);
    zName = (const char*)sqlite3_value_text(argv[0]);
    for(i=0; i<nOp; i++){
      if( strcmp(aOp[i].zName, zName)==0 ){
        op = aOp[i].op;
        break;
      }
    }
    if( i>=nOp ){
      char *zMsg = sqlite3_mprintf("unknown status property: %s", zName);
      sqlite3_result_error(context, zMsg, -1);
      sqlite3_free(zMsg);
      return;
    }
  }else{
    sqlite3_result_error(context, "unknown status type", -1);
    return;
  }
  if( argc==2 ){
    resetFlag = sqlite3_value_int(argv[1]);
  }else{
    resetFlag = 0;
  }
  rc = sqlite3_status(op, &cur, &mx, resetFlag);
  if( rc!=SQLITE_OK ){
    char *zMsg = sqlite3_mprintf("sqlite3_status(%d,...) returns %d", op, rc);
    sqlite3_result_error(context, zMsg, -1);
    sqlite3_free(zMsg);
    return;
  } 
  if( argc==2 ){
    sqlite3_result_int(context, mx);
  }else{
    sqlite3_result_int(context, cur);
  }
}