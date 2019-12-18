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
 char* fz_strsep (char**,char*) ; 
 float fz_strtof (char*,char**) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void
pdf_parse_default_appearance(fz_context *ctx, const char *da, const char **font, float *size, float color[3])
{
	char buf[100], *p = buf, *tok, *end;
	float stack[3] = { 0, 0, 0 };
	int top = 0;

	*font = "Helv";
	*size = 12;
	color[0] = color[1] = color[2] = 0;

	fz_strlcpy(buf, da, sizeof buf);
	while ((tok = fz_strsep(&p, " \n\r\t")) != NULL)
	{
		if (tok[0] == 0)
			;
		else if (tok[0] == '/')
		{
			if (!strcmp(tok+1, "Cour")) *font = "Cour";
			if (!strcmp(tok+1, "Helv")) *font = "Helv";
			if (!strcmp(tok+1, "TiRo")) *font = "TiRo";
			if (!strcmp(tok+1, "Symb")) *font = "Symb";
			if (!strcmp(tok+1, "ZaDb")) *font = "ZaDb";
		}
		else if (!strcmp(tok, "Tf"))
		{
			*size = stack[0];
			top = 0;
		}
		else if (!strcmp(tok, "g"))
		{
			color[0] = color[1] = color[2] = stack[0];
			top = 0;
		}
		else if (!strcmp(tok, "rg"))
		{
			color[0] = stack[0];
			color[1] = stack[1];
			color[2] = stack[2];
			top=0;
		}
		else
		{
			if (top < 3)
				stack[top] = fz_strtof(tok, &end);
			if (*end == 0)
				++top;
			else
				top = 0;
		}
	}
}