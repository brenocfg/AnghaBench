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
typedef  int /*<<< orphan*/  Fts3Table ;

/* Variables and functions */
 int FTS_CORRUPT_VTAB ; 
 int SQLITE_OK ; 
 int fts3IntegrityCheck (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int fts3DoIntegrityCheck(
  Fts3Table *p                    /* FTS3 table handle */
){
  int rc;
  int bOk = 0;
  rc = fts3IntegrityCheck(p, &bOk);
  if( rc==SQLITE_OK && bOk==0 ) rc = FTS_CORRUPT_VTAB;
  return rc;
}