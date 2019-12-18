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
typedef  int /*<<< orphan*/  Fts5SegIter ;
typedef  int /*<<< orphan*/  Fts5Iter ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAM2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts5IterSetOutputs_Noop(Fts5Iter *pUnused1, Fts5SegIter *pUnused2){
  UNUSED_PARAM2(pUnused1, pUnused2);
}