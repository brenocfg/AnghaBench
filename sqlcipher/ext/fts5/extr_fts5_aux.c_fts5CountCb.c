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
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  Fts5ExtensionApi ;
typedef  int /*<<< orphan*/  Fts5Context ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  UNUSED_PARAM2 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts5CountCb(
  const Fts5ExtensionApi *pApi, 
  Fts5Context *pFts,
  void *pUserData                 /* Pointer to sqlite3_int64 variable */
){
  sqlite3_int64 *pn = (sqlite3_int64*)pUserData;
  UNUSED_PARAM2(pApi, pFts);
  (*pn)++;
  return SQLITE_OK;
}