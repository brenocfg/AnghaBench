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

/* Variables and functions */
 int JS_REGEXP_G ; 
 int JS_REGEXP_I ; 
 int JS_REGEXP_M ; 
 int /*<<< orphan*/  pc (char) ; 
 int /*<<< orphan*/  ps (char const*) ; 

__attribute__((used)) static void pregexp(const char *prog, int flags)
{
	pc('/');
	ps(prog);
	pc('/');
	if (flags & JS_REGEXP_G) pc('g');
	if (flags & JS_REGEXP_I) pc('i');
	if (flags & JS_REGEXP_M) pc('m');
}