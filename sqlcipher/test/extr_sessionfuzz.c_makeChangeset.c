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
typedef  int /*<<< orphan*/  sqlite3_session ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sqlite3_free (void*) ; 
 int sqlite3session_changeset (int /*<<< orphan*/ *,int*,void**) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  writeFile (char const*,void*,int) ; 

__attribute__((used)) static void makeChangeset(const char *zFile, sqlite3_session *pSess){
  void *pChg;
  int nChg;
  int rc;
  rc = sqlite3session_changeset(pSess, &nChg, &pChg);
  if( rc ){
    fprintf(stderr, "sqlite3session_changeset() returned %d\n", rc);
    exit(1);
  }
  writeFile(zFile, pChg, nChg);
  sqlite3_free(pChg);
}