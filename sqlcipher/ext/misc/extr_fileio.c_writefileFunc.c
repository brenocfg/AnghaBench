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
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  scalar_t__ mode_t ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ SQLITE_OK ; 
 scalar_t__ S_ISDIR (scalar_t__) ; 
 scalar_t__ S_ISLNK (scalar_t__) ; 
 int /*<<< orphan*/  ctxErrorMsg (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ errno ; 
 scalar_t__ makeDirectory (char const*) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ sqlite3_value_int (int /*<<< orphan*/ *) ; 
 int sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int writeFile (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void writefileFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  const char *zFile;
  mode_t mode = 0;
  int res;
  sqlite3_int64 mtime = -1;

  if( argc<2 || argc>4 ){
    sqlite3_result_error(context, 
        "wrong number of arguments to function writefile()", -1
    );
    return;
  }

  zFile = (const char*)sqlite3_value_text(argv[0]);
  if( zFile==0 ) return;
  if( argc>=3 ){
    mode = (mode_t)sqlite3_value_int(argv[2]);
  }
  if( argc==4 ){
    mtime = sqlite3_value_int64(argv[3]);
  }

  res = writeFile(context, zFile, argv[1], mode, mtime);
  if( res==1 && errno==ENOENT ){
    if( makeDirectory(zFile)==SQLITE_OK ){
      res = writeFile(context, zFile, argv[1], mode, mtime);
    }
  }

  if( argc>2 && res!=0 ){
    if( S_ISLNK(mode) ){
      ctxErrorMsg(context, "failed to create symlink: %s", zFile);
    }else if( S_ISDIR(mode) ){
      ctxErrorMsg(context, "failed to create directory: %s", zFile);
    }else{
      ctxErrorMsg(context, "failed to write file: %s", zFile);
    }
  }
}