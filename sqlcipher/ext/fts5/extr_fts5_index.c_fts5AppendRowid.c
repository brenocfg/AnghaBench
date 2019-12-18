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
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_3__ {int /*<<< orphan*/  rc; } ;
typedef  int /*<<< orphan*/  Fts5Iter ;
typedef  TYPE_1__ Fts5Index ;
typedef  int /*<<< orphan*/  Fts5Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts5BufferAppendVarint (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fts5AppendRowid(
  Fts5Index *p,
  i64 iDelta,
  Fts5Iter *pUnused,
  Fts5Buffer *pBuf
){
  UNUSED_PARAM(pUnused);
  fts5BufferAppendVarint(&p->rc, pBuf, iDelta);
}