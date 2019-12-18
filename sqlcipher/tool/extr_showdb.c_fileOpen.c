#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ dbfd; scalar_t__ bRaw; int /*<<< orphan*/  pDb; int /*<<< orphan*/  pFd; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SQLITE_FCNTL_FILE_POINTER ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 TYPE_1__ g ; 
 scalar_t__ open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openDatabase (char const*,char const*) ; 
 int sqlite3_file_control (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void fileOpen(const char *zPrg, const char *zName){
  assert( g.dbfd<0 );
  if( g.bRaw==0 ){
    int rc;
    void *pArg = (void *)(&g.pFd);
    g.pDb = openDatabase(zPrg, zName);
    rc = sqlite3_file_control(g.pDb, "main", SQLITE_FCNTL_FILE_POINTER, pArg);
    if( rc!=SQLITE_OK ){
      fprintf(stderr, 
          "%s: failed to obtain fd for %s (SQLite too old?)\n", zPrg, zName
      );
      exit(1);
    }
  }else{
    g.dbfd = open(zName, O_RDONLY);
    if( g.dbfd<0 ){
      fprintf(stderr,"%s: can't open %s\n", zPrg, zName);
      exit(1);
    }
  }
}