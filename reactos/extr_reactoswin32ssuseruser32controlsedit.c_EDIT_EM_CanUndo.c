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
struct TYPE_3__ {int /*<<< orphan*/  undo_text; scalar_t__ undo_insert_count; } ;
typedef  TYPE_1__ EDITSTATE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ strlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline BOOL EDIT_EM_CanUndo(const EDITSTATE *es)
{
	return (es->undo_insert_count || strlenW(es->undo_text));
}