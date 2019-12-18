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
typedef  int /*<<< orphan*/  VALUE ;
struct TYPE_3__ {int /*<<< orphan*/  lnum; } ;
struct TYPE_4__ {TYPE_1__ w_cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  curbuf ; 
 TYPE_2__* curwin ; 
 int /*<<< orphan*/  get_buffer_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VALUE line_s_current()
{
    return get_buffer_line(curbuf, curwin->w_cursor.lnum);
}