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
struct TYPE_5__ {scalar_t__ method; } ;
typedef  TYPE_1__ pdf_crypt_filter ;
struct TYPE_6__ {int length; scalar_t__ v; unsigned char* key; } ;
typedef  TYPE_2__ pdf_crypt ;
typedef  unsigned char num ;
typedef  unsigned char gen ;
typedef  int /*<<< orphan*/  fz_md5 ;

/* Variables and functions */
 scalar_t__ PDF_CRYPT_AESV2 ; 
 scalar_t__ PDF_CRYPT_AESV3 ; 
 int /*<<< orphan*/  fz_md5_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  fz_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_md5_update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static int
pdf_compute_object_key(pdf_crypt *crypt, pdf_crypt_filter *cf, int num, int gen, unsigned char *key, int max_len)
{
	fz_md5 md5;
	unsigned char message[5];
	int key_len = crypt->length / 8;

	if (key_len > max_len)
		key_len = max_len;

	/* Encryption method version 0 is undocumented, but a lucky
	   guess revealed that all streams/strings in those PDFs are
	   encrypted using the same 40 bit file enryption key using RC4. */
	if (crypt->v == 0 || cf->method == PDF_CRYPT_AESV3)
	{
		memcpy(key, crypt->key, key_len);
		return key_len;
	}

	fz_md5_init(&md5);
	fz_md5_update(&md5, crypt->key, key_len);
	message[0] = (num) & 0xFF;
	message[1] = (num >> 8) & 0xFF;
	message[2] = (num >> 16) & 0xFF;
	message[3] = (gen) & 0xFF;
	message[4] = (gen >> 8) & 0xFF;
	fz_md5_update(&md5, message, 5);

	if (cf->method == PDF_CRYPT_AESV2)
		fz_md5_update(&md5, (unsigned char *)"sAlT", 4);

	fz_md5_final(&md5, key);

	if (key_len + 5 > 16)
		return 16;
	return key_len + 5;
}