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
typedef  int /*<<< orphan*/  x ;
struct stat {int st_size; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int PATH_DB ; 
 int PATH_DIR ; 
 int PATH_NEXIST ; 
 int PATH_OTHER ; 
 int PATH_TREE ; 
 int /*<<< orphan*/  R_OK ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*) ; 
 int stat (char const*,struct stat*) ; 

__attribute__((used)) static int pathType(const char *zPath){
  struct stat x;
  int rc;
  if( access(zPath,R_OK) ) return PATH_NEXIST;
  memset(&x, 0, sizeof(x));
  rc = stat(zPath, &x);
  if( rc<0 ) return PATH_OTHER;
  if( S_ISDIR(x.st_mode) ){
    char *zLayer1 = sqlite3_mprintf("%s/00", zPath);
    memset(&x, 0, sizeof(x));
    rc = stat(zLayer1, &x);
    sqlite3_free(zLayer1);
    if( rc<0 ) return PATH_DIR;
    if( S_ISDIR(x.st_mode) ) return PATH_TREE;
    return PATH_DIR;
  }
  if( (x.st_size%512)==0 ) return PATH_DB;
  return PATH_OTHER;
}