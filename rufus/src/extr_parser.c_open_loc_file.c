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
 int /*<<< orphan*/ * _wfopen (int /*<<< orphan*/ *,char*) ; 
 char* conversion_error ; 
 scalar_t__ embedded_loc_filename ; 
 scalar_t__ loc_filename ; 
 int /*<<< orphan*/  safe_free (scalar_t__) ; 
 scalar_t__ safe_strcmp (char const*,char const*) ; 
 scalar_t__ safe_strdup (char const*) ; 
 int safe_strlen (char const*) ; 
 int /*<<< orphan*/  uprintf (char*,char const*) ; 
 int /*<<< orphan*/ * utf8_to_wchar (char const*) ; 

FILE* open_loc_file(const char* filename)
{
	FILE* fd = NULL;
	wchar_t *wfilename = NULL;
	const char* tmp_ext = ".tmp";

	if (filename == NULL)
		return NULL;

	if (loc_filename != embedded_loc_filename) {
		safe_free(loc_filename);
	}
	if (safe_strcmp(tmp_ext, &filename[safe_strlen(filename)-4]) == 0) {
		loc_filename = embedded_loc_filename;
	} else {
		loc_filename = safe_strdup(filename);
	}
	wfilename = utf8_to_wchar(filename);
	if (wfilename == NULL) {
		uprintf(conversion_error, filename);
		goto out;
	}
	fd = _wfopen(wfilename, L"rb");
	if (fd == NULL) {
		uprintf("localization: could not open '%s'\n", filename);
	}

out:
	safe_free(wfilename);
	return fd;
}