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
typedef  double real ;

/* Variables and functions */
 double COS6_1 ; 
 double COS6_2 ; 
 double REAL_MUL (double,double) ; 
 size_t SBLIMIT ; 
 double* tfcos12 ; 

__attribute__((used)) static void dct12(real *in,real *rawout1,real *rawout2,register real *wi,register real *ts)
{
#define DCT12_PART1 \
	in5 = in[5*3];  \
	in5 += (in4 = in[4*3]); \
	in4 += (in3 = in[3*3]); \
	in3 += (in2 = in[2*3]); \
	in2 += (in1 = in[1*3]); \
	in1 += (in0 = in[0*3]); \
	\
	in5 += in3; in3 += in1; \
	\
	in2 = REAL_MUL(in2, COS6_1); \
	in3 = REAL_MUL(in3, COS6_1);

#define DCT12_PART2 \
	in0 += REAL_MUL(in4, COS6_2); \
	\
	in4 = in0 + in2; \
	in0 -= in2;      \
	\
	in1 += REAL_MUL(in5, COS6_2); \
	\
	in5 = REAL_MUL((in1 + in3), tfcos12[0]); \
	in1 = REAL_MUL((in1 - in3), tfcos12[2]); \
	\
	in3 = in4 + in5; \
	in4 -= in5;      \
	\
	in2 = in0 + in1; \
	in0 -= in1;

	{
		real in0,in1,in2,in3,in4,in5;
		register real *out1 = rawout1;
		ts[SBLIMIT*0] = out1[0]; ts[SBLIMIT*1] = out1[1]; ts[SBLIMIT*2] = out1[2];
		ts[SBLIMIT*3] = out1[3]; ts[SBLIMIT*4] = out1[4]; ts[SBLIMIT*5] = out1[5];
 
		DCT12_PART1

		{
			real tmp0,tmp1 = (in0 - in4);
			{
				real tmp2 = REAL_MUL((in1 - in5), tfcos12[1]);
				tmp0 = tmp1 + tmp2;
				tmp1 -= tmp2;
			}
			ts[(17-1)*SBLIMIT] = out1[17-1] + REAL_MUL(tmp0, wi[11-1]);
			ts[(12+1)*SBLIMIT] = out1[12+1] + REAL_MUL(tmp0, wi[6+1]);
			ts[(6 +1)*SBLIMIT] = out1[6 +1] + REAL_MUL(tmp1, wi[1]);
			ts[(11-1)*SBLIMIT] = out1[11-1] + REAL_MUL(tmp1, wi[5-1]);
		}

		DCT12_PART2

		ts[(17-0)*SBLIMIT] = out1[17-0] + REAL_MUL(in2, wi[11-0]);
		ts[(12+0)*SBLIMIT] = out1[12+0] + REAL_MUL(in2, wi[6+0]);
		ts[(12+2)*SBLIMIT] = out1[12+2] + REAL_MUL(in3, wi[6+2]);
		ts[(17-2)*SBLIMIT] = out1[17-2] + REAL_MUL(in3, wi[11-2]);

		ts[(6 +0)*SBLIMIT]  = out1[6+0] + REAL_MUL(in0, wi[0]);
		ts[(11-0)*SBLIMIT] = out1[11-0] + REAL_MUL(in0, wi[5-0]);
		ts[(6 +2)*SBLIMIT]  = out1[6+2] + REAL_MUL(in4, wi[2]);
		ts[(11-2)*SBLIMIT] = out1[11-2] + REAL_MUL(in4, wi[5-2]);
	}

	in++;

	{
		real in0,in1,in2,in3,in4,in5;
		register real *out2 = rawout2;
 
		DCT12_PART1

		{
			real tmp0,tmp1 = (in0 - in4);
			{
				real tmp2 = REAL_MUL((in1 - in5), tfcos12[1]);
				tmp0 = tmp1 + tmp2;
				tmp1 -= tmp2;
			}
			out2[5-1] = REAL_MUL(tmp0, wi[11-1]);
			out2[0+1] = REAL_MUL(tmp0, wi[6+1]);
			ts[(12+1)*SBLIMIT] += REAL_MUL(tmp1, wi[1]);
			ts[(17-1)*SBLIMIT] += REAL_MUL(tmp1, wi[5-1]);
		}

		DCT12_PART2

		out2[5-0] = REAL_MUL(in2, wi[11-0]);
		out2[0+0] = REAL_MUL(in2, wi[6+0]);
		out2[0+2] = REAL_MUL(in3, wi[6+2]);
		out2[5-2] = REAL_MUL(in3, wi[11-2]);

		ts[(12+0)*SBLIMIT] += REAL_MUL(in0, wi[0]);
		ts[(17-0)*SBLIMIT] += REAL_MUL(in0, wi[5-0]);
		ts[(12+2)*SBLIMIT] += REAL_MUL(in4, wi[2]);
		ts[(17-2)*SBLIMIT] += REAL_MUL(in4, wi[5-2]);
	}

	in++; 

	{
		real in0,in1,in2,in3,in4,in5;
		register real *out2 = rawout2;
		out2[12]=out2[13]=out2[14]=out2[15]=out2[16]=out2[17]=0.0;

		DCT12_PART1

		{
			real tmp0,tmp1 = (in0 - in4);
			{
				real tmp2 = REAL_MUL((in1 - in5), tfcos12[1]);
				tmp0 = tmp1 + tmp2;
				tmp1 -= tmp2;
			}
			out2[11-1] = REAL_MUL(tmp0, wi[11-1]);
			out2[6 +1] = REAL_MUL(tmp0, wi[6+1]);
			out2[0+1] += REAL_MUL(tmp1, wi[1]);
			out2[5-1] += REAL_MUL(tmp1, wi[5-1]);
		}

		DCT12_PART2

		out2[11-0] = REAL_MUL(in2, wi[11-0]);
		out2[6 +0] = REAL_MUL(in2, wi[6+0]);
		out2[6 +2] = REAL_MUL(in3, wi[6+2]);
		out2[11-2] = REAL_MUL(in3, wi[11-2]);

		out2[0+0] += REAL_MUL(in0, wi[0]);
		out2[5-0] += REAL_MUL(in0, wi[5-0]);
		out2[0+2] += REAL_MUL(in4, wi[2]);
		out2[5-2] += REAL_MUL(in4, wi[5-2]);
	}
}