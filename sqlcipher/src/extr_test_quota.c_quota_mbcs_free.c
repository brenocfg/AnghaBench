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

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (char*) ; 

__attribute__((used)) static void quota_mbcs_free(char *zOld){
#if SQLITE_OS_WIN
  sqlite3_free(zOld);
#else
  /* No-op on unix */
#endif
}