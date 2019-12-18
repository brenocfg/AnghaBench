#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_4__ {scalar_t__ method; } ;
struct TYPE_5__ {TYPE_1__ strf; } ;
typedef  TYPE_2__ pdf_crypt ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_arc4 ;
typedef  int /*<<< orphan*/  fz_aes ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_AES_DECRYPT ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 scalar_t__ PDF_CRYPT_AESV2 ; 
 scalar_t__ PDF_CRYPT_AESV3 ; 
 scalar_t__ PDF_CRYPT_RC4 ; 
 int /*<<< orphan*/  fz_aes_crypt_cbc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned char*,unsigned char*,unsigned char*) ; 
 scalar_t__ fz_aes_setkey_dec (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  fz_arc4_encrypt (int /*<<< orphan*/ *,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  fz_arc4_init (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_get_val (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_dict_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_set_str_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ pdf_to_str_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pdf_to_str_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pdf_crypt_obj_imp(fz_context *ctx, pdf_crypt *crypt, pdf_obj *obj, unsigned char *key, int keylen)
{
	unsigned char *s;
	int i, n;

	if (pdf_is_indirect(ctx, obj))
		return;

	if (pdf_is_string(ctx, obj))
	{
		s = (unsigned char *)pdf_to_str_buf(ctx, obj);
		n = pdf_to_str_len(ctx, obj);

		if (crypt->strf.method == PDF_CRYPT_RC4)
		{
			fz_arc4 arc4;
			fz_arc4_init(&arc4, key, keylen);
			fz_arc4_encrypt(&arc4, s, s, n);
		}

		if (crypt->strf.method == PDF_CRYPT_AESV2 || crypt->strf.method == PDF_CRYPT_AESV3)
		{
			if (n == 0)
			{
				/* Empty strings are permissible */
			}
			else if (n & 15 || n < 32)
				fz_warn(ctx, "invalid string length for aes encryption");
			else
			{
				unsigned char iv[16];
				fz_aes aes;
				memcpy(iv, s, 16);
				if (fz_aes_setkey_dec(&aes, key, keylen * 8))
					fz_throw(ctx, FZ_ERROR_GENERIC, "AES key init failed (keylen=%d)", keylen * 8);
				fz_aes_crypt_cbc(&aes, FZ_AES_DECRYPT, n - 16, iv, s + 16, s);
				/* delete space used for iv and padding bytes at end */
				if (s[n - 17] < 1 || s[n - 17] > 16)
					fz_warn(ctx, "aes padding out of range");
				else
					pdf_set_str_len(ctx, obj, n - 16 - s[n - 17]);
			}
		}
	}

	else if (pdf_is_array(ctx, obj))
	{
		n = pdf_array_len(ctx, obj);
		for (i = 0; i < n; i++)
		{
			pdf_crypt_obj_imp(ctx, crypt, pdf_array_get(ctx, obj, i), key, keylen);
		}
	}

	else if (pdf_is_dict(ctx, obj))
	{
		n = pdf_dict_len(ctx, obj);
		for (i = 0; i < n; i++)
		{
			pdf_crypt_obj_imp(ctx, crypt, pdf_dict_get_val(ctx, obj, i), key, keylen);
		}
	}
}