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
typedef  int /*<<< orphan*/  svg_document ;
typedef  int /*<<< orphan*/  keyword ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 float FZ_DEGREE ; 
 int /*<<< orphan*/  FZ_ERROR_SYNTAX ; 
 int /*<<< orphan*/  fz_concat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_make_matrix (int,float,float,int,float,float) ; 
 int /*<<< orphan*/  fz_rotate (float) ; 
 int /*<<< orphan*/  fz_scale (float,float) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fz_translate (float,float) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ svg_is_alpha (char const) ; 
 scalar_t__ svg_is_digit (char const) ; 
 scalar_t__ svg_is_whitespace (char const) ; 
 scalar_t__ svg_is_whitespace_or_comma (char const) ; 
 char* svg_lex_number (float*,char const*) ; 
 float tanf (float) ; 

fz_matrix
svg_parse_transform(fz_context *ctx, svg_document *doc, const char *str, fz_matrix transform)
{
	char keyword[20];
	int keywordlen;
	float args[6];
	int nargs;

	nargs = 0;
	keywordlen = 0;

	while (*str)
	{
		while (svg_is_whitespace_or_comma(*str))
			str ++;
		if (*str == 0)
			break;

		/*
		 * Parse keyword and opening parenthesis.
		 */

		keywordlen = 0;
		while (svg_is_alpha(*str) && keywordlen < (int)sizeof(keyword) - 1)
			keyword[keywordlen++] = *str++;
		keyword[keywordlen] = 0;

		if (keywordlen == 0)
			fz_throw(ctx, FZ_ERROR_SYNTAX, "expected keyword in transform attribute");

		while (svg_is_whitespace(*str))
			str ++;

		if (*str != '(')
			fz_throw(ctx, FZ_ERROR_SYNTAX, "expected opening parenthesis in transform attribute");
		str ++;

		/*
		 * Parse list of numbers until closing parenthesis
		 */

		nargs = 0;
		while (*str && *str != ')' && nargs < 6)
		{
			while (svg_is_whitespace_or_comma(*str))
				str ++;
			if (svg_is_digit(*str))
				str = svg_lex_number(&args[nargs++], str);
			else
				break;
		}

		if (*str != ')')
			fz_throw(ctx, FZ_ERROR_SYNTAX, "expected closing parenthesis in transform attribute");
		str ++;

		/*
		 * Execute the transform.
		 */

		if (!strcmp(keyword, "matrix"))
		{
			if (nargs != 6)
				fz_throw(ctx, FZ_ERROR_SYNTAX, "wrong number of arguments to matrix(): %d", nargs);
			transform = fz_concat(fz_make_matrix(args[0], args[1], args[2], args[3], args[4], args[5]), transform);
		}

		else if (!strcmp(keyword, "translate"))
		{
			if (nargs != 2)
				fz_throw(ctx, FZ_ERROR_SYNTAX, "wrong number of arguments to translate(): %d", nargs);
			transform = fz_concat(fz_translate(args[0], args[1]), transform);
		}

		else if (!strcmp(keyword, "scale"))
		{
			if (nargs == 1)
				transform = fz_concat(fz_scale(args[0], args[0]), transform);
			else if (nargs == 2)
				transform = fz_concat(fz_scale(args[0], args[1]), transform);
			else
				fz_throw(ctx, FZ_ERROR_SYNTAX, "wrong number of arguments to scale(): %d", nargs);
		}

		else if (!strcmp(keyword, "rotate"))
		{
			if (nargs != 1)
				fz_throw(ctx, FZ_ERROR_SYNTAX, "wrong number of arguments to rotate(): %d", nargs);
			transform = fz_concat(fz_rotate(args[0]), transform);
		}

		else if (!strcmp(keyword, "skewX"))
		{
			if (nargs != 1)
				fz_throw(ctx, FZ_ERROR_SYNTAX, "wrong number of arguments to skewX(): %d", nargs);
			transform = fz_concat(fz_make_matrix(1, 0, tanf(args[0] * FZ_DEGREE), 1, 0, 0), transform);
		}

		else if (!strcmp(keyword, "skewY"))
		{
			if (nargs != 1)
				fz_throw(ctx, FZ_ERROR_SYNTAX, "wrong number of arguments to skewY(): %d", nargs);
			transform = fz_concat(fz_make_matrix(1, tanf(args[0] * FZ_DEGREE), 0, 1, 0, 0), transform);
		}

		else
		{
			fz_throw(ctx, FZ_ERROR_SYNTAX, "unknown transform function: %s", keyword);
		}
	}

	return transform;
}