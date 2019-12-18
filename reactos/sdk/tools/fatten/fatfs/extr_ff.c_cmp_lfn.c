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
typedef  int WCHAR ;
typedef  int UINT ;
typedef  int BYTE ;

/* Variables and functions */
 int LDIR_FstClusLO ; 
 size_t LDIR_Ord ; 
 int LD_WORD (int*) ; 
 int LLEF ; 
 int* LfnOfs ; 
 int _MAX_LFN ; 
 scalar_t__ ff_wtoupper (int) ; 

__attribute__((used)) static
int cmp_lfn (			/* 1:matched, 0:not matched */
	WCHAR* lfnbuf,		/* Pointer to the LFN working buffer to be compared */
	BYTE* dir			/* Pointer to the directory entry containing the part of LFN */
)
{
	UINT i, s;
	WCHAR wc, uc;


	if (LD_WORD(dir + LDIR_FstClusLO) != 0) return 0;	/* Check LDIR_FstClusLO */

	i = ((dir[LDIR_Ord] & 0x3F) - 1) * 13;	/* Offset in the LFN buffer */

	for (wc = 1, s = 0; s < 13; s++) {		/* Process all characters in the entry */
		uc = LD_WORD(dir + LfnOfs[s]);		/* Pick an LFN character */
		if (wc) {
			if (i >= _MAX_LFN || ff_wtoupper(uc) != ff_wtoupper(lfnbuf[i++]))	/* Compare it */
				return 0;					/* Not matched */
			wc = uc;
		} else {
			if (uc != 0xFFFF) return 0;		/* Check filler */
		}
	}

	if ((dir[LDIR_Ord] & LLEF) && wc && lfnbuf[i])	/* Last segment matched but different length */
		return 0;

	return 1;		/* The part of LFN matched */
}