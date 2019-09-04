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
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_WM_HScroll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDIT_WM_VScroll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EM_GETTHUMB ; 
 int /*<<< orphan*/  MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT EDIT_EM_GetThumb(EDITSTATE *es)
{
	return MAKELONG(EDIT_WM_VScroll(es, EM_GETTHUMB, 0),
                        EDIT_WM_HScroll(es, EM_GETTHUMB, 0));
}