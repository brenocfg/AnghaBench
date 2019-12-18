#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int errCode; scalar_t__ pErr; } ;
typedef  TYPE_1__ sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3ErrorFinish (TYPE_1__*,int) ; 

void sqlite3Error(sqlite3 *db, int err_code){
  assert( db!=0 );
  db->errCode = err_code;
  if( err_code || db->pErr ) sqlite3ErrorFinish(db, err_code);
}