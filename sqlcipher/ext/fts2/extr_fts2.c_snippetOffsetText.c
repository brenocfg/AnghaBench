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
typedef  int /*<<< orphan*/  zBuf ;
struct snippetMatch {int /*<<< orphan*/  nByte; int /*<<< orphan*/  iStart; int /*<<< orphan*/  iTerm; int /*<<< orphan*/  iCol; } ;
struct TYPE_3__ {int nMatch; int /*<<< orphan*/  nOffset; int /*<<< orphan*/  zOffset; struct snippetMatch* aMatch; } ;
typedef  int /*<<< orphan*/  StringBuffer ;
typedef  TYPE_1__ Snippet ;

/* Variables and functions */
 int /*<<< orphan*/  append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  initStringBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stringBufferData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stringBufferLength (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snippetOffsetText(Snippet *p){
  int i;
  int cnt = 0;
  StringBuffer sb;
  char zBuf[200];
  if( p->zOffset ) return;
  initStringBuffer(&sb);
  for(i=0; i<p->nMatch; i++){
    struct snippetMatch *pMatch = &p->aMatch[i];
    zBuf[0] = ' ';
    sqlite3_snprintf(sizeof(zBuf)-1, &zBuf[cnt>0], "%d %d %d %d",
        pMatch->iCol, pMatch->iTerm, pMatch->iStart, pMatch->nByte);
    append(&sb, zBuf);
    cnt++;
  }
  p->zOffset = stringBufferData(&sb);
  p->nOffset = stringBufferLength(&sb);
}