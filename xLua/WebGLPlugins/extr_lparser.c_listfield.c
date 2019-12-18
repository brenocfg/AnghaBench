#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ConsControl {int /*<<< orphan*/  tostore; int /*<<< orphan*/  na; int /*<<< orphan*/  v; } ;
struct TYPE_4__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ LexState ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_INT ; 
 int /*<<< orphan*/  checklimit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  expr (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void listfield (LexState *ls, struct ConsControl *cc) {
  /* listfield -> exp */
  expr(ls, &cc->v);
  checklimit(ls->fs, cc->na, MAX_INT, "items in a constructor");
  cc->na++;
  cc->tostore++;
}