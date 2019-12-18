#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ bHasDocsize; scalar_t__ bFts4; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 char FTS3_MATCHINFO_AVGLENGTH ; 
 char FTS3_MATCHINFO_HITS ; 
 char FTS3_MATCHINFO_LCS ; 
 char FTS3_MATCHINFO_LENGTH ; 
 char FTS3_MATCHINFO_LHITS ; 
 char FTS3_MATCHINFO_LHITS_BM ; 
 char FTS3_MATCHINFO_NCOL ; 
 char FTS3_MATCHINFO_NDOC ; 
 char FTS3_MATCHINFO_NPHRASE ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3Fts3ErrMsg (char**,char*,char) ; 

__attribute__((used)) static int fts3MatchinfoCheck(
  Fts3Table *pTab, 
  char cArg,
  char **pzErr
){
  if( (cArg==FTS3_MATCHINFO_NPHRASE)
   || (cArg==FTS3_MATCHINFO_NCOL)
   || (cArg==FTS3_MATCHINFO_NDOC && pTab->bFts4)
   || (cArg==FTS3_MATCHINFO_AVGLENGTH && pTab->bFts4)
   || (cArg==FTS3_MATCHINFO_LENGTH && pTab->bHasDocsize)
   || (cArg==FTS3_MATCHINFO_LCS)
   || (cArg==FTS3_MATCHINFO_HITS)
   || (cArg==FTS3_MATCHINFO_LHITS)
   || (cArg==FTS3_MATCHINFO_LHITS_BM)
  ){
    return SQLITE_OK;
  }
  sqlite3Fts3ErrMsg(pzErr, "unrecognized matchinfo request: %c", cArg);
  return SQLITE_ERROR;
}