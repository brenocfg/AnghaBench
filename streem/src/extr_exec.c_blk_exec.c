#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct strm_lambda {TYPE_1__* body; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_14__ {TYPE_4__* exc; struct strm_lambda* data; } ;
typedef  TYPE_2__ strm_stream ;
struct TYPE_15__ {int /*<<< orphan*/  prev; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ strm_state ;
struct TYPE_16__ {scalar_t__ type; int /*<<< orphan*/  arg; } ;
typedef  TYPE_4__ node_error ;
struct TYPE_17__ {int len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_5__ node_args ;
struct TYPE_13__ {int /*<<< orphan*/  body; scalar_t__ args; } ;

/* Variables and functions */
 scalar_t__ NODE_ERROR_RETURN ; 
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int exec_expr (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_to_sym (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_clear_exc (TYPE_2__*) ; 
 int /*<<< orphan*/  strm_emit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_eprint (TYPE_2__*) ; 
 int /*<<< orphan*/  strm_nil_value () ; 
 scalar_t__ strm_option_verbose ; 
 int /*<<< orphan*/  strm_var_set (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
blk_exec(strm_stream* strm, strm_value data)
{
  struct strm_lambda* lambda = strm->data;
  strm_value ret = strm_nil_value();
  node_args* args = (node_args*)lambda->body->args;
  node_error* exc;
  int n;
  strm_state c = {0};

  c.prev = lambda->state;
  if (args) {
    assert(args->len == 1);
    strm_var_set(&c, node_to_sym(args->data[0]), data);
  }

  n = exec_expr(strm, &c, lambda->body->body, &ret);
  exc = strm->exc;
  if (exc) {
    if (exc->type == NODE_ERROR_RETURN) {
      ret = exc->arg;
      strm_clear_exc(strm);
    }
    else {
      if (strm_option_verbose) {
        strm_eprint(strm);
      }
      return STRM_NG;
    }
  }
  if (n) return STRM_NG;
  strm_emit(strm, ret, NULL);
  return STRM_OK;
}