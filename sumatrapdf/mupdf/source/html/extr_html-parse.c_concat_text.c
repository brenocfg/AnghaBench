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
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 char* fz_malloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * fz_xml_down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_xml_next (int /*<<< orphan*/ *) ; 
 char* fz_xml_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static char *concat_text(fz_context *ctx, fz_xml *root)
{
	fz_xml *node;
	size_t i = 0, n = 1;
	char *s;
	for (node = fz_xml_down(root); node; node = fz_xml_next(node))
	{
		const char *text = fz_xml_text(node);
		n += text ? strlen(text) : 0;
	}
	s = fz_malloc(ctx, n);
	for (node = fz_xml_down(root); node; node = fz_xml_next(node))
	{
		const char *text = fz_xml_text(node);
		if (text)
		{
			n = strlen(text);
			memcpy(s+i, text, n);
			i += n;
		}
	}
	s[i] = 0;
	return s;
}