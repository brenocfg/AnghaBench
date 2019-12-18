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
typedef  scalar_t__ linenr_T ;
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_5__ {scalar_t__ ml_line_count; } ;
struct TYPE_6__ {TYPE_1__ b_ml; } ;
typedef  TYPE_2__ buf_T ;
typedef  int /*<<< orphan*/  aco_save_T ;
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  NOT_VALID ; 
 scalar_t__ OK ; 
 char* StringValuePtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  aucmd_prepbuf (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  aucmd_restbuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  changed () ; 
 int /*<<< orphan*/  ml_replace (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_eIndexError ; 
 int /*<<< orphan*/  rb_raise (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  syn_changed (scalar_t__) ; 
 scalar_t__ u_savesub (scalar_t__) ; 
 int /*<<< orphan*/  update_curbuf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VALUE set_buffer_line(buf_T *buf, linenr_T n, VALUE str)
{
    char	*line = StringValuePtr(str);
    aco_save_T	aco;

    if (n > 0 && n <= buf->b_ml.ml_line_count && line != NULL)
    {
	/* set curwin/curbuf for "buf" and save some things */
	aucmd_prepbuf(&aco, buf);

	if (u_savesub(n) == OK) {
	    ml_replace(n, (char_u *)line, TRUE);
	    changed();
#ifdef SYNTAX_HL
	    syn_changed(n); /* recompute syntax hl. for this line */
#endif
	}

	/* restore curwin/curbuf and a few other things */
	aucmd_restbuf(&aco);
	/* Careful: autocommands may have made "buf" invalid! */

	update_curbuf(NOT_VALID);
    }
    else
    {
	rb_raise(rb_eIndexError, "line number %ld out of range", (long)n);
    }
    return str;
}