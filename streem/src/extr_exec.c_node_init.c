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
typedef  int /*<<< orphan*/  strm_state ;

/* Variables and functions */
 int /*<<< orphan*/  STRM_IO_READ ; 
 int /*<<< orphan*/  STRM_IO_WRITE ; 
 int /*<<< orphan*/  exec_bar ; 
 int /*<<< orphan*/  exec_eq ; 
 int /*<<< orphan*/  exec_exit ; 
 int /*<<< orphan*/  exec_fread ; 
 int /*<<< orphan*/  exec_fwrite ; 
 int /*<<< orphan*/  exec_match ; 
 int /*<<< orphan*/  exec_neq ; 
 int /*<<< orphan*/  exec_puts ; 
 int /*<<< orphan*/  strm_cfunc_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_io_new (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_var_def (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
node_init(strm_state* state)
{
  strm_init(state);

  strm_var_def(state, "stdin", strm_io_new(0, STRM_IO_READ));
  strm_var_def(state, "stdout", strm_io_new(1, STRM_IO_WRITE));
  strm_var_def(state, "stderr", strm_io_new(2, STRM_IO_WRITE));
  strm_var_def(state, "puts", strm_cfunc_value(exec_puts));
  strm_var_def(state, "print", strm_cfunc_value(exec_puts));
  strm_var_def(state, "==", strm_cfunc_value(exec_eq));
  strm_var_def(state, "!=", strm_cfunc_value(exec_neq));
  strm_var_def(state, "|", strm_cfunc_value(exec_bar));
  strm_var_def(state, "fread", strm_cfunc_value(exec_fread));
  strm_var_def(state, "fwrite", strm_cfunc_value(exec_fwrite));
  strm_var_def(state, "exit", strm_cfunc_value(exec_exit));
  strm_var_def(state, "match", strm_cfunc_value(exec_match));
}