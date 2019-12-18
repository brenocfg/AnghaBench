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
typedef  int /*<<< orphan*/  aes_context ;

/* Variables and functions */
 int FZ_AES_DECRYPT ; 
 int /*<<< orphan*/  FZ_AES_ENCRYPT ; 
 int /*<<< orphan*/  fz_aes_crypt_ecb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,unsigned char*) ; 

void fz_aes_crypt_cfb( aes_context *ctx,
	int mode,
	int length,
	int *iv_off,
	unsigned char iv[16],
	const unsigned char *input,
	unsigned char *output )
{
	int c, n = *iv_off;

	if( mode == FZ_AES_DECRYPT )
	{
		while( length-- )
		{
			if( n == 0 )
				fz_aes_crypt_ecb( ctx, FZ_AES_ENCRYPT, iv, iv );

			c = *input++;
			*output++ = (unsigned char)( c ^ iv[n] );
			iv[n] = (unsigned char) c;

			n = (n + 1) & 0x0F;
		}
	}
	else
	{
		while( length-- )
		{
			if( n == 0 )
				fz_aes_crypt_ecb( ctx, FZ_AES_ENCRYPT, iv, iv );

			iv[n] = *output++ = (unsigned char)( iv[n] ^ *input++ );

			n = (n + 1) & 0x0F;
		}
	}

	*iv_off = n;
}