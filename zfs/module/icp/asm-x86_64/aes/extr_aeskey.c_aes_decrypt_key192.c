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
 int ff (int) ; 
 int inv_mcol (int) ; 
 int /*<<< orphan*/  k6e (int*,int) ; 
 int /*<<< orphan*/  k6ef (int*,int) ; 
 int /*<<< orphan*/  kd6 (int*,int) ; 
 int /*<<< orphan*/  kdf6 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdl6 (int*,int) ; 
 size_t v (int,int) ; 
 int word_in (unsigned char const*,int) ; 

__attribute__((used)) static void
aes_decrypt_key192(const unsigned char *key, uint32_t rk[])
{
	uint32_t	ss[7];
#if defined(d_vars)
	d_vars;
#endif
	rk[v(48, (0))] = ss[0] = word_in(key, 0);
	rk[v(48, (1))] = ss[1] = word_in(key, 1);
	rk[v(48, (2))] = ss[2] = word_in(key, 2);
	rk[v(48, (3))] = ss[3] = word_in(key, 3);

#ifdef DEC_KS_UNROLL
	ss[4] = word_in(key, 4);
	rk[v(48, (4))] = ff(ss[4]);
	ss[5] = word_in(key, 5);
	rk[v(48, (5))] = ff(ss[5]);
	kdf6(rk, 0); kd6(rk, 1);
	kd6(rk, 2);  kd6(rk, 3);
	kd6(rk, 4);  kd6(rk, 5);
	kd6(rk, 6);  kdl6(rk, 7);
#else
	rk[v(48, (4))] = ss[4] = word_in(key, 4);
	rk[v(48, (5))] = ss[5] = word_in(key, 5);
	{
		uint32_t	i;

		for (i = 0; i < 7; ++i)
			k6e(rk, i);
		k6ef(rk, 7);
#if !(DEC_ROUND == NO_TABLES)
		for (i = MAX_AES_NB; i < 12 * MAX_AES_NB; ++i)
			rk[i] = inv_mcol(rk[i]);
#endif
	}
#endif
}