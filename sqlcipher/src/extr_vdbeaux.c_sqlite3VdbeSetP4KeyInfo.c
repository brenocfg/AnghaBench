#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_4__ {int /*<<< orphan*/ * pVdbe; } ;
typedef  TYPE_1__ Parse ;
typedef  int /*<<< orphan*/  KeyInfo ;
typedef  int /*<<< orphan*/  Index ;

/* Variables and functions */
 int /*<<< orphan*/  P4_KEYINFO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * sqlite3KeyInfoOfIndex (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeAppendP4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sqlite3VdbeSetP4KeyInfo(Parse *pParse, Index *pIdx){
  Vdbe *v = pParse->pVdbe;
  KeyInfo *pKeyInfo;
  assert( v!=0 );
  assert( pIdx!=0 );
  pKeyInfo = sqlite3KeyInfoOfIndex(pParse, pIdx);
  if( pKeyInfo ) sqlite3VdbeAppendP4(v, pKeyInfo, P4_KEYINFO);
}