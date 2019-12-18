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
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  Select ;

/* Variables and functions */
 scalar_t__ OK_IF_ALWAYS_TRUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clearSelect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void sqlite3SelectDelete(sqlite3 *db, Select *p){
  if( OK_IF_ALWAYS_TRUE(p) ) clearSelect(db, p, 1);
}