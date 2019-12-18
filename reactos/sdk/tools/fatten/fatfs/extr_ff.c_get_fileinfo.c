#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int WCHAR ;
typedef  int UINT ;
struct TYPE_6__ {char* dir; int lfn_idx; int* lfn; scalar_t__ sect; } ;
struct TYPE_5__ {char* fname; char fattrib; char* lfname; int lfsize; void* ftime; void* fdate; int /*<<< orphan*/  fsize; } ;
typedef  char TCHAR ;
typedef  TYPE_1__ FILINFO ;
typedef  TYPE_2__ DIR ;
typedef  char BYTE ;

/* Variables and functions */
 scalar_t__ DDEM ; 
 size_t DIR_Attr ; 
 int DIR_FileSize ; 
 size_t DIR_NTres ; 
 int DIR_WrtDate ; 
 int DIR_WrtTime ; 
 scalar_t__ IsDBCS1 (char) ; 
 scalar_t__ IsDBCS2 (char) ; 
 scalar_t__ IsUpper (char) ; 
 int /*<<< orphan*/  LD_DWORD (char*) ; 
 void* LD_WORD (char*) ; 
 char NS_BODY ; 
 char NS_EXT ; 
 char RDDEM ; 
 scalar_t__ _DF1S ; 
 void* ff_convert (int,int) ; 

__attribute__((used)) static
void get_fileinfo (		/* No return code */
	DIR* dp,			/* Pointer to the directory object */
	FILINFO* fno	 	/* Pointer to the file information to be filled */
)
{
	UINT i;
	TCHAR *p, c;
	BYTE *dir;
#if _USE_LFN
	WCHAR w, *lfn;
#endif

	p = fno->fname;
	if (dp->sect) {		/* Get SFN */
		dir = dp->dir;
		i = 0;
		while (i < 11) {		/* Copy name body and extension */
			c = (TCHAR)dir[i++];
			if (c == ' ') continue;				/* Skip padding spaces */
			if (c == RDDEM) c = (TCHAR)DDEM;	/* Restore replaced DDEM character */
			if (i == 9) *p++ = '.';				/* Insert a . if extension is exist */
#if _USE_LFN
			if (IsUpper(c) && (dir[DIR_NTres] & (i >= 9 ? NS_EXT : NS_BODY)))
				c += 0x20;			/* To lower */
#if _LFN_UNICODE
			if (IsDBCS1(c) && i != 8 && i != 11 && IsDBCS2(dir[i]))
				c = c << 8 | dir[i++];
			c = ff_convert(c, 1);	/* OEM -> Unicode */
			if (!c) c = '?';
#endif
#endif
			*p++ = c;
		}
		fno->fattrib = dir[DIR_Attr];				/* Attribute */
		fno->fsize = LD_DWORD(dir + DIR_FileSize);	/* Size */
		fno->fdate = LD_WORD(dir + DIR_WrtDate);	/* Date */
		fno->ftime = LD_WORD(dir + DIR_WrtTime);	/* Time */
	}
	*p = 0;		/* Terminate SFN string by a \0 */

#if _USE_LFN
	if (fno->lfname) {
		i = 0; p = fno->lfname;
		if (dp->sect && fno->lfsize && dp->lfn_idx != 0xFFFF) {	/* Get LFN if available */
			lfn = dp->lfn;
			while ((w = *lfn++) != 0) {		/* Get an LFN character */
#if !_LFN_UNICODE
				w = ff_convert(w, 0);		/* Unicode -> OEM */
				if (!w) { i = 0; break; }	/* No LFN if it could not be converted */
				if (_DF1S && w >= 0x100)	/* Put 1st byte if it is a DBC (always false on SBCS cfg) */
					p[i++] = (TCHAR)(w >> 8);
#endif
				if (i >= fno->lfsize - 1) { i = 0; break; }	/* No LFN if buffer overflow */
				p[i++] = (TCHAR)w;
			}
		}
		p[i] = 0;	/* Terminate LFN string by a \0 */
	}
#endif
}