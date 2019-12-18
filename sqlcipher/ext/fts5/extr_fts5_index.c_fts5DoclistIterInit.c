#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t n; int /*<<< orphan*/ * p; } ;
struct TYPE_7__ {int /*<<< orphan*/ * aEof; int /*<<< orphan*/ * aPoslist; } ;
typedef  TYPE_1__ Fts5DoclistIter ;
typedef  TYPE_2__ Fts5Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fts5DoclistIterNext (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fts5DoclistIterInit(
  Fts5Buffer *pBuf, 
  Fts5DoclistIter *pIter
){
  memset(pIter, 0, sizeof(*pIter));
  pIter->aPoslist = pBuf->p;
  pIter->aEof = &pBuf->p[pBuf->n];
  fts5DoclistIterNext(pIter);
}