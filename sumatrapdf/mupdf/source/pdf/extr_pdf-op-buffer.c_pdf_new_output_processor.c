#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_processor ;
struct TYPE_4__ {int /*<<< orphan*/  op_gs_UseBlackPtComp; int /*<<< orphan*/  op_gs_OPM; int /*<<< orphan*/  op_gs_op; int /*<<< orphan*/  op_gs_OP; int /*<<< orphan*/  op_EX; int /*<<< orphan*/  op_BX; int /*<<< orphan*/  op_EMC; int /*<<< orphan*/  op_BDC; int /*<<< orphan*/  op_BMC; int /*<<< orphan*/  op_DP; int /*<<< orphan*/  op_MP; int /*<<< orphan*/  op_Do_form; int /*<<< orphan*/  op_Do_image; int /*<<< orphan*/  op_sh; int /*<<< orphan*/  op_BI; int /*<<< orphan*/  op_k; int /*<<< orphan*/  op_K; int /*<<< orphan*/  op_rg; int /*<<< orphan*/  op_RG; int /*<<< orphan*/  op_g; int /*<<< orphan*/  op_G; int /*<<< orphan*/  op_sc_shade; int /*<<< orphan*/  op_SC_shade; int /*<<< orphan*/  op_sc_pattern; int /*<<< orphan*/  op_SC_pattern; int /*<<< orphan*/  op_sc_color; int /*<<< orphan*/  op_SC_color; int /*<<< orphan*/  op_cs; int /*<<< orphan*/  op_CS; int /*<<< orphan*/  op_d1; int /*<<< orphan*/  op_d0; int /*<<< orphan*/  op_dquote; int /*<<< orphan*/  op_squote; int /*<<< orphan*/  op_Tj; int /*<<< orphan*/  op_TJ; int /*<<< orphan*/  op_Tstar; int /*<<< orphan*/  op_Tm; int /*<<< orphan*/  op_TD; int /*<<< orphan*/  op_Td; int /*<<< orphan*/  op_Ts; int /*<<< orphan*/  op_Tr; int /*<<< orphan*/  op_Tf; int /*<<< orphan*/  op_TL; int /*<<< orphan*/  op_Tz; int /*<<< orphan*/  op_Tw; int /*<<< orphan*/  op_Tc; int /*<<< orphan*/  op_ET; int /*<<< orphan*/  op_BT; int /*<<< orphan*/  op_Wstar; int /*<<< orphan*/  op_W; int /*<<< orphan*/  op_n; int /*<<< orphan*/  op_bstar; int /*<<< orphan*/  op_b; int /*<<< orphan*/  op_Bstar; int /*<<< orphan*/  op_B; int /*<<< orphan*/  op_fstar; int /*<<< orphan*/  op_f; int /*<<< orphan*/  op_F; int /*<<< orphan*/  op_s; int /*<<< orphan*/  op_S; int /*<<< orphan*/  op_re; int /*<<< orphan*/  op_h; int /*<<< orphan*/  op_y; int /*<<< orphan*/  op_v; int /*<<< orphan*/  op_c; int /*<<< orphan*/  op_l; int /*<<< orphan*/  op_m; int /*<<< orphan*/  op_cm; int /*<<< orphan*/  op_Q; int /*<<< orphan*/  op_q; int /*<<< orphan*/ * op_gs_SMask; int /*<<< orphan*/ * op_gs_ca; int /*<<< orphan*/ * op_gs_CA; int /*<<< orphan*/ * op_gs_BM; int /*<<< orphan*/  op_gs_end; int /*<<< orphan*/  op_gs_begin; int /*<<< orphan*/  op_i; int /*<<< orphan*/  op_ri; int /*<<< orphan*/  op_d; int /*<<< orphan*/  op_M; int /*<<< orphan*/  op_J; int /*<<< orphan*/  op_j; int /*<<< orphan*/  op_w; int /*<<< orphan*/  drop_processor; int /*<<< orphan*/  close_processor; } ;
struct TYPE_5__ {int ahxencode; int /*<<< orphan*/ * out; TYPE_1__ super; } ;
typedef  TYPE_2__ pdf_output_processor ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_close_output_processor ; 
 int /*<<< orphan*/  pdf_drop_output_processor ; 
 TYPE_2__* pdf_new_processor (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pdf_out_B ; 
 int /*<<< orphan*/  pdf_out_BDC ; 
 int /*<<< orphan*/  pdf_out_BI ; 
 int /*<<< orphan*/  pdf_out_BMC ; 
 int /*<<< orphan*/  pdf_out_BT ; 
 int /*<<< orphan*/  pdf_out_BX ; 
 int /*<<< orphan*/  pdf_out_Bstar ; 
 int /*<<< orphan*/  pdf_out_CS ; 
 int /*<<< orphan*/  pdf_out_DP ; 
 int /*<<< orphan*/  pdf_out_Do_form ; 
 int /*<<< orphan*/  pdf_out_Do_image ; 
 int /*<<< orphan*/  pdf_out_EMC ; 
 int /*<<< orphan*/  pdf_out_ET ; 
 int /*<<< orphan*/  pdf_out_EX ; 
 int /*<<< orphan*/  pdf_out_F ; 
 int /*<<< orphan*/  pdf_out_G ; 
 int /*<<< orphan*/  pdf_out_J ; 
 int /*<<< orphan*/  pdf_out_K ; 
 int /*<<< orphan*/  pdf_out_M ; 
 int /*<<< orphan*/  pdf_out_MP ; 
 int /*<<< orphan*/  pdf_out_Q ; 
 int /*<<< orphan*/  pdf_out_RG ; 
 int /*<<< orphan*/  pdf_out_S ; 
 int /*<<< orphan*/  pdf_out_SC_color ; 
 int /*<<< orphan*/  pdf_out_SC_pattern ; 
 int /*<<< orphan*/  pdf_out_SC_shade ; 
 int /*<<< orphan*/  pdf_out_TD ; 
 int /*<<< orphan*/  pdf_out_TJ ; 
 int /*<<< orphan*/  pdf_out_TL ; 
 int /*<<< orphan*/  pdf_out_Tc ; 
 int /*<<< orphan*/  pdf_out_Td ; 
 int /*<<< orphan*/  pdf_out_Tf ; 
 int /*<<< orphan*/  pdf_out_Tj ; 
 int /*<<< orphan*/  pdf_out_Tm ; 
 int /*<<< orphan*/  pdf_out_Tr ; 
 int /*<<< orphan*/  pdf_out_Ts ; 
 int /*<<< orphan*/  pdf_out_Tstar ; 
 int /*<<< orphan*/  pdf_out_Tw ; 
 int /*<<< orphan*/  pdf_out_Tz ; 
 int /*<<< orphan*/  pdf_out_W ; 
 int /*<<< orphan*/  pdf_out_Wstar ; 
 int /*<<< orphan*/  pdf_out_b ; 
 int /*<<< orphan*/  pdf_out_bstar ; 
 int /*<<< orphan*/  pdf_out_c ; 
 int /*<<< orphan*/  pdf_out_cm ; 
 int /*<<< orphan*/  pdf_out_cs ; 
 int /*<<< orphan*/  pdf_out_d ; 
 int /*<<< orphan*/  pdf_out_d0 ; 
 int /*<<< orphan*/  pdf_out_d1 ; 
 int /*<<< orphan*/  pdf_out_dquote ; 
 int /*<<< orphan*/  pdf_out_f ; 
 int /*<<< orphan*/  pdf_out_fstar ; 
 int /*<<< orphan*/  pdf_out_g ; 
 int /*<<< orphan*/  pdf_out_gs_OP ; 
 int /*<<< orphan*/  pdf_out_gs_OPM ; 
 int /*<<< orphan*/  pdf_out_gs_UseBlackPtComp ; 
 int /*<<< orphan*/  pdf_out_gs_begin ; 
 int /*<<< orphan*/  pdf_out_gs_end ; 
 int /*<<< orphan*/  pdf_out_gs_op ; 
 int /*<<< orphan*/  pdf_out_h ; 
 int /*<<< orphan*/  pdf_out_i ; 
 int /*<<< orphan*/  pdf_out_j ; 
 int /*<<< orphan*/  pdf_out_k ; 
 int /*<<< orphan*/  pdf_out_l ; 
 int /*<<< orphan*/  pdf_out_m ; 
 int /*<<< orphan*/  pdf_out_n ; 
 int /*<<< orphan*/  pdf_out_q ; 
 int /*<<< orphan*/  pdf_out_re ; 
 int /*<<< orphan*/  pdf_out_rg ; 
 int /*<<< orphan*/  pdf_out_ri ; 
 int /*<<< orphan*/  pdf_out_s ; 
 int /*<<< orphan*/  pdf_out_sc_color ; 
 int /*<<< orphan*/  pdf_out_sc_pattern ; 
 int /*<<< orphan*/  pdf_out_sc_shade ; 
 int /*<<< orphan*/  pdf_out_sh ; 
 int /*<<< orphan*/  pdf_out_squote ; 
 int /*<<< orphan*/  pdf_out_v ; 
 int /*<<< orphan*/  pdf_out_w ; 
 int /*<<< orphan*/  pdf_out_y ; 

pdf_processor *
pdf_new_output_processor(fz_context *ctx, fz_output *out, int ahxencode)
{
	pdf_output_processor *proc = pdf_new_processor(ctx, sizeof *proc);
	{
		proc->super.close_processor = pdf_close_output_processor;
		proc->super.drop_processor = pdf_drop_output_processor;

		/* general graphics state */
		proc->super.op_w = pdf_out_w;
		proc->super.op_j = pdf_out_j;
		proc->super.op_J = pdf_out_J;
		proc->super.op_M = pdf_out_M;
		proc->super.op_d = pdf_out_d;
		proc->super.op_ri = pdf_out_ri;
		proc->super.op_i = pdf_out_i;
		proc->super.op_gs_begin = pdf_out_gs_begin;
		proc->super.op_gs_end = pdf_out_gs_end;

		/* transparency graphics state */
		proc->super.op_gs_BM = NULL;
		proc->super.op_gs_CA = NULL;
		proc->super.op_gs_ca = NULL;
		proc->super.op_gs_SMask = NULL;

		/* special graphics state */
		proc->super.op_q = pdf_out_q;
		proc->super.op_Q = pdf_out_Q;
		proc->super.op_cm = pdf_out_cm;

		/* path construction */
		proc->super.op_m = pdf_out_m;
		proc->super.op_l = pdf_out_l;
		proc->super.op_c = pdf_out_c;
		proc->super.op_v = pdf_out_v;
		proc->super.op_y = pdf_out_y;
		proc->super.op_h = pdf_out_h;
		proc->super.op_re = pdf_out_re;

		/* path painting */
		proc->super.op_S = pdf_out_S;
		proc->super.op_s = pdf_out_s;
		proc->super.op_F = pdf_out_F;
		proc->super.op_f = pdf_out_f;
		proc->super.op_fstar = pdf_out_fstar;
		proc->super.op_B = pdf_out_B;
		proc->super.op_Bstar = pdf_out_Bstar;
		proc->super.op_b = pdf_out_b;
		proc->super.op_bstar = pdf_out_bstar;
		proc->super.op_n = pdf_out_n;

		/* clipping paths */
		proc->super.op_W = pdf_out_W;
		proc->super.op_Wstar = pdf_out_Wstar;

		/* text objects */
		proc->super.op_BT = pdf_out_BT;
		proc->super.op_ET = pdf_out_ET;

		/* text state */
		proc->super.op_Tc = pdf_out_Tc;
		proc->super.op_Tw = pdf_out_Tw;
		proc->super.op_Tz = pdf_out_Tz;
		proc->super.op_TL = pdf_out_TL;
		proc->super.op_Tf = pdf_out_Tf;
		proc->super.op_Tr = pdf_out_Tr;
		proc->super.op_Ts = pdf_out_Ts;

		/* text positioning */
		proc->super.op_Td = pdf_out_Td;
		proc->super.op_TD = pdf_out_TD;
		proc->super.op_Tm = pdf_out_Tm;
		proc->super.op_Tstar = pdf_out_Tstar;

		/* text showing */
		proc->super.op_TJ = pdf_out_TJ;
		proc->super.op_Tj = pdf_out_Tj;
		proc->super.op_squote = pdf_out_squote;
		proc->super.op_dquote = pdf_out_dquote;

		/* type 3 fonts */
		proc->super.op_d0 = pdf_out_d0;
		proc->super.op_d1 = pdf_out_d1;

		/* color */
		proc->super.op_CS = pdf_out_CS;
		proc->super.op_cs = pdf_out_cs;
		proc->super.op_SC_color = pdf_out_SC_color;
		proc->super.op_sc_color = pdf_out_sc_color;
		proc->super.op_SC_pattern = pdf_out_SC_pattern;
		proc->super.op_sc_pattern = pdf_out_sc_pattern;
		proc->super.op_SC_shade = pdf_out_SC_shade;
		proc->super.op_sc_shade = pdf_out_sc_shade;

		proc->super.op_G = pdf_out_G;
		proc->super.op_g = pdf_out_g;
		proc->super.op_RG = pdf_out_RG;
		proc->super.op_rg = pdf_out_rg;
		proc->super.op_K = pdf_out_K;
		proc->super.op_k = pdf_out_k;

		/* shadings, images, xobjects */
		proc->super.op_BI = pdf_out_BI;
		proc->super.op_sh = pdf_out_sh;
		proc->super.op_Do_image = pdf_out_Do_image;
		proc->super.op_Do_form = pdf_out_Do_form;

		/* marked content */
		proc->super.op_MP = pdf_out_MP;
		proc->super.op_DP = pdf_out_DP;
		proc->super.op_BMC = pdf_out_BMC;
		proc->super.op_BDC = pdf_out_BDC;
		proc->super.op_EMC = pdf_out_EMC;

		/* compatibility */
		proc->super.op_BX = pdf_out_BX;
		proc->super.op_EX = pdf_out_EX;

		/* extgstate */
		proc->super.op_gs_OP = pdf_out_gs_OP;
		proc->super.op_gs_op = pdf_out_gs_op;
		proc->super.op_gs_OPM = pdf_out_gs_OPM;
		proc->super.op_gs_UseBlackPtComp = pdf_out_gs_UseBlackPtComp;
	}

	proc->out = out;
	proc->ahxencode = ahxencode;

	return (pdf_processor*)proc;
}