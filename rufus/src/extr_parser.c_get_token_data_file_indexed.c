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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _wfopen (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  conversion_error ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgetws (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_token_data_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safe_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uprintf (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * utf8_to_wchar (char const*) ; 
 char* wchar_to_utf8 (int /*<<< orphan*/ *) ; 

char* get_token_data_file_indexed(const char* token, const char* filename, int index)
{
	int i = 0;
	wchar_t *wtoken = NULL, *wdata= NULL, *wfilename = NULL;
	wchar_t buf[1024];
	FILE* fd = NULL;
	char *ret = NULL;

	if ((filename == NULL) || (token == NULL))
		return NULL;
	if ((filename[0] == 0) || (token[0] == 0))
		return NULL;

	wfilename = utf8_to_wchar(filename);
	if (wfilename == NULL) {
		uprintf(conversion_error, filename);
		goto out;
	}
	wtoken = utf8_to_wchar(token);
	if (wfilename == NULL) {
		uprintf(conversion_error, token);
		goto out;
	}
	fd = _wfopen(wfilename, L"r, ccs=UNICODE");
	if (fd == NULL) goto out;

	// Process individual lines. NUL is always appended.
	// Ideally, we'd check that our buffer fits the line
	while (fgetws(buf, ARRAYSIZE(buf), fd) != NULL) {
		wdata = get_token_data_line(wtoken, buf);
		if ((wdata != NULL) && (++i == index)) {
			ret = wchar_to_utf8(wdata);
			break;
		}
	}

out:
	if (fd != NULL)
		fclose(fd);
	safe_free(wfilename);
	safe_free(wtoken);
	return ret;
}