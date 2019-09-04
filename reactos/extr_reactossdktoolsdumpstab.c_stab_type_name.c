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

/* Variables and functions */
#define  N_BCOMM 160 
#define  N_BINCL 159 
#define  N_BSLINE 158 
#define  N_CATCH 157 
#define  N_DEFD 156 
#define  N_DSLINE 155 
#define  N_ECOML 154 
#define  N_ECOMM 153 
#define  N_EHDECL 152 
#define  N_EINCL 151 
#define  N_ENTRY 150 
#define  N_EXCL 149 
#define  N_FNAME 148 
#define  N_FUN 147 
#define  N_GYSM 146 
#define  N_LBRAC 145 
#define  N_LCSYM 144 
#define  N_LENG 143 
#define  N_LSYM 142 
#define  N_M2C 141 
#define  N_MAIN 140 
#define  N_NOMAP 139 
#define  N_NSYMS 138 
#define  N_PC 137 
#define  N_PSYM 136 
#define  N_RBRAC 135 
#define  N_RSYM 134 
#define  N_SCOPE 133 
#define  N_SLINE 132 
#define  N_SO 131 
#define  N_SOL 130 
#define  N_SSYM 129 
#define  N_STSYM 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char*
stab_type_name ( int stab_type )
{
	static char buf[32];
	switch ( stab_type )
	{
#define X(n) case n: return #n;
		X(N_GYSM)
		X(N_FNAME)
		X(N_FUN)
		X(N_STSYM)
		X(N_LCSYM)
		X(N_MAIN)
		X(N_PC)
		X(N_NSYMS)
		X(N_NOMAP)
		X(N_RSYM)
		X(N_M2C)
		X(N_SLINE)
		X(N_DSLINE)
		X(N_BSLINE)
		//X(N_BROWS)
		X(N_DEFD)
		X(N_EHDECL)
		//X(N_MOD2)
		X(N_CATCH)
		X(N_SSYM)
		X(N_SO)
		X(N_LSYM)
		X(N_BINCL)
		X(N_SOL)
		X(N_PSYM)
		X(N_EINCL)
		X(N_ENTRY)
		X(N_LBRAC)
		X(N_EXCL)
		X(N_SCOPE)
		X(N_RBRAC)
		X(N_BCOMM)
		X(N_ECOMM)
		X(N_ECOML)
		X(N_LENG)
	}
	sprintf ( buf, "%lu", stab_type );
	return buf;
}