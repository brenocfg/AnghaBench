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
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_NEW ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateFile (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFile (char const*) ; 
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ GetACP () ; 
 scalar_t__ GetFullPathName (char const*,int /*<<< orphan*/ ,char*,char**) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetTempFileName (char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MoveFile (char const*,char const*) ; 
 char NUL ; 
 int STRLEN (char*) ; 
 int /*<<< orphan*/  _MAX_PATH ; 
 int enc_codepage ; 
 int /*<<< orphan*/ * enc_to_utf16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ gettail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mch_windows95 () ; 
 int mch_wrename (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rename (char const*,char const*) ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

int
mch_rename(
    const char	*pszOldFile,
    const char	*pszNewFile)
{
    char	szTempFile[_MAX_PATH+1];
    char	szNewPath[_MAX_PATH+1];
    char	*pszFilePart;
    HANDLE	hf;
#ifdef FEAT_MBYTE
    WCHAR	*wold = NULL;
    WCHAR	*wnew = NULL;
    int		retval = -1;

    if (enc_codepage >= 0 && (int)GetACP() != enc_codepage)
    {
	wold = enc_to_utf16((char_u *)pszOldFile, NULL);
	wnew = enc_to_utf16((char_u *)pszNewFile, NULL);
	if (wold != NULL && wnew != NULL)
	    retval = mch_wrename(wold, wnew);
	vim_free(wold);
	vim_free(wnew);
	if (retval == 0 || GetLastError() != ERROR_CALL_NOT_IMPLEMENTED)
	    return retval;
	/* Retry with non-wide function (for Windows 98). */
    }
#endif

    /*
     * No need to play tricks if not running Windows 95, unless the file name
     * contains a "~" as the seventh character.
     */
    if (!mch_windows95())
    {
	pszFilePart = (char *)gettail((char_u *)pszOldFile);
	if (STRLEN(pszFilePart) < 8 || pszFilePart[6] != '~')
	    return rename(pszOldFile, pszNewFile);
    }

    /* Get base path of new file name.  Undocumented feature: If pszNewFile is
     * a directory, no error is returned and pszFilePart will be NULL. */
    if (GetFullPathName(pszNewFile, _MAX_PATH, szNewPath, &pszFilePart) == 0
	    || pszFilePart == NULL)
	return -1;
    *pszFilePart = NUL;

    /* Get (and create) a unique temporary file name in directory of new file */
    if (GetTempFileName(szNewPath, "VIM", 0, szTempFile) == 0)
	return -2;

    /* blow the temp file away */
    if (!DeleteFile(szTempFile))
	return -3;

    /* rename old file to the temp file */
    if (!MoveFile(pszOldFile, szTempFile))
	return -4;

    /* now create an empty file called pszOldFile; this prevents the operating
     * system using pszOldFile as an alias (SFN) if we're renaming within the
     * same directory.  For example, we're editing a file called
     * filename.asc.txt by its SFN, filena~1.txt.  If we rename filena~1.txt
     * to filena~1.txt~ (i.e., we're making a backup while writing it), the
     * SFN for filena~1.txt~ will be filena~1.txt, by default, which will
     * cause all sorts of problems later in buf_write().  So, we create an
     * empty file called filena~1.txt and the system will have to find some
     * other SFN for filena~1.txt~, such as filena~2.txt
     */
    if ((hf = CreateFile(pszOldFile, GENERIC_WRITE, 0, NULL, CREATE_NEW,
		    FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
	return -5;
    if (!CloseHandle(hf))
	return -6;

    /* rename the temp file to the new file */
    if (!MoveFile(szTempFile, pszNewFile))
    {
	/* Renaming failed.  Rename the file back to its old name, so that it
	 * looks like nothing happened. */
	(void)MoveFile(szTempFile, pszOldFile);

	return -7;
    }

    /* Seems to be left around on Novell filesystems */
    DeleteFile(szTempFile);

    /* finally, remove the empty old file */
    if (!DeleteFile(pszOldFile))
	return -8;

    return 0;	/* success */
}