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
struct TYPE_4__ {scalar_t__ text; scalar_t__ (* word_break_proc ) (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ;} ;
typedef  scalar_t__ INT ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 scalar_t__ EDIT_WordBreakProc (TYPE_1__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static INT EDIT_CallWordBreakProc(EDITSTATE *es, INT start, INT index, INT count, INT action)
{
    INT ret;

    if (es->word_break_proc)
        ret = es->word_break_proc(es->text + start, index, count, action);
    else
        ret = EDIT_WordBreakProc(es, es->text, index + start, count + start, action) - start;

    return ret;
}