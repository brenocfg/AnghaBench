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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_000 ; 
 int /*<<< orphan*/  PrintStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SizeToHumanReadable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  safe_sprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  uprintf (char*,char*) ; 

__attribute__((used)) static void print_extracted_file(char* psz_fullpath, int64_t file_length)
{
	size_t i, nul_pos;

	if (psz_fullpath == NULL)
		return;
	// Replace slashes with backslashes and append the size to the path for UI display
	nul_pos = strlen(psz_fullpath);
	for (i=0; i<nul_pos; i++)
		if (psz_fullpath[i] == '/') psz_fullpath[i] = '\\';
	safe_sprintf(&psz_fullpath[nul_pos], 24, " (%s)", SizeToHumanReadable(file_length, TRUE, FALSE));
	uprintf("Extracting: %s\n", psz_fullpath);
	safe_sprintf(&psz_fullpath[nul_pos], 24, " (%s)", SizeToHumanReadable(file_length, FALSE, FALSE));
	PrintStatus(0, MSG_000, psz_fullpath);	// MSG_000 is "%s"
	// ISO9660 cannot handle backslashes
	for (i=0; i<nul_pos; i++)
		if (psz_fullpath[i] == '\\') psz_fullpath[i] = '/';
	// Remove the appended size for extraction
	psz_fullpath[nul_pos] = 0;
}