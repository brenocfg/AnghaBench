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
struct TYPE_3__ {size_t nCol; size_t nPhrase; } ;
typedef  TYPE_1__ MatchInfo ;

/* Variables and functions */
#define  FTS3_MATCHINFO_AVGLENGTH 135 
 char FTS3_MATCHINFO_HITS ; 
#define  FTS3_MATCHINFO_LCS 134 
#define  FTS3_MATCHINFO_LENGTH 133 
#define  FTS3_MATCHINFO_LHITS 132 
#define  FTS3_MATCHINFO_LHITS_BM 131 
#define  FTS3_MATCHINFO_NCOL 130 
#define  FTS3_MATCHINFO_NDOC 129 
#define  FTS3_MATCHINFO_NPHRASE 128 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static size_t fts3MatchinfoSize(MatchInfo *pInfo, char cArg){
  size_t nVal;                      /* Number of integers output by cArg */

  switch( cArg ){
    case FTS3_MATCHINFO_NDOC:
    case FTS3_MATCHINFO_NPHRASE: 
    case FTS3_MATCHINFO_NCOL: 
      nVal = 1;
      break;

    case FTS3_MATCHINFO_AVGLENGTH:
    case FTS3_MATCHINFO_LENGTH:
    case FTS3_MATCHINFO_LCS:
      nVal = pInfo->nCol;
      break;

    case FTS3_MATCHINFO_LHITS:
      nVal = pInfo->nCol * pInfo->nPhrase;
      break;

    case FTS3_MATCHINFO_LHITS_BM:
      nVal = pInfo->nPhrase * ((pInfo->nCol + 31) / 32);
      break;

    default:
      assert( cArg==FTS3_MATCHINFO_HITS );
      nVal = pInfo->nCol * pInfo->nPhrase * 3;
      break;
  }

  return nVal;
}