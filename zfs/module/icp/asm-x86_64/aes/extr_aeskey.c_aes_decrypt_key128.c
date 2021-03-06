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
 int MAX_AES_NB ; 
 int /*<<< orphan*/  d_vars ; 
 int inv_mcol (int) ; 
 int /*<<< orphan*/  k4e (int*,int) ; 
 int /*<<< orphan*/  kd4 (int*,int) ; 
 int /*<<< orphan*/  kdf4 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdl4 (int*,int) ; 
 size_t v (int,int) ; 
 int word_in (unsigned char const*,int) ; 

__attribute__((used)) static void
aes_decrypt_key128(const unsigned char *key, uint32_t rk[])
{
	uint32_t	ss[5];
#if defined(d_vars)
	d_vars;
#endif
	rk[v(40, (0))] = ss[0] = word_in(key, 0);
	rk[v(40, (1))] = ss[1] = word_in(key, 1);
	rk[v(40, (2))] = ss[2] = word_in(key, 2);
	rk[v(40, (3))] = ss[3] = word_in(key, 3);

#ifdef DEC_KS_UNROLL
	kdf4(rk, 0); kd4(rk, 1);
	kd4(rk, 2);  kd4(rk, 3);
	kd4(rk, 4);  kd4(rk, 5);
	kd4(rk, 6);  kd4(rk, 7);
	kd4(rk, 8);  kdl4(rk, 9);
#else
	{
		uint32_t	i;
		for (i = 0; i < 10; ++i)
			k4e(rk, i);
#if !(DEC_ROUND == NO_TABLES)
		for (i = MAX_AES_NB; i < 10 * MAX_AES_NB; ++i)
			rk[i] = inv_mcol(rk[i]);
#endif
	}
#endif	/* DEC_KS_UNROLL */
}