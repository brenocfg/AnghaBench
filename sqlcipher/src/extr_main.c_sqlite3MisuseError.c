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
struct TYPE_2__ {scalar_t__ xLog; } ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_MISUSE ; 
 TYPE_1__ sqlite3GlobalConfig ; 
 int sqlite3ReportError (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  testcase (int) ; 

int sqlite3MisuseError(int lineno){
  testcase( sqlite3GlobalConfig.xLog!=0 );
  return sqlite3ReportError(SQLITE_MISUSE, lineno, "misuse");
}