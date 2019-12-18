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
 int /*<<< orphan*/  PADLOCK_ACE ; 
 int /*<<< orphan*/  fz_aes_crypt_ecb (int /*<<< orphan*/ *,int,unsigned char const*,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 scalar_t__ padlock_supports (int /*<<< orphan*/ ) ; 
 scalar_t__ padlock_xcryptcbc (int /*<<< orphan*/ *,int,size_t,unsigned char*,unsigned char const*,unsigned char*) ; 

void fz_aes_crypt_cbc( aes_context *ctx,
	int mode,
	size_t length,
	unsigned char iv[16],
	const unsigned char *input,
	unsigned char *output )
{
	int i;
	unsigned char temp[16];

#if defined(XYSSL_PADLOCK_C) && defined(XYSSL_HAVE_X86)
	if( padlock_supports( PADLOCK_ACE ) )
	{
		if( padlock_xcryptcbc( ctx, mode, length, iv, input, output ) == 0 )
			return;
	}
#endif

	if( mode == FZ_AES_DECRYPT )
	{
		while( length > 0 )
		{
			memcpy( temp, input, 16 );
			fz_aes_crypt_ecb( ctx, mode, input, output );

			for( i = 0; i < 16; i++ )
				output[i] = (unsigned char)( output[i] ^ iv[i] );

			memcpy( iv, temp, 16 );

			input += 16;
			output += 16;
			length -= 16;
		}
	}
	else
	{
		while( length > 0 )
		{
			for( i = 0; i < 16; i++ )
				output[i] = (unsigned char)( input[i] ^ iv[i] );

			fz_aes_crypt_ecb( ctx, mode, output, output );
			memcpy( iv, output, 16 );

			input += 16;
			output += 16;
			length -= 16;
		}
	}
}