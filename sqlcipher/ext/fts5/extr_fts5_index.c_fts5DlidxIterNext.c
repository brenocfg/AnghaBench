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
typedef  int /*<<< orphan*/  Fts5Index ;
typedef  int /*<<< orphan*/  Fts5DlidxIter ;

/* Variables and functions */
 int fts5DlidxIterNextR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5DlidxIterNext(Fts5Index *p, Fts5DlidxIter *pIter){
  return fts5DlidxIterNextR(p, pIter, 0);
}