#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  key; scalar_t__ encrypt_metadata; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ pdf_crypt ;
typedef  int /*<<< orphan*/  iv ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_aes ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_AES_ENCRYPT ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_aes_crypt_cbc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned char*,unsigned char*,unsigned char*) ; 
 scalar_t__ fz_aes_setkey_enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_memrnd (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 

__attribute__((used)) static void
pdf_compute_permissions_r6(fz_context *ctx, pdf_crypt *crypt, unsigned char *output)
{
	unsigned char buf[16];
	unsigned char iv[16];
	fz_aes aes;

	/* Steps a) and b) - Extend permissions field and put into lower order bytes. */
	memcpy(buf, (unsigned char *) &crypt->p, 4);
	memset(&buf[4], 0xff, 4);

	/* Step c) - Encode EncryptMetadata as T/F. */
	buf[8] = crypt->encrypt_metadata ? 'T' : 'F';

	/* Step d) - Encode ASCII characters "adb". */
	buf[9] = 'a';
	buf[10] = 'd';
	buf[11] = 'b';

	/* Step e) - Encode 4 random bytes. */
	fz_memrnd(ctx, &buf[12], 4);

	/* Step f) - Use file encryption key as AES-key when encrypting buffer. */
	memset(iv, 0, sizeof(iv));
	if (fz_aes_setkey_enc(&aes, crypt->key, 256))
		fz_throw(ctx, FZ_ERROR_GENERIC, "AES key init failed (keylen=256)");
	fz_aes_crypt_cbc(&aes, FZ_AES_ENCRYPT, 16, iv, buf, output);
}