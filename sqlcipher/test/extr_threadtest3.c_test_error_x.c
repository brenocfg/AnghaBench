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
struct TYPE_3__ {int rc; char* zErr; } ;
typedef  TYPE_1__ Error ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 

__attribute__((used)) static void test_error_x(
  Error *pErr,
  char *zErr
){
  if( pErr->rc==SQLITE_OK ){
    pErr->rc = 1;
    pErr->zErr = zErr;
  }else{
    sqlite3_free(zErr);
  }
}