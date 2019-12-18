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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_DBSTATUS_CACHE_HIT ; 
 int /*<<< orphan*/  SQLITE_DBSTATUS_CACHE_MISS ; 
 int /*<<< orphan*/  SQLITE_DBSTATUS_CACHE_USED ; 
 int /*<<< orphan*/  SQLITE_DBSTATUS_CACHE_WRITE ; 
 int /*<<< orphan*/  SQLITE_STATUS_MALLOC_COUNT ; 
 int /*<<< orphan*/  SQLITE_STATUS_MALLOC_SIZE ; 
 int /*<<< orphan*/  SQLITE_STATUS_MEMORY_USED ; 
 int /*<<< orphan*/  SQLITE_STATUS_PAGECACHE_OVERFLOW ; 
 int /*<<< orphan*/  SQLITE_STATUS_PAGECACHE_SIZE ; 
 int /*<<< orphan*/  SQLITE_STATUS_PAGECACHE_USED ; 
 int /*<<< orphan*/  displayLinuxIoStats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  sqlite3_db_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int) ; 
 int /*<<< orphan*/  sqlite3_status (int /*<<< orphan*/ ,int*,int*,int) ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static int display_stats(
  sqlite3 *db,                    /* Database to query */
  int bReset                      /* True to reset SQLite stats */
){
  int iCur;
  int iHiwtr;
  FILE *out = stdout;

  fprintf(out, "\n");

  iHiwtr = iCur = -1;
  sqlite3_status(SQLITE_STATUS_MEMORY_USED, &iCur, &iHiwtr, bReset);
  fprintf(out,
          "Memory Used:                         %d (max %d) bytes\n",
          iCur, iHiwtr);
  iHiwtr = iCur = -1;
  sqlite3_status(SQLITE_STATUS_MALLOC_COUNT, &iCur, &iHiwtr, bReset);
  fprintf(out, "Number of Outstanding Allocations:   %d (max %d)\n",
          iCur, iHiwtr);
  iHiwtr = iCur = -1;
  sqlite3_status(SQLITE_STATUS_PAGECACHE_USED, &iCur, &iHiwtr, bReset);
  fprintf(out,
      "Number of Pcache Pages Used:         %d (max %d) pages\n",
      iCur, iHiwtr);
  iHiwtr = iCur = -1;
  sqlite3_status(SQLITE_STATUS_PAGECACHE_OVERFLOW, &iCur, &iHiwtr, bReset);
  fprintf(out,
          "Number of Pcache Overflow Bytes:     %d (max %d) bytes\n",
          iCur, iHiwtr);
  iHiwtr = iCur = -1;
  sqlite3_status(SQLITE_STATUS_MALLOC_SIZE, &iCur, &iHiwtr, bReset);
  fprintf(out, "Largest Allocation:                  %d bytes\n",
          iHiwtr);
  iHiwtr = iCur = -1;
  sqlite3_status(SQLITE_STATUS_PAGECACHE_SIZE, &iCur, &iHiwtr, bReset);
  fprintf(out, "Largest Pcache Allocation:           %d bytes\n",
          iHiwtr);

  iHiwtr = iCur = -1;
  sqlite3_db_status(db, SQLITE_DBSTATUS_CACHE_USED, &iCur, &iHiwtr, bReset);
  fprintf(out, "Pager Heap Usage:                    %d bytes\n",
      iCur);
  iHiwtr = iCur = -1;
  sqlite3_db_status(db, SQLITE_DBSTATUS_CACHE_HIT, &iCur, &iHiwtr, 1);
  fprintf(out, "Page cache hits:                     %d\n", iCur);
  iHiwtr = iCur = -1;
  sqlite3_db_status(db, SQLITE_DBSTATUS_CACHE_MISS, &iCur, &iHiwtr, 1);
  fprintf(out, "Page cache misses:                   %d\n", iCur);
  iHiwtr = iCur = -1;
  sqlite3_db_status(db, SQLITE_DBSTATUS_CACHE_WRITE, &iCur, &iHiwtr, 1);
  fprintf(out, "Page cache writes:                   %d\n", iCur);
  iHiwtr = iCur = -1;

#ifdef __linux__
  displayLinuxIoStats(out);
#endif

  return 0;
}