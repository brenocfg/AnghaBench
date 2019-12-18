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
struct TYPE_5__ {char* text; } ;
struct TYPE_6__ {TYPE_1__ lexbuf; } ;
typedef  TYPE_2__ js_State ;

/* Variables and functions */
 int /*<<< orphan*/  textpush (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *textend(js_State *J)
{
	textpush(J, 0);
	return J->lexbuf.text;
}