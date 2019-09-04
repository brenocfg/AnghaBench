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
typedef  int uint32_t ;
typedef  int h ;
typedef  int g ;
typedef  int f ;
typedef  int e ;
typedef  int d ;
typedef  int c ;
typedef  int b ;
typedef  int a ;
struct TYPE_3__ {int* state; } ;
typedef  TYPE_1__ SUM_CONTEXT ;

/* Variables and functions */
 int* K ; 
 int ROR (int,int) ; 
 int read_swap32 (unsigned char const*) ; 

__attribute__((used)) static __inline void sha256_transform(SUM_CONTEXT *ctx, const unsigned char *data)
{
	uint32_t a, b, c, d, e, f, g, h, j, x[16];

	a = ctx->state[0];
	b = ctx->state[1];
	c = ctx->state[2];
	d = ctx->state[3];
	e = ctx->state[4];
	f = ctx->state[5];
	g = ctx->state[6];
	h = ctx->state[7];

#define CH(x,y,z) ((z) ^ ((x) & ((y) ^ (z))))
#define MAJ(x,y,z) (((x) & (y)) | ((z) & ((x) | (y))))
// Nesting the ROR allows for single register compiler optimizations
#define S0(x) (ROR(ROR(ROR(x,9)^(x),11)^(x),2))
#define S1(x) (ROR(ROR(ROR(x,14)^(x),5)^(x),6))
#define s0(x) (ROR(ROR(x,11)^(x),7)^((x)>>3))
#define s1(x) (ROR(ROR(x,2)^(x),17)^((x)>>10))
#define BLK0(i) (x[i])
#define BLK2(i) (x[i] += s1(x[((i)-2)&15]) + x[((i)-7)&15] + s0(x[((i)-15)&15]))
#define R(a,b,c,d,e,f,g,h,i) \
	h += S1(e) + CH(e,f,g) + K[(i)+(j)] + (j ? BLK2(i) : BLK0(i)); \
	d += h; \
	h += S0(a) + MAJ(a, b, c)
#define RX_8(i) \
	R(a,b,c,d,e,f,g,h, i); \
	R(h,a,b,c,d,e,f,g, i+1); \
	R(g,h,a,b,c,d,e,f, i+2); \
	R(f,g,h,a,b,c,d,e, i+3); \
	R(e,f,g,h,a,b,c,d, i+4); \
	R(d,e,f,g,h,a,b,c, i+5); \
	R(c,d,e,f,g,h,a,b, i+6); \
	R(b,c,d,e,f,g,h,a, i+7)

#ifdef BIG_ENDIAN_HOST
	memcpy(x, data, sizeof(x));
#else
	{
		unsigned k;
		for (k = 0; k < 16; k += 4) {
			const unsigned char *p2 = data + k * 4;
			x[k] = read_swap32(p2);
			x[k + 1] = read_swap32(p2 + 4);
			x[k + 2] = read_swap32(p2 + 8);
			x[k + 3] = read_swap32(p2 + 12);
		}
	}
#endif

	for (j = 0; j < 64; j += 16) {
		RX_8(0);
		RX_8(8);
	}

#undef S0
#undef S1
#undef s0
#undef s1

	ctx->state[0] += a;
	ctx->state[1] += b;
	ctx->state[2] += c;
	ctx->state[3] += d;
	ctx->state[4] += e;
	ctx->state[5] += f;
	ctx->state[6] += g;
	ctx->state[7] += h;
}