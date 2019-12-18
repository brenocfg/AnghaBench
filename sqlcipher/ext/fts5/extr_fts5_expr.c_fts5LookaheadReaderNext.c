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
struct TYPE_3__ {scalar_t__ iPos; scalar_t__ iLookahead; int /*<<< orphan*/  i; int /*<<< orphan*/  n; int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ Fts5LookaheadReader ;

/* Variables and functions */
 scalar_t__ FTS5_LOOKAHEAD_EOF ; 
 scalar_t__ sqlite3Fts5PoslistNext64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static int fts5LookaheadReaderNext(Fts5LookaheadReader *p){
  p->iPos = p->iLookahead;
  if( sqlite3Fts5PoslistNext64(p->a, p->n, &p->i, &p->iLookahead) ){
    p->iLookahead = FTS5_LOOKAHEAD_EOF;
  }
  return (p->iPos==FTS5_LOOKAHEAD_EOF);
}