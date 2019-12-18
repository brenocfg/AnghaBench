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
 int AM_LFN ; 
 size_t LDIR_Attr ; 
 size_t LDIR_Chksum ; 
 int LDIR_FstClusLO ; 
 size_t LDIR_Ord ; 
 size_t LDIR_Type ; 
 int LLEF ; 
 int* LfnOfs ; 
 int /*<<< orphan*/  ST_WORD (int*,int) ; 

__attribute__((used)) static
void fit_lfn (
	const WCHAR* lfnbuf,	/* Pointer to the LFN working buffer */
	BYTE* dir,				/* Pointer to the LFN entry to be processed */
	BYTE ord,				/* LFN order (1-20) */
	BYTE sum				/* Checksum of the corresponding SFN */
)
{
	UINT i, s;
	WCHAR wc;


	dir[LDIR_Chksum] = sum;			/* Set checksum */
	dir[LDIR_Attr] = AM_LFN;		/* Set attribute. LFN entry */
	dir[LDIR_Type] = 0;
	ST_WORD(dir + LDIR_FstClusLO, 0);

	i = (ord - 1) * 13;				/* Get offset in the LFN working buffer */
	s = wc = 0;
	do {
		if (wc != 0xFFFF) wc = lfnbuf[i++];	/* Get an effective character */
		ST_WORD(dir+LfnOfs[s], wc);	/* Put it */
		if (!wc) wc = 0xFFFF;		/* Padding characters following last character */
	} while (++s < 13);
	if (wc == 0xFFFF || !lfnbuf[i]) ord |= LLEF;	/* Bottom LFN part is the start of LFN sequence */
	dir[LDIR_Ord] = ord;			/* Set the LFN order */
}