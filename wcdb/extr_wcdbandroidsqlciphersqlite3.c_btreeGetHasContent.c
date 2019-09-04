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
struct TYPE_3__ {int /*<<< orphan*/ * pHasContent; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_1__ BtShared ;
typedef  int /*<<< orphan*/  Bitvec ;

/* Variables and functions */
 scalar_t__ sqlite3BitvecSize (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3BitvecTest (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int btreeGetHasContent(BtShared *pBt, Pgno pgno){
  Bitvec *p = pBt->pHasContent;
  return (p && (pgno>sqlite3BitvecSize(p) || sqlite3BitvecTest(p, pgno)));
}