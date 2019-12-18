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
typedef  int /*<<< orphan*/  Fts3MultiSegReader ;

/* Variables and functions */
 int /*<<< orphan*/  FTS3_SEGCURSOR_ALL ; 
 int fts3SegReaderCursor (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3SegReaderCursorAddZero(
  Fts3Table *p,                   /* FTS virtual table handle */
  int iLangid,
  const char *zTerm,              /* Term to scan doclist of */
  int nTerm,                      /* Number of bytes in zTerm */
  Fts3MultiSegReader *pCsr        /* Fts3MultiSegReader to modify */
){
  return fts3SegReaderCursor(p, 
      iLangid, 0, FTS3_SEGCURSOR_ALL, zTerm, nTerm, 0, 0,pCsr
  );
}