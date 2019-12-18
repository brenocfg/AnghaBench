#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {long ml_line_count; } ;
struct TYPE_6__ {TYPE_1__ b_ml; } ;
typedef  TYPE_2__ buf_T ;
typedef  int /*<<< orphan*/  aco_save_T ;
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  NOT_VALID ; 
 long NUM2LONG (int /*<<< orphan*/ ) ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  Qnil ; 
 int /*<<< orphan*/  aucmd_prepbuf (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  aucmd_restbuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  changed () ; 
 int /*<<< orphan*/  deleted_lines_mark (long,long) ; 
 TYPE_2__* get_buf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_delete (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_eIndexError ; 
 int /*<<< orphan*/  rb_raise (int /*<<< orphan*/ ,char*,long) ; 
 scalar_t__ u_savedel (long,int) ; 
 int /*<<< orphan*/  update_curbuf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VALUE buffer_delete(VALUE self, VALUE num)
{
    buf_T	*buf = get_buf(self);
    long	n = NUM2LONG(num);
    aco_save_T	aco;

    if (n > 0 && n <= buf->b_ml.ml_line_count)
    {
	/* set curwin/curbuf for "buf" and save some things */
	aucmd_prepbuf(&aco, buf);

	if (u_savedel(n, 1) == OK) {
	    ml_delete(n, 0);

	    /* Changes to non-active buffers should properly refresh
	     *   SegPhault - 01/09/05 */
	    deleted_lines_mark(n, 1L);

	    changed();
	}

	/* restore curwin/curbuf and a few other things */
	aucmd_restbuf(&aco);
	/* Careful: autocommands may have made "buf" invalid! */

	update_curbuf(NOT_VALID);
    }
    else
    {
	rb_raise(rb_eIndexError, "line number %ld out of range", n);
    }
    return Qnil;
}