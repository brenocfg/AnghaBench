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
typedef  int uint64_t ;
struct aes_block {int a; unsigned long long b; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int htonll (int) ; 
 void* ntohll (int) ; 

__attribute__((used)) static void
gcm_generic_mul(uint64_t *x_in, uint64_t *y, uint64_t *res)
{
	static const uint64_t R = 0xe100000000000000ULL;
	struct aes_block z = {0, 0};
	struct aes_block v;
	uint64_t x;
	int i, j;

	v.a = ntohll(y[0]);
	v.b = ntohll(y[1]);

	for (j = 0; j < 2; j++) {
		x = ntohll(x_in[j]);
		for (i = 0; i < 64; i++, x <<= 1) {
			if (x & 0x8000000000000000ULL) {
				z.a ^= v.a;
				z.b ^= v.b;
			}
			if (v.b & 1ULL) {
				v.b = (v.a << 63)|(v.b >> 1);
				v.a = (v.a >> 1) ^ R;
			} else {
				v.b = (v.a << 63)|(v.b >> 1);
				v.a = v.a >> 1;
			}
		}
	}
	res[0] = htonll(z.a);
	res[1] = htonll(z.b);
}