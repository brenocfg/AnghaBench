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
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ DemoFile ;

/* Variables and functions */
 int SQLITE_IOERR_TRUNCATE ; 
 int SQLITE_OK ; 
 scalar_t__ ftruncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int demoTruncate(sqlite3_file *pFile, sqlite_int64 size){
#if 0
  if( ftruncate(((DemoFile *)pFile)->fd, size) ) return SQLITE_IOERR_TRUNCATE;
#endif
  return SQLITE_OK;
}