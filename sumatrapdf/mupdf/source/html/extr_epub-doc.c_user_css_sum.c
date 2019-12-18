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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ crc32 (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* fz_user_css (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static uint32_t
user_css_sum(fz_context *ctx)
{
	uint32_t sum = 0;
	const char *css = fz_user_css(ctx);
	sum = crc32(0, NULL, 0);
	if (css)
		sum = crc32(sum, (Byte*)css, strlen(css));
	return sum;
}