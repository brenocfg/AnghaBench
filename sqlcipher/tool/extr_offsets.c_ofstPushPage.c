#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {size_t nStack; int* aPgno; int szPg; int pgno; int /*<<< orphan*/  f; int /*<<< orphan*/ * aPage; int /*<<< orphan*/ ** aStack; scalar_t__ zErr; } ;
typedef  TYPE_1__ GState ;

/* Variables and functions */
 size_t ArraySize (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 size_t fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofstError (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  ofstPopPage (TYPE_1__*) ; 
 int /*<<< orphan*/ * sqlite3_malloc (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void ofstPushPage(GState *p, int pgno){
  u8 *pPage;
  size_t got;
  if( p->zErr ) return;
  if( p->nStack >= ArraySize(p->aStack) ){
    ofstError(p, "page stack overflow");
    return;
  }
  p->aPgno[p->nStack] = pgno;
  p->aStack[p->nStack] = pPage = sqlite3_malloc( p->szPg );
  if( pPage==0 ){
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  p->nStack++;
  p->aPage = pPage;
  p->pgno = pgno;
  fseek(p->f, (pgno-1)*p->szPg, SEEK_SET);
  got = fread(pPage, 1, p->szPg, p->f);
  if( got!=p->szPg ){
    ofstError(p, "unable to read page %d", pgno);
    ofstPopPage(p);
  }
}