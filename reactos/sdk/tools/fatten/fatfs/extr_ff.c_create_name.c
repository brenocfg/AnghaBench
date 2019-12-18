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
typedef  char WCHAR ;
typedef  size_t UINT ;
struct TYPE_3__ {char* lfn; char* fn; } ;
typedef  char TCHAR ;
typedef  int /*<<< orphan*/  FRESULT ;
typedef  TYPE_1__ DIR ;
typedef  char BYTE ;

/* Variables and functions */
 char DDEM ; 
 char* ExCvt ; 
 int /*<<< orphan*/  FR_INVALID_NAME ; 
 int /*<<< orphan*/  FR_OK ; 
 scalar_t__ IsDBCS1 (char) ; 
 int /*<<< orphan*/  IsDBCS2 (char) ; 
 scalar_t__ IsLower (char) ; 
 scalar_t__ IsUpper (char) ; 
 size_t NSFLAG ; 
 char NS_BODY ; 
 char NS_DOT ; 
 char NS_EXT ; 
 char NS_LAST ; 
 char NS_LFN ; 
 char NS_LOSS ; 
 void* RDDEM ; 
 scalar_t__ _DF1S ; 
 size_t _MAX_LFN ; 
 scalar_t__ chk_chr (char*,char) ; 
 char ff_convert (char,int) ; 
 char ff_wtoupper (char) ; 
 int /*<<< orphan*/  mem_set (char*,char,int) ; 

