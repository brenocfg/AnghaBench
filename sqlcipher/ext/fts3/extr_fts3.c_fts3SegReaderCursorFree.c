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
typedef  int /*<<< orphan*/  Fts3MultiSegReader ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3Fts3SegReaderFinish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts3SegReaderCursorFree(Fts3MultiSegReader *pSegcsr){
  sqlite3Fts3SegReaderFinish(pSegcsr);
  sqlite3_free(pSegcsr);
}