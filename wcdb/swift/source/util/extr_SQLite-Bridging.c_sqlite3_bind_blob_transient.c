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
typedef  int /*<<< orphan*/  sqlite3_stmt ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int sqlite3_bind_blob (int /*<<< orphan*/ *,int,void const*,int,int /*<<< orphan*/ ) ; 

int sqlite3_bind_blob_transient(sqlite3_stmt *a, int b, const void *c, int n)
{
    return sqlite3_bind_blob(a, b, c, n, SQLITE_TRANSIENT);
}