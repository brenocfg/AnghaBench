#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int code; int /*<<< orphan*/  output; } ;
typedef  TYPE_1__ stb_arith ;

/* Variables and functions */
 int stb_getc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stb__renorm_decoder(stb_arith *a)
{
   int c = stb_getc(a->output);
   a->code = (a->code << 8) + (c >= 0 ? c : 0); // if EOF, insert 0
}