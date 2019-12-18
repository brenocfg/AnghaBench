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
struct TYPE_2__ {int /*<<< orphan*/  p; } ;
typedef  int /*<<< orphan*/  CallInfo ;

/* Variables and functions */
 TYPE_1__* ci_func (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  currentpc (int /*<<< orphan*/ *) ; 
 int getfuncline (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int currentline (CallInfo *ci) {
  return getfuncline(ci_func(ci)->p, currentpc(ci));
}