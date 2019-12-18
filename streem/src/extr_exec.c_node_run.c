#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_8__ {scalar_t__ lval; } ;
typedef  TYPE_1__ parser_state ;
struct TYPE_9__ {scalar_t__ type; } ;
typedef  TYPE_2__ node_error ;
typedef  int /*<<< orphan*/  node ;
struct TYPE_10__ {TYPE_2__* exc; } ;

/* Variables and functions */
 scalar_t__ NODE_ERROR_RETURN ; 
 int STRM_OK ; 
 int /*<<< orphan*/  exec_expr (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_clear_exc (TYPE_3__*) ; 
 int /*<<< orphan*/  strm_eprint (TYPE_3__*) ; 
 int /*<<< orphan*/  top_state ; 
 TYPE_3__ top_strm ; 

int
node_run(parser_state* p)
{
  strm_value v;
  node_error* exc;

  node_init(&top_state);

  exec_expr(&top_strm, &top_state, (node*)p->lval, &v);
  exc = top_strm.exc;
  if (exc != NULL) {
    if (exc->type != NODE_ERROR_RETURN) {
      strm_eprint(&top_strm);
    }
    strm_clear_exc(&top_strm);
  }
  return STRM_OK;
}