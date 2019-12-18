#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ bFts4; int /*<<< orphan*/  bHasStat; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int FTS3_MERGE_COUNT ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fts3Getint (char const**) ; 
 int /*<<< orphan*/  sqlite3Fts3CreateStatTable (int*,TYPE_1__*) ; 
 int sqlite3Fts3Incrmerge (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  sqlite3Fts3SegmentsClose (TYPE_1__*) ; 

__attribute__((used)) static int fts3DoIncrmerge(
  Fts3Table *p,                   /* FTS3 table handle */
  const char *zParam              /* Nul-terminated string containing "A,B" */
){
  int rc;
  int nMin = (FTS3_MERGE_COUNT / 2);
  int nMerge = 0;
  const char *z = zParam;

  /* Read the first integer value */
  nMerge = fts3Getint(&z);

  /* If the first integer value is followed by a ',',  read the second
  ** integer value. */
  if( z[0]==',' && z[1]!='\0' ){
    z++;
    nMin = fts3Getint(&z);
  }

  if( z[0]!='\0' || nMin<2 ){
    rc = SQLITE_ERROR;
  }else{
    rc = SQLITE_OK;
    if( !p->bHasStat ){
      assert( p->bFts4==0 );
      sqlite3Fts3CreateStatTable(&rc, p);
    }
    if( rc==SQLITE_OK ){
      rc = sqlite3Fts3Incrmerge(p, nMerge, nMin);
    }
    sqlite3Fts3SegmentsClose(p);
  }
  return rc;
}