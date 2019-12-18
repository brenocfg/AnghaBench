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
struct TYPE_5__ {int n; int /*<<< orphan*/  const* a; } ;
typedef  TYPE_1__ Fts5LookaheadReader ;

/* Variables and functions */
 int fts5LookaheadReaderNext (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fts5LookaheadReaderInit(
  const u8 *a, int n,             /* Buffer to read position list from */
  Fts5LookaheadReader *p          /* Iterator object to initialize */
){
  memset(p, 0, sizeof(Fts5LookaheadReader));
  p->a = a;
  p->n = n;
  fts5LookaheadReaderNext(p);
  return fts5LookaheadReaderNext(p);
}