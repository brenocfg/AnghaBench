#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_5__ {int length; void* method; } ;
typedef  TYPE_1__ pdf_crypt_filter ;
struct TYPE_6__ {int length; int r; int /*<<< orphan*/ * cf; } ;
typedef  TYPE_2__ pdf_crypt ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  AESV2 ; 
 int /*<<< orphan*/  AESV3 ; 
 int /*<<< orphan*/  CFM ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  Identity ; 
 int /*<<< orphan*/  Length ; 
 int /*<<< orphan*/  None ; 
 void* PDF_CRYPT_AESV2 ; 
 void* PDF_CRYPT_AESV3 ; 
 void* PDF_CRYPT_NONE ; 
 void* PDF_CRYPT_RC4 ; 
 int /*<<< orphan*/ * PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StdCF ; 
 int /*<<< orphan*/  V2 ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pdf_dict_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_name_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_to_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_to_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_to_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pdf_parse_crypt_filter(fz_context *ctx, pdf_crypt_filter *cf, pdf_crypt *crypt, pdf_obj *name)
{
	pdf_obj *obj;
	pdf_obj *dict;
	int is_identity = (pdf_name_eq(ctx, name, PDF_NAME(Identity)));
	int is_stdcf = (!is_identity && pdf_name_eq(ctx, name, PDF_NAME(StdCF)));

	if (!is_identity && !is_stdcf)
		fz_throw(ctx, FZ_ERROR_GENERIC, "Crypt Filter not Identity or StdCF (%d 0 R)", pdf_to_num(ctx, crypt->cf));

	cf->method = PDF_CRYPT_NONE;
	cf->length = crypt->length;

	if (!crypt->cf)
	{
		cf->method = (is_identity ? PDF_CRYPT_NONE : PDF_CRYPT_RC4);
		return;
	}

	dict = pdf_dict_get(ctx, crypt->cf, name);
	if (pdf_is_dict(ctx, dict))
	{
		obj = pdf_dict_get(ctx, dict, PDF_NAME(CFM));
		if (pdf_is_name(ctx, obj))
		{
			if (pdf_name_eq(ctx, PDF_NAME(None), obj))
				cf->method = PDF_CRYPT_NONE;
			else if (pdf_name_eq(ctx, PDF_NAME(V2), obj))
				cf->method = PDF_CRYPT_RC4;
			else if (pdf_name_eq(ctx, PDF_NAME(AESV2), obj))
				cf->method = PDF_CRYPT_AESV2;
			else if (pdf_name_eq(ctx, PDF_NAME(AESV3), obj))
				cf->method = PDF_CRYPT_AESV3;
			else
				fz_warn(ctx, "unknown encryption method: %s", pdf_to_name(ctx, obj));
		}

		obj = pdf_dict_get(ctx, dict, PDF_NAME(Length));
		if (pdf_is_int(ctx, obj))
			cf->length = pdf_to_int(ctx, obj);
	}
	else if (!is_identity)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot parse crypt filter (%d 0 R)", pdf_to_num(ctx, crypt->cf));

	/* the length for crypt filters is supposed to be in bytes not bits */
	if (cf->length < 40)
		cf->length = cf->length * 8;

	if ((cf->length % 8) != 0)
		fz_throw(ctx, FZ_ERROR_GENERIC, "invalid key length: %d", cf->length);

	if ((crypt->r == 1 || crypt->r == 2 || crypt->r == 3 || crypt->r == 4) &&
		(cf->length < 40 || cf->length > 128))
		fz_throw(ctx, FZ_ERROR_GENERIC, "invalid key length: %d", cf->length);
	if ((crypt->r == 5 || crypt->r == 6) && cf->length != 256)
		fz_throw(ctx, FZ_ERROR_GENERIC, "invalid key length: %d", cf->length);
}