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
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_strlcpy (char*,char*,int) ; 

__attribute__((used)) static void
hail_mary_format_key(fz_context *ctx, char *s, int n, void *key_)
{
	fz_strlcpy(s, "(hail mary font)", n);
}