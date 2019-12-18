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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _fputts (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _tfopen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 

FILE *REGPROC_open_export_file(TCHAR *file_name)
{
//_CRTIMP FILE * __cdecl _wfopen(const wchar_t *, const wchar_t *);

//FILE*	fopen (const char* szFileName, const char* szMode);
//FILE*	_wfopen(const wchar_t *file, const wchar_t *mode);

    FILE *file = _tfopen(file_name, _T("w"));
    if (!file) {
        perror("");
        _tprintf(_T("REGPROC_open_export_file(%s) - Can't open file.\n"), file_name);
        //exit(1);
        return NULL;
    }
    _fputts(_T("REGEDIT4\n"), file);
    return file;
}