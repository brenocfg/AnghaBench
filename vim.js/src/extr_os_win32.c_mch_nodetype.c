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
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 int FILE_TYPE_CHAR ; 
 int FILE_TYPE_DISK ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ GetACP () ; 
 int GetFileType (scalar_t__) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int NODE_NORMAL ; 
 int NODE_OTHER ; 
 int NODE_WRITABLE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ STRNCMP (int /*<<< orphan*/ *,char*,int) ; 
 int enc_codepage ; 
 int /*<<< orphan*/ * enc_to_utf16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

int
mch_nodetype(char_u *name)
{
    HANDLE	hFile;
    int		type;
#ifdef FEAT_MBYTE
    WCHAR	*wn = NULL;
#endif

    /* We can't open a file with a name "\\.\con" or "\\.\prn" and trying to
     * read from it later will cause Vim to hang.  Thus return NODE_WRITABLE
     * here. */
    if (STRNCMP(name, "\\\\.\\", 4) == 0)
	return NODE_WRITABLE;

#ifdef FEAT_MBYTE
    if (enc_codepage >= 0 && (int)GetACP() != enc_codepage)
    {
	wn = enc_to_utf16(name, NULL);
	if (wn != NULL)
	{
	    hFile = CreateFileW(wn,	/* file name */
			GENERIC_WRITE,	/* access mode */
			0,		/* share mode */
			NULL,		/* security descriptor */
			OPEN_EXISTING,	/* creation disposition */
			0,		/* file attributes */
			NULL);		/* handle to template file */
	    if (hFile == INVALID_HANDLE_VALUE
			      && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
	    {
		/* Retry with non-wide function (for Windows 98). */
		vim_free(wn);
		wn = NULL;
	    }
	}
    }
    if (wn == NULL)
#endif
	hFile = CreateFile(name,	/* file name */
		    GENERIC_WRITE,	/* access mode */
		    0,			/* share mode */
		    NULL,		/* security descriptor */
		    OPEN_EXISTING,	/* creation disposition */
		    0,			/* file attributes */
		    NULL);		/* handle to template file */

#ifdef FEAT_MBYTE
    vim_free(wn);
#endif
    if (hFile == INVALID_HANDLE_VALUE)
	return NODE_NORMAL;

    type = GetFileType(hFile);
    CloseHandle(hFile);
    if (type == FILE_TYPE_CHAR)
	return NODE_WRITABLE;
    if (type == FILE_TYPE_DISK)
	return NODE_NORMAL;
    return NODE_OTHER;
}