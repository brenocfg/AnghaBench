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
typedef  int /*<<< orphan*/  pdf_token ;

/* Variables and functions */
 int /*<<< orphan*/  PDF_TOK_ENDOBJ ; 
 int /*<<< orphan*/  PDF_TOK_ENDSTREAM ; 
 int /*<<< orphan*/  PDF_TOK_ERROR ; 
 int /*<<< orphan*/  PDF_TOK_FALSE ; 
 int /*<<< orphan*/  PDF_TOK_KEYWORD ; 
 int /*<<< orphan*/  PDF_TOK_NULL ; 
 int /*<<< orphan*/  PDF_TOK_OBJ ; 
 int /*<<< orphan*/  PDF_TOK_R ; 
 int /*<<< orphan*/  PDF_TOK_STARTXREF ; 
 int /*<<< orphan*/  PDF_TOK_STREAM ; 
 int /*<<< orphan*/  PDF_TOK_TRAILER ; 
 int /*<<< orphan*/  PDF_TOK_TRUE ; 
 int /*<<< orphan*/  PDF_TOK_XREF ; 
 int /*<<< orphan*/  fz_isprint (char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static pdf_token
pdf_token_from_keyword(char *key)
{
	switch (*key)
	{
	case 'R':
		if (!strcmp(key, "R")) return PDF_TOK_R;
		break;
	case 't':
		if (!strcmp(key, "true")) return PDF_TOK_TRUE;
		if (!strcmp(key, "trailer")) return PDF_TOK_TRAILER;
		break;
	case 'f':
		if (!strcmp(key, "false")) return PDF_TOK_FALSE;
		break;
	case 'n':
		if (!strcmp(key, "null")) return PDF_TOK_NULL;
		break;
	case 'o':
		if (!strcmp(key, "obj")) return PDF_TOK_OBJ;
		break;
	case 'e':
		if (!strcmp(key, "endobj")) return PDF_TOK_ENDOBJ;
		if (!strcmp(key, "endstream")) return PDF_TOK_ENDSTREAM;
		break;
	case 's':
		if (!strcmp(key, "stream")) return PDF_TOK_STREAM;
		if (!strcmp(key, "startxref")) return PDF_TOK_STARTXREF;
		break;
	case 'x':
		if (!strcmp(key, "xref")) return PDF_TOK_XREF;
		break;
	}

	while (*key)
	{
		if (!fz_isprint(*key))
			return PDF_TOK_ERROR;
		++key;
	}

	return PDF_TOK_KEYWORD;
}