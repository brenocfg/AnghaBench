#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_8__* value; } ;
typedef  TYPE_1__ node_str ;
struct TYPE_13__ {TYPE_8__* rhs; TYPE_8__* lhs; } ;
typedef  TYPE_2__ node_op ;
struct TYPE_14__ {TYPE_8__* body; TYPE_8__* args; } ;
typedef  TYPE_3__ node_lambda ;
struct TYPE_15__ {TYPE_8__* opt_else; TYPE_8__* then; TYPE_8__* cond; } ;
typedef  TYPE_4__ node_if ;
struct TYPE_16__ {TYPE_8__* name; } ;
typedef  TYPE_5__ node_ident ;
struct TYPE_17__ {TYPE_8__* emit; } ;
typedef  TYPE_6__ node_emit ;
struct TYPE_18__ {TYPE_8__* args; } ;
typedef  TYPE_7__ node_call ;
typedef  int /*<<< orphan*/  node_array ;
struct TYPE_19__ {int type; } ;
typedef  TYPE_8__ node ;

/* Variables and functions */
#define  NODE_ARGS 140 
#define  NODE_ARRAY 139 
#define  NODE_BOOL 138 
#define  NODE_CALL 137 
#define  NODE_EMIT 136 
#define  NODE_FLOAT 135 
#define  NODE_IDENT 134 
#define  NODE_IF 133 
#define  NODE_INT 132 
#define  NODE_LAMBDA 131 
#define  NODE_OP 130 
#define  NODE_RETURN 129 
#define  NODE_STR 128 
 int /*<<< orphan*/  free (TYPE_8__*) ; 
 int /*<<< orphan*/  node_args_free (TYPE_8__*) ; 
 int /*<<< orphan*/  node_array_free (int /*<<< orphan*/ *) ; 

void
node_free(node* np) {
  if (!np) {
    return;
  }

  switch (np->type) {
  case NODE_ARGS:
    node_args_free(np);
    break;
  case NODE_IF:
    node_free(((node_if*)np)->cond);
    node_free(((node_if*)np)->then);
    node_free(((node_if*)np)->opt_else);
    free(np);
    break;
  case NODE_EMIT:
    node_free(((node_emit*)np)->emit);
    free(np);
    break;
  case NODE_OP:
    node_free(((node_op*)np)->lhs);
    node_free(((node_op*)np)->rhs);
    free(np);
    break;
  case NODE_LAMBDA:
    node_args_free(((node_lambda*)np)->args);
    node_free(((node_lambda*)np)->body);
    free(np);
    break;
  case NODE_CALL:
    node_free(((node_call*)np)->args);
    free(np);
    break;
  case NODE_RETURN:
    node_free((node*)np);
    free(np);
    break;
  case NODE_IDENT:
    free(((node_ident*)np)->name);
    free(np);
    break;
  case NODE_ARRAY:
    node_array_free((node_array*)np);
    break;
  case NODE_INT:
  case NODE_FLOAT:
    free(np);
    break;
  case NODE_BOOL:
    return;
  case NODE_STR:
    free(((node_str*)np)->value);
    free(np);
    break;
  default:
    break;
  }
}