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
typedef  int /*<<< orphan*/  EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_WM_Clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDIT_WM_Copy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void EDIT_WM_Cut(EDITSTATE *es)
{
	EDIT_WM_Copy(es);
	EDIT_WM_Clear(es);
}