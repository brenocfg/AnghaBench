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
struct TYPE_3__ {int /*<<< orphan*/  key; int /*<<< orphan*/  u; } ;
typedef  TYPE_1__ pdf_crypt ;
typedef  int /*<<< orphan*/  iv ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_aes ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_AES_ENCRYPT ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_aes_crypt_cbc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned char*,int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ fz_aes_setkey_enc (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  fz_memrnd (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nelem (unsigned char*) ; 
 int /*<<< orphan*/  pdf_compute_hardened_hash_r6 (int /*<<< orphan*/ *,unsigned char*,size_t,unsigned char*,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static void
pdf_compute_owner_password_r6(fz_context *ctx, pdf_crypt *crypt, unsigned char *password, size_t pwlen, unsigned char *outputpw, unsigned char *outputencryption)
{
	unsigned char validationsalt[8];
	unsigned char keysalt[8];
	unsigned char hash[32];
	unsigned char iv[16];
	fz_aes aes;

	/* Step a) - Generate random salts. */
	fz_memrnd(ctx, validationsalt, nelem(validationsalt));
	fz_memrnd(ctx, keysalt, nelem(keysalt));

	/* Step a) - Compute 32 byte hash given owner password, validation salt and user password. */
	pdf_compute_hardened_hash_r6(ctx, password, pwlen, validationsalt, crypt->u, outputpw);
	memcpy(outputpw + 32, validationsalt, nelem(validationsalt));
	memcpy(outputpw + 40, keysalt, nelem(keysalt));

	/* Step b) - Compute 32 byte hash given owner password, user salt and user password. */
	pdf_compute_hardened_hash_r6(ctx, password, pwlen, keysalt, crypt->u, hash);

	/* Step b) - Use hash as AES-key when encrypting the file encryption key. */
	memset(iv, 0, sizeof(iv));
	if (fz_aes_setkey_enc(&aes, hash, 256))
		fz_throw(ctx, FZ_ERROR_GENERIC, "AES key init failed (keylen=256)");
	fz_aes_crypt_cbc(&aes, FZ_AES_ENCRYPT, 32, iv, crypt->key, outputencryption);
}