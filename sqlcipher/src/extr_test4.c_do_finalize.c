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
struct TYPE_3__ {scalar_t__ pStmt; char* zErr; char* zStaticErr; int /*<<< orphan*/  rc; } ;
typedef  TYPE_1__ Thread ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_ERROR ; 
 int /*<<< orphan*/  sqlite3_finalize (scalar_t__) ; 

__attribute__((used)) static void do_finalize(Thread *p){
  if( p->pStmt==0 ){
    p->zErr = p->zStaticErr = "no virtual machine available";
    p->rc = SQLITE_ERROR;
    return;
  }
  p->rc = sqlite3_finalize(p->pStmt);
  p->pStmt = 0;
}