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
struct TYPE_3__ {int length; unsigned char* o; int r; int /*<<< orphan*/  encrypt_metadata; int /*<<< orphan*/  id; scalar_t__ p; } ;
typedef  TYPE_1__ pdf_crypt ;
typedef  unsigned char p ;
typedef  int /*<<< orphan*/  fz_md5 ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int fz_clampi (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_md5_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  fz_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_md5_update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 unsigned char* padding ; 
 scalar_t__ pdf_to_str_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pdf_to_str_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pdf_compute_encryption_key(fz_context *ctx, pdf_crypt *crypt, unsigned char *password, size_t pwlen, unsigned char *key)
{
	unsigned char buf[32];
	unsigned int p;
	int i, n;
	fz_md5 md5;

	n = fz_clampi(crypt->length / 8, 0, 16);

	/* Step 1 - copy and pad password string */
	if (pwlen > 32)
		pwlen = 32;
	memcpy(buf, password, pwlen);
	memcpy(buf + pwlen, padding, 32 - pwlen);

	/* Step 2 - init md5 and pass value of step 1 */
	fz_md5_init(&md5);
	fz_md5_update(&md5, buf, 32);

	/* Step 3 - pass O value */
	fz_md5_update(&md5, crypt->o, 32);

	/* Step 4 - pass P value as unsigned int, low-order byte first */
	p = (unsigned int) crypt->p;
	buf[0] = (p) & 0xFF;
	buf[1] = (p >> 8) & 0xFF;
	buf[2] = (p >> 16) & 0xFF;
	buf[3] = (p >> 24) & 0xFF;
	fz_md5_update(&md5, buf, 4);

	/* Step 5 - pass first element of ID array */
	fz_md5_update(&md5, (unsigned char *)pdf_to_str_buf(ctx, crypt->id), pdf_to_str_len(ctx, crypt->id));

	/* Step 6 (revision 4 or greater) - if metadata is not encrypted pass 0xFFFFFFFF */
	if (crypt->r >= 4)
	{
		if (!crypt->encrypt_metadata)
		{
			buf[0] = 0xFF;
			buf[1] = 0xFF;
			buf[2] = 0xFF;
			buf[3] = 0xFF;
			fz_md5_update(&md5, buf, 4);
		}
	}

	/* Step 7 - finish the hash */
	fz_md5_final(&md5, buf);

	/* Step 8 (revision 3 or greater) - do some voodoo 50 times */
	if (crypt->r >= 3)
	{
		for (i = 0; i < 50; i++)
		{
			fz_md5_init(&md5);
			fz_md5_update(&md5, buf, n);
			fz_md5_final(&md5, buf);
		}
	}

	/* Step 9 - the key is the first 'n' bytes of the result */
	memcpy(key, buf, n);
}