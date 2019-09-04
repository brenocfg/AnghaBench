#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ code; int aux; } ;
struct TYPE_4__ {TYPE_1__ i; } ;
typedef  int /*<<< orphan*/  CompileState ;

/* Variables and functions */
 int /*<<< orphan*/  IAny ; 
 int /*<<< orphan*/  IChar ; 
 scalar_t__ ITestChar ; 
 int /*<<< orphan*/  addinstruction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ getinstr (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void codechar (CompileState *compst, int c, int tt) {
  if (tt >= 0 && getinstr(compst, tt).i.code == ITestChar &&
                 getinstr(compst, tt).i.aux == c)
    addinstruction(compst, IAny, 0);
  else
    addinstruction(compst, IChar, c);
}