__attribute__((used)) static
FRESULT create_name (	/* FR_OK: successful, FR_INVALID_NAME: could not create */
	DIR* dp,			/* Pointer to the directory object */
	const TCHAR** path	/* Pointer to pointer to the segment in the path string */
)
{
#if _USE_LFN	/* LFN configuration */
	BYTE b, cf;
	WCHAR w, *lfn;
	UINT i, ni, si, di;
	const TCHAR *p;

	/* Create LFN in Unicode */
	for (p = *path; *p == '/' || *p == '\\'; p++) ;	/* Strip duplicated separator */
	lfn = dp->lfn;
	si = di = 0;
	for (;;) {
		w = p[si++];					/* Get a character */
		if (w < ' ' || w == '/' || w == '\\') break;	/* Break on end of segment */
		if (di >= _MAX_LFN)				/* Reject too long name */
			return FR_INVALID_NAME;
#if !_LFN_UNICODE
		w &= 0xFF;
		if (IsDBCS1(w)) {				/* Check if it is a DBC 1st byte (always false on SBCS cfg) */
			b = (BYTE)p[si++];			/* Get 2nd byte */
			w = (w << 8) + b;			/* Create a DBC */
			if (!IsDBCS2(b))
				return FR_INVALID_NAME;	/* Reject invalid sequence */
		}
		w = ff_convert(w, 1);			/* Convert ANSI/OEM to Unicode */
		if (!w) return FR_INVALID_NAME;	/* Reject invalid code */
#endif
		if (w < 0x80 && chk_chr("\"*:<>\?|\x7F", w)) /* Reject illegal characters for LFN */
			return FR_INVALID_NAME;
		lfn[di++] = w;					/* Store the Unicode character */
	}
	*path = &p[si];						/* Return pointer to the next segment */
	cf = (w < ' ') ? NS_LAST : 0;		/* Set last segment flag if end of path */
#if _FS_RPATH
	if ((di == 1 && lfn[di - 1] == '.') ||
		(di == 2 && lfn[di - 1] == '.' && lfn[di - 2] == '.')) {	/* Is this segment a dot entry? */
		lfn[di] = 0;
		for (i = 0; i < 11; i++)		/* Create dot name for SFN entry */
			dp->fn[i] = (i < di) ? '.' : ' ';
		dp->fn[i] = cf | NS_DOT;		/* This is a dot entry */
		return FR_OK;
	}
#endif
	while (di) {						/* Snip off trailing spaces and dots if exist */
		w = lfn[di - 1];
		if (w != ' ' && w != '.') break;
		di--;
	}
	if (!di) return FR_INVALID_NAME;	/* Reject nul string */
	lfn[di] = 0;						/* LFN is created */

	/* Create SFN in directory form */
	mem_set(dp->fn, ' ', 11);
	for (si = 0; lfn[si] == ' ' || lfn[si] == '.'; si++) ;	/* Strip leading spaces and dots */
	if (si) cf |= NS_LOSS | NS_LFN;
	while (di && lfn[di - 1] != '.') di--;	/* Find extension (di<=si: no extension) */

	b = i = 0; ni = 8;
	for (;;) {
		w = lfn[si++];					/* Get an LFN character */
		if (!w) break;					/* Break on end of the LFN */
		if (w == ' ' || (w == '.' && si != di)) {	/* Remove spaces and dots */
			cf |= NS_LOSS | NS_LFN; continue;
		}

		if (i >= ni || si == di) {		/* Extension or end of SFN */
			if (ni == 11) {				/* Long extension */
				cf |= NS_LOSS | NS_LFN; break;
			}
			if (si != di) cf |= NS_LOSS | NS_LFN;	/* Out of 8.3 format */
			if (si > di) break;			/* No extension */
			si = di; i = 8; ni = 11;	/* Enter extension section */
			b <<= 2; continue;
		}

		if (w >= 0x80) {				/* Non ASCII character */
#ifdef _EXCVT
			w = ff_convert(w, 0);		/* Unicode -> OEM code */
			if (w) w = ExCvt[w - 0x80];	/* Convert extended character to upper (SBCS) */
#else
			w = ff_convert(ff_wtoupper(w), 0);	/* Upper converted Unicode -> OEM code */
#endif
			cf |= NS_LFN;				/* Force create LFN entry */
		}

		if (_DF1S && w >= 0x100) {		/* Is this DBC? (always false at SBCS cfg) */
			if (i >= ni - 1) {
				cf |= NS_LOSS | NS_LFN; i = ni; continue;
			}
			dp->fn[i++] = (BYTE)(w >> 8);
		} else {						/* SBC */
			if (!w || chk_chr("+,;=[]", w)) {	/* Replace illegal characters for SFN */
				w = '_'; cf |= NS_LOSS | NS_LFN;/* Lossy conversion */
			} else {
				if (IsUpper(w)) {		/* ASCII large capital */
					b |= 2;
				} else {
					if (IsLower(w)) {	/* ASCII small capital */
						b |= 1; w -= 0x20;
					}
				}
			}
		}
		dp->fn[i++] = (BYTE)w;
	}

	if (dp->fn[0] == DDEM) dp->fn[0] = RDDEM;	/* If the first character collides with DDEM, replace it with RDDEM */

	if (ni == 8) b <<= 2;
	if ((b & 0x0C) == 0x0C || (b & 0x03) == 0x03)	/* Create LFN entry when there are composite capitals */
		cf |= NS_LFN;
	if (!(cf & NS_LFN)) {						/* When LFN is in 8.3 format without extended character, NT flags are created */
		if ((b & 0x03) == 0x01) cf |= NS_EXT;	/* NT flag (Extension has only small capital) */
		if ((b & 0x0C) == 0x04) cf |= NS_BODY;	/* NT flag (Filename has only small capital) */
	}

	dp->fn[NSFLAG] = cf;	/* SFN is created */

	return FR_OK;


#else	/* Non-LFN configuration */
	BYTE b, c, d, *sfn;
	UINT ni, si, i;
	const char *p;

	/* Create file name in directory form */
	for (p = *path; *p == '/' || *p == '\\'; p++) ;	/* Skip duplicated separator */
	sfn = dp->fn;
	mem_set(sfn, ' ', 11);
	si = i = b = 0; ni = 8;
#if _FS_RPATH
	if (p[si] == '.') { /* Is this a dot entry? */
		for (;;) {
			c = (BYTE)p[si++];
			if (c != '.' || si >= 3) break;
			sfn[i++] = c;
		}
		if (c != '/' && c != '\\' && c > ' ') return FR_INVALID_NAME;
		*path = &p[si];									/* Return pointer to the next segment */
		sfn[NSFLAG] = (c <= ' ') ? NS_LAST | NS_DOT : NS_DOT;	/* Set last segment flag if end of path */
		return FR_OK;
	}
#endif
	for (;;) {
		c = (BYTE)p[si++];
		if (c <= ' ' || c == '/' || c == '\\') break;	/* Break on end of segment */
		if (c == '.' || i >= ni) {
			if (ni != 8 || c != '.') return FR_INVALID_NAME;
			i = 8; ni = 11;
			b <<= 2; continue;
		}
		if (c >= 0x80) {				/* Extended character? */
			b |= 3;						/* Eliminate NT flag */
#ifdef _EXCVT
			c = ExCvt[c - 0x80];		/* To upper extended characters (SBCS cfg) */
#else
#if !_DF1S
			return FR_INVALID_NAME;		/* Reject extended characters (ASCII cfg) */
#endif
#endif
		}
		if (IsDBCS1(c)) {				/* Check if it is a DBC 1st byte (always false at SBCS cfg.) */
			d = (BYTE)p[si++];			/* Get 2nd byte */
			if (!IsDBCS2(d) || i >= ni - 1)	/* Reject invalid DBC */
				return FR_INVALID_NAME;
			sfn[i++] = c;
			sfn[i++] = d;
		} else {						/* SBC */
			if (chk_chr("\"*+,:;<=>\?[]|\x7F", c))	/* Reject illegal chrs for SFN */
				return FR_INVALID_NAME;
			if (IsUpper(c)) {			/* ASCII large capital? */
				b |= 2;
			} else {
				if (IsLower(c)) {		/* ASCII small capital? */
					b |= 1; c -= 0x20;
				}
			}
			sfn[i++] = c;
		}
	}
	*path = &p[si];						/* Return pointer to the next segment */
	c = (c <= ' ') ? NS_LAST : 0;		/* Set last segment flag if end of path */

	if (!i) return FR_INVALID_NAME;		/* Reject nul string */
	if (sfn[0] == DDEM) sfn[0] = RDDEM;	/* When first character collides with DDEM, replace it with RDDEM */

	if (ni == 8) b <<= 2;
	if ((b & 0x03) == 0x01) c |= NS_EXT;	/* NT flag (Name extension has only small capital) */
	if ((b & 0x0C) == 0x04) c |= NS_BODY;	/* NT flag (Name body has only small capital) */

	sfn[NSFLAG] = c;		/* Store NT flag, File name is created */

	return FR_OK;
#endif
}