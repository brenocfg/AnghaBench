#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char char_u ;
struct TYPE_4__ {char* cFileName; char* cAlternateFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATA ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  FindClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FindFirstFile (char*,TYPE_1__*) ; 
 scalar_t__ FindNextFile (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ GetACP () ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 char NUL ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  STRCPY (char*,char*) ; 
 scalar_t__ STRLEN (char*) ; 
 int _MAX_PATH ; 
 scalar_t__ _stricoll (char*,char*) ; 
 int enc_codepage ; 
 scalar_t__ enc_dbcs ; 
 char* enc_to_utf16 (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ fname_casew (char*,int) ; 
 scalar_t__ isalpha (char) ; 
 int mb_ptr2len (char*) ; 
 char psepc ; 
 int /*<<< orphan*/  slash_adjust (char*) ; 
 scalar_t__ strcoll (char*,char*) ; 
 int strlen (char*) ; 
 int stub1 (char*) ; 
 char* utf16_to_enc (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_free (char*) ; 
 int /*<<< orphan*/  vim_strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  wcscpy (char*,char*) ; 

void
fname_case(
    char_u	*name,
    int		len)
{
    char		szTrueName[_MAX_PATH + 2];
    char		szTrueNameTemp[_MAX_PATH + 2];
    char		*ptrue, *ptruePrev;
    char		*porig, *porigPrev;
    int			flen;
    WIN32_FIND_DATA	fb;
    HANDLE		hFind;
    int			c;
    int			slen;

    flen = (int)STRLEN(name);
    if (flen == 0)
	return;

    slash_adjust(name);

#ifdef FEAT_MBYTE
    if (enc_codepage >= 0 && (int)GetACP() != enc_codepage)
    {
	WCHAR	*p = enc_to_utf16(name, NULL);

	if (p != NULL)
	{
	    char_u	*q;
	    WCHAR	buf[_MAX_PATH + 2];

	    wcscpy(buf, p);
	    vim_free(p);

	    if (fname_casew(buf, (len > 0) ? _MAX_PATH : 0) == OK)
	    {
		q = utf16_to_enc(buf, NULL);
		if (q != NULL)
		{
		    vim_strncpy(name, q, (len > 0) ? len - 1 : flen);
		    vim_free(q);
		    return;
		}
	    }
	}
	/* Retry with non-wide function (for Windows 98). */
    }
#endif

    /* If 'enc' is utf-8, flen can be larger than _MAX_PATH.
     * So we should check this after calling wide function. */
    if (flen > _MAX_PATH)
	return;

    /* Build the new name in szTrueName[] one component at a time. */
    porig = name;
    ptrue = szTrueName;

    if (isalpha(porig[0]) && porig[1] == ':')
    {
	/* copy leading drive letter */
	*ptrue++ = *porig++;
	*ptrue++ = *porig++;
	*ptrue = NUL;	    /* in case nothing follows */
    }

    while (*porig != NUL)
    {
	/* copy \ characters */
	while (*porig == psepc)
	    *ptrue++ = *porig++;

	ptruePrev = ptrue;
	porigPrev = porig;
	while (*porig != NUL && *porig != psepc)
	{
#ifdef FEAT_MBYTE
	    int l;

	    if (enc_dbcs)
	    {
		l = (*mb_ptr2len)(porig);
		while (--l >= 0)
		    *ptrue++ = *porig++;
	    }
	    else
#endif
		*ptrue++ = *porig++;
	}
	*ptrue = NUL;

	/* To avoid a slow failure append "\*" when searching a directory,
	 * server or network share. */
	STRCPY(szTrueNameTemp, szTrueName);
	slen = (int)strlen(szTrueNameTemp);
	if (*porig == psepc && slen + 2 < _MAX_PATH)
	    STRCPY(szTrueNameTemp + slen, "\\*");

	/* Skip "", "." and "..". */
	if (ptrue > ptruePrev
		&& (ptruePrev[0] != '.'
		    || (ptruePrev[1] != NUL
			&& (ptruePrev[1] != '.' || ptruePrev[2] != NUL)))
		&& (hFind = FindFirstFile(szTrueNameTemp, &fb))
						      != INVALID_HANDLE_VALUE)
	{
	    c = *porig;
	    *porig = NUL;

	    /* Only use the match when it's the same name (ignoring case) or
	     * expansion is allowed and there is a match with the short name
	     * and there is enough room. */
	    if (_stricoll(porigPrev, fb.cFileName) == 0
		    || (len > 0
			&& (_stricoll(porigPrev, fb.cAlternateFileName) == 0
			    && (int)(ptruePrev - szTrueName)
					   + (int)strlen(fb.cFileName) < len)))
	    {
		STRCPY(ptruePrev, fb.cFileName);

		/* Look for exact match and prefer it if found.  Must be a
		 * long name, otherwise there would be only one match. */
		while (FindNextFile(hFind, &fb))
		{
		    if (*fb.cAlternateFileName != NUL
			    && (strcoll(porigPrev, fb.cFileName) == 0
				|| (len > 0
				    && (_stricoll(porigPrev,
						   fb.cAlternateFileName) == 0
				    && (int)(ptruePrev - szTrueName)
					 + (int)strlen(fb.cFileName) < len))))
		    {
			STRCPY(ptruePrev, fb.cFileName);
			break;
		    }
		}
	    }
	    FindClose(hFind);
	    *porig = c;
	    ptrue = ptruePrev + strlen(ptruePrev);
	}
    }

    STRCPY(name, szTrueName);
}