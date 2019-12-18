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
struct TYPE_5__ {int len; int cap; int text; } ;
struct TYPE_6__ {TYPE_1__ lexbuf; } ;
typedef  TYPE_2__ js_State ;
typedef  int /*<<< orphan*/  Rune ;

/* Variables and functions */
 int js_realloc (TYPE_2__*,int,int) ; 
 int runelen (int /*<<< orphan*/ ) ; 
 int runetochar (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void textpush(js_State *J, Rune c)
{
	int n = runelen(c);
	if (J->lexbuf.len + n > J->lexbuf.cap) {
		J->lexbuf.cap = J->lexbuf.cap * 2;
		J->lexbuf.text = js_realloc(J, J->lexbuf.text, J->lexbuf.cap);
	}
	J->lexbuf.len += runetochar(J->lexbuf.text + J->lexbuf.len, &c);
}