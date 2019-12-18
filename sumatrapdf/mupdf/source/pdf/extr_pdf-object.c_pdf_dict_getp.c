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
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  OBJ_IS_DICT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RESOLVE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * pdf_dict_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

pdf_obj *
pdf_dict_getp(fz_context *ctx, pdf_obj *obj, const char *keys)
{
	char buf[256];
	char *k, *e;

	RESOLVE(obj);
	if (!OBJ_IS_DICT(obj))
		return NULL;
	if (strlen(keys)+1 > 256)
		fz_throw(ctx, FZ_ERROR_GENERIC, "path too long");

	strcpy(buf, keys);

	e = buf;
	while (*e && obj)
	{
		k = e;
		while (*e != '/' && *e != '\0')
			e++;

		if (*e == '/')
		{
			*e = '\0';
			e++;
		}

		obj = pdf_dict_gets(ctx, obj, k);
	}

	return obj;
}