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
struct TYPE_3__ {int accError; } ;
typedef  TYPE_1__ sqlite3_str ;

/* Variables and functions */
 int SQLITE_NOMEM ; 

int sqlite3_str_errcode(sqlite3_str *p){
  return p ? p->accError : SQLITE_NOMEM;
}