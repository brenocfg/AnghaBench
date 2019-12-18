#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_size; } ;
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_6__ {scalar_t__ bRaw; int /*<<< orphan*/  dbfd; TYPE_2__* pFd; } ;
struct TYPE_5__ {TYPE_1__* pMethods; } ;
struct TYPE_4__ {int (* xFileSize ) (TYPE_2__*,scalar_t__*) ;} ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fstat (int /*<<< orphan*/ ,struct stat*) ; 
 TYPE_3__ g ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (TYPE_2__*,scalar_t__*) ; 

__attribute__((used)) static sqlite3_int64 fileGetsize(void){
  sqlite3_int64 res = 0;
  if( g.bRaw==0 ){
    int rc = g.pFd->pMethods->xFileSize(g.pFd, &res);
    if( rc!=SQLITE_OK ){
      fprintf(stderr, "error in xFileSize() - %d\n", rc);
      exit(1);
    }
  }else{
    struct stat sbuf;
    fstat(g.dbfd, &sbuf);
    res = (sqlite3_int64)(sbuf.st_size);
  }
  return res;
}