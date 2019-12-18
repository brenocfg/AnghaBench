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
struct TYPE_3__ {int iBitmap; int idCommand; int fsStyle; int iString; int /*<<< orphan*/  fsState; } ;
typedef  TYPE_1__ TBBUTTON ;

/* Variables and functions */
 int /*<<< orphan*/  TBSTATE_ENABLED ; 

__attribute__((used)) static void MakeButton(TBBUTTON *p, int idCommand, int fsStyle, int nString) {
  p->iBitmap = -2;
  p->idCommand = idCommand;
  p->fsState = TBSTATE_ENABLED;
  p->fsStyle = fsStyle;
  p->iString = nString;
}