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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 scalar_t__ _TEOF ; 
 scalar_t__ _fputts (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _tfopen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ferror (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL create_output_file(TCHAR* file_name, TCHAR* file_mode, TCHAR* file_data)
{
    BOOL result = FALSE;
    FILE *file = _tfopen(file_name, file_mode);
    if (file != NULL) {
        if (_fputts(file_data, file) != _TEOF) {
            result = TRUE;
        } else {
            _tprintf(_T("ERROR: failed to write data to file \"%s\"\n"), file_name);
            _tprintf(_T("ERROR: ferror returned %d\n"), ferror(file));
        }
        fclose(file);
    } else {
        _tprintf(_T("ERROR: failed to open/create file \"%s\" for output\n"), file_name);
        _tprintf(_T("ERROR: ferror returned %d\n"), ferror(file));
    }
    return result;
}