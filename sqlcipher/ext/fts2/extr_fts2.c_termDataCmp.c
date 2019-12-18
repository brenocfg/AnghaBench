#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nTerm; int /*<<< orphan*/  pTerm; } ;
typedef  TYPE_1__ TermData ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int termDataCmp(const void *av, const void *bv){
  const TermData *a = (const TermData *)av;
  const TermData *b = (const TermData *)bv;
  int n = a->nTerm<b->nTerm ? a->nTerm : b->nTerm;
  int c = memcmp(a->pTerm, b->pTerm, n);
  if( c!=0 ) return c;
  return a->nTerm-b->nTerm;
}