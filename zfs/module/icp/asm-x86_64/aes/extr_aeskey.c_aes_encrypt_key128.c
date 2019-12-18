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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ke4 (int*,int) ; 
 int word_in (unsigned char const*,int) ; 

__attribute__((used)) static void
aes_encrypt_key128(const unsigned char *key, uint32_t rk[])
{
	uint32_t	ss[4];

	rk[0] = ss[0] = word_in(key, 0);
	rk[1] = ss[1] = word_in(key, 1);
	rk[2] = ss[2] = word_in(key, 2);
	rk[3] = ss[3] = word_in(key, 3);

#ifdef ENC_KS_UNROLL
	ke4(rk, 0);  ke4(rk, 1);
	ke4(rk, 2);  ke4(rk, 3);
	ke4(rk, 4);  ke4(rk, 5);
	ke4(rk, 6);  ke4(rk, 7);
	ke4(rk, 8);
#else
	{
		uint32_t	i;
		for (i = 0; i < 9; ++i)
			ke4(rk, i);
	}
#endif	/* ENC_KS_UNROLL */
	ke4(rk, 9);
}