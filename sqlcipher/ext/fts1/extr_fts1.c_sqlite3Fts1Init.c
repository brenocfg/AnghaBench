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

/* Variables and functions */
 int /*<<< orphan*/  fulltextModule ; 
 int sqlite3_create_module (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_overload_function (int /*<<< orphan*/ *,char*,int) ; 

int sqlite3Fts1Init(sqlite3 *db){
  sqlite3_overload_function(db, "snippet", -1);
  sqlite3_overload_function(db, "offsets", -1);
  return sqlite3_create_module(db, "fts1", &fulltextModule, 0);
}