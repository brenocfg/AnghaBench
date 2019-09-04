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
struct TYPE_4__ {int style; } ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  EDIT_EM_ReplaceSel (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ES_READONLY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  empty_stringW ; 

__attribute__((used)) static inline void EDIT_WM_Clear(EDITSTATE *es)
{
	/* Protect read-only edit control from modification */
	if(es->style & ES_READONLY)
	    return;

	EDIT_EM_ReplaceSel(es, TRUE, empty_stringW, TRUE, TRUE);
}