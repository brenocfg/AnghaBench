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
struct TYPE_6__ {size_t trytop; TYPE_1__* trybuf; int /*<<< orphan*/  strict; int /*<<< orphan*/  bot; int /*<<< orphan*/  top; int /*<<< orphan*/  tracetop; int /*<<< orphan*/  envtop; int /*<<< orphan*/  E; } ;
typedef  TYPE_2__ js_State ;
struct TYPE_5__ {void* buf; int /*<<< orphan*/ * pc; int /*<<< orphan*/  strict; int /*<<< orphan*/  bot; int /*<<< orphan*/  top; int /*<<< orphan*/  tracetop; int /*<<< orphan*/  envtop; int /*<<< orphan*/  E; } ;

/* Variables and functions */
 size_t JS_TRYLIMIT ; 
 int /*<<< orphan*/  js_error (TYPE_2__*,char*) ; 

void *js_savetry(js_State *J)
{
	if (J->trytop == JS_TRYLIMIT)
		js_error(J, "try: exception stack overflow");
	J->trybuf[J->trytop].E = J->E;
	J->trybuf[J->trytop].envtop = J->envtop;
	J->trybuf[J->trytop].tracetop = J->tracetop;
	J->trybuf[J->trytop].top = J->top;
	J->trybuf[J->trytop].bot = J->bot;
	J->trybuf[J->trytop].strict = J->strict;
	J->trybuf[J->trytop].pc = NULL;
	return J->trybuf[J->trytop++].buf;
}