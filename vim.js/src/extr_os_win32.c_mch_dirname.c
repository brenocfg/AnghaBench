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

/* Variables and functions */
 int FAIL ; 
 scalar_t__ GetACP () ; 
 scalar_t__ GetCurrentDirectory (int,int /*<<< orphan*/ *) ; 
 scalar_t__ GetCurrentDirectoryW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int OK ; 
 int /*<<< orphan*/  _MAX_PATH ; 
 int enc_codepage ; 
 int /*<<< orphan*/ * utf16_to_enc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_strncpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
mch_dirname(
    char_u	*buf,
    int		len)
{
    /*
     * Originally this was:
     *    return (getcwd(buf, len) != NULL ? OK : FAIL);
     * But the Win32s known bug list says that getcwd() doesn't work
     * so use the Win32 system call instead. <Negri>
     */
#ifdef FEAT_MBYTE
    if (enc_codepage >= 0 && (int)GetACP() != enc_codepage)
    {
	WCHAR	wbuf[_MAX_PATH + 1];

	if (GetCurrentDirectoryW(_MAX_PATH, wbuf) != 0)
	{
	    char_u  *p = utf16_to_enc(wbuf, NULL);

	    if (p != NULL)
	    {
		vim_strncpy(buf, p, len - 1);
		vim_free(p);
		return OK;
	    }
	}
	/* Retry with non-wide function (for Windows 98). */
    }
#endif
    return (GetCurrentDirectory(len, buf) != 0 ? OK : FAIL);
}