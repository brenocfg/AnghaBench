#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ method; } ;
struct TYPE_5__ {TYPE_4__ strf; } ;
typedef  TYPE_1__ pdf_crypt ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_arc4 ;
typedef  int /*<<< orphan*/  fz_aes ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_AES_ENCRYPT ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 scalar_t__ PDF_CRYPT_AESV2 ; 
 scalar_t__ PDF_CRYPT_AESV3 ; 
 scalar_t__ PDF_CRYPT_RC4 ; 
 int /*<<< orphan*/  fz_aes_crypt_cbc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned char*,unsigned char*,unsigned char*) ; 
 scalar_t__ fz_aes_setkey_enc (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  fz_arc4_encrypt (int /*<<< orphan*/ *,unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  fz_arc4_init (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  fz_memrnd (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int pdf_compute_object_key (TYPE_1__*,TYPE_4__*,int,int,unsigned char*,int) ; 

void pdf_encrypt_data(fz_context *ctx, pdf_crypt *crypt, int num, int gen, void (*write_data)(fz_context *ctx, void *, const unsigned char *, int), void *arg, const unsigned char *s, int n)
{
	unsigned char buffer[256];
	unsigned char key[32];
	int keylen;

	if (crypt == NULL)
	{
		write_data(ctx, arg, s, n);
		return;
	}

	keylen = pdf_compute_object_key(crypt, &crypt->strf, num, gen, key, 32);

	if (crypt->strf.method == PDF_CRYPT_RC4)
	{
		fz_arc4 arc4;
		fz_arc4_init(&arc4, key, keylen);
		while (n > 0)
		{
			int len = n;
			if (len > (int)sizeof(buffer))
				len = sizeof(buffer);
			fz_arc4_encrypt(&arc4, buffer, s, len);
			write_data(ctx, arg, buffer, len);
			s += len;
			n -= len;
		}
		return;
	}

	if (crypt->strf.method == PDF_CRYPT_AESV2 || crypt->strf.method == PDF_CRYPT_AESV3)
	{
		fz_aes aes;
		unsigned char iv[16];

		/* Empty strings can be represented by empty strings */
		if (n == 0)
			return;

		if (fz_aes_setkey_enc(&aes, key, keylen * 8))
			fz_throw(ctx, FZ_ERROR_GENERIC, "AES key init failed (keylen=%d)", keylen * 8);

		fz_memrnd(ctx, iv, 16);
		write_data(ctx, arg, iv, 16);

		while (n > 0)
		{
			int len = n;
			if (len > 16)
				len = 16;
			memcpy(buffer, s, len);
			if (len != 16)
				memset(&buffer[len], 16-len, 16-len);
			fz_aes_crypt_cbc(&aes, FZ_AES_ENCRYPT, 16, iv, buffer, buffer+16);
			write_data(ctx, arg, buffer+16, 16);
			s += 16;
			n -= 16;
		}
		if (n == 0) {
			memset(buffer, 16, 16);
			fz_aes_crypt_cbc(&aes, FZ_AES_ENCRYPT, 16, iv, buffer, buffer+16);
			write_data(ctx, arg, buffer+16, 16);
		}
		return;
	}

	/* Should never happen, but... */
	write_data(ctx, arg, s, n);
}