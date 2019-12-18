#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__* state; } ;
struct hash_state {TYPE_1__ sha512; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 scalar_t__ Gamma0 (scalar_t__) ; 
 scalar_t__ Gamma1 (scalar_t__) ; 
 int /*<<< orphan*/  LOAD64H (scalar_t__,unsigned char const*) ; 
 int /*<<< orphan*/  RND (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void sha512_compress(struct hash_state * md, const unsigned char *buf)
{
	__u64 S[8], W[80], t0, t1;
	int i;

	/* copy state into S */
	for (i = 0; i < 8; i++) {
		S[i] = md->sha512.state[i];
	}

	/* copy the state into 1024-bits into W[0..15] */
	for (i = 0; i < 16; i++) {
		LOAD64H(W[i], buf + (8*i));
	}

	/* fill W[16..79] */
	for (i = 16; i < 80; i++) {
		W[i] = Gamma1(W[i - 2]) + W[i - 7] +
			Gamma0(W[i - 15]) + W[i - 16];
	}

	for (i = 0; i < 80; i += 8) {
		RND(S[0],S[1],S[2],S[3],S[4],S[5],S[6],S[7],i+0);
		RND(S[7],S[0],S[1],S[2],S[3],S[4],S[5],S[6],i+1);
		RND(S[6],S[7],S[0],S[1],S[2],S[3],S[4],S[5],i+2);
		RND(S[5],S[6],S[7],S[0],S[1],S[2],S[3],S[4],i+3);
		RND(S[4],S[5],S[6],S[7],S[0],S[1],S[2],S[3],i+4);
		RND(S[3],S[4],S[5],S[6],S[7],S[0],S[1],S[2],i+5);
		RND(S[2],S[3],S[4],S[5],S[6],S[7],S[0],S[1],i+6);
		RND(S[1],S[2],S[3],S[4],S[5],S[6],S[7],S[0],i+7);
	}

	 /* feedback */
	for (i = 0; i < 8; i++) {
		md->sha512.state[i] = md->sha512.state[i] + S[i];
	}
}