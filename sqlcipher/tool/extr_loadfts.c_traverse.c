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
struct dirent {int d_type; int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int DT_DIR ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error_out (char*) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void traverse(
  const char *zDir,               /* Directory to traverse */
  void *pCtx,                     /* First argument passed to callback */
  void (*xCallback)(void*, const char *zPath)
){
  DIR *d;
  struct dirent *e;

  d = opendir(zDir);
  if( d==0 ) error_out("opendir()");

  for(e=readdir(d); e; e=readdir(d)){
    if( strcmp(e->d_name, ".")==0 || strcmp(e->d_name, "..")==0 ) continue;
    char *zPath = sqlite3_mprintf("%s/%s", zDir, e->d_name);
    if (e->d_type & DT_DIR) {
      traverse(zPath, pCtx, xCallback);
    }else{
      xCallback(pCtx, zPath);
    }
    sqlite3_free(zPath);
  }

  closedir(d);
}