#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int block; int /*<<< orphan*/  lineno; int /*<<< orphan*/ * fname; TYPE_2__* body; TYPE_2__* args; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ node_lambda ;
struct TYPE_8__ {int /*<<< orphan*/  lineno; int /*<<< orphan*/ * fname; } ;
typedef  TYPE_2__ node ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_LAMBDA ; 
 TYPE_1__* malloc (int) ; 

node*
node_lambda_alloc(node* args, node* compstmt, int block)
{
  node_lambda* lambda = malloc(sizeof(node_lambda));
  lambda->type = NODE_LAMBDA;
  lambda->args = args;
  lambda->body = compstmt;
  lambda->block = block;
  lambda->fname = compstmt ? compstmt->fname : NULL;
  lambda->lineno = compstmt ? compstmt->lineno : 0;
  return (node*)lambda;
}