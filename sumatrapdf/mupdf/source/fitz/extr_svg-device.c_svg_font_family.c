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
 int /*<<< orphan*/  fz_strlcpy (char*,char const*,int) ; 
 char* strchr (char const*,char) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void
svg_font_family(fz_context *ctx, char buf[], int size, const char *name)
{
	/* Remove "ABCDEF+" prefix and "-Bold" suffix. */
	char *p = strchr(name, '+');
	if (p) fz_strlcpy(buf, p+1, size);
	else fz_strlcpy(buf, name, size);
	p = strrchr(buf, '-');
	if (p) *p = 0;
}