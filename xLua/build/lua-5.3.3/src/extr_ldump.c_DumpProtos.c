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
struct TYPE_3__ {int sizep; int /*<<< orphan*/  source; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ Proto ;
typedef  int /*<<< orphan*/  DumpState ;

/* Variables and functions */
 int /*<<< orphan*/  DumpFunction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpInt (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DumpProtos (const Proto *f, DumpState *D) {
  int i;
  int n = f->sizep;
  DumpInt(n, D);
  for (i = 0; i < n; i++)
    DumpFunction(f->p[i], f->source, D);
}