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
typedef  int /*<<< orphan*/  js_Value ;
struct TYPE_8__ {size_t trytop; int /*<<< orphan*/  (* panic ) (TYPE_2__*) ;TYPE_1__* trybuf; int /*<<< orphan*/  strict; int /*<<< orphan*/  bot; int /*<<< orphan*/  top; int /*<<< orphan*/  tracetop; int /*<<< orphan*/  envtop; int /*<<< orphan*/  E; } ;
typedef  TYPE_2__ js_State ;
struct TYPE_7__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  strict; int /*<<< orphan*/  bot; int /*<<< orphan*/  top; int /*<<< orphan*/  tracetop; int /*<<< orphan*/  envtop; int /*<<< orphan*/  E; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  js_pushvalue (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * stackidx (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void js_throw(js_State *J)
{
	if (J->trytop > 0) {
		js_Value v = *stackidx(J, -1);
		--J->trytop;
		J->E = J->trybuf[J->trytop].E;
		J->envtop = J->trybuf[J->trytop].envtop;
		J->tracetop = J->trybuf[J->trytop].tracetop;
		J->top = J->trybuf[J->trytop].top;
		J->bot = J->trybuf[J->trytop].bot;
		J->strict = J->trybuf[J->trytop].strict;
		js_pushvalue(J, v);
		longjmp(J->trybuf[J->trytop].buf, 1);
	}
	if (J->panic)
		J->panic(J);
	abort();
}