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
 int /*<<< orphan*/  anyCollFunc ; 
 int /*<<< orphan*/  sqlite3_create_collation (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void anyCollNeeded(
  void *NotUsed,
  sqlite3 *db,
  int eTextRep,
  const char *zCollName
){
  sqlite3_create_collation(db, zCollName, eTextRep, 0, anyCollFunc); 
}