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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MAX_PATH ; 
 scalar_t__ RunCommand (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 scalar_t__ _access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ rename (char*,char const*) ; 
 size_t safe_strlen (char const*) ; 
 int /*<<< orphan*/  sevenzip_path ; 
 int /*<<< orphan*/  static_sprintf (char*,char*,int /*<<< orphan*/ ,char const*,char*,char const*) ; 
 int /*<<< orphan*/  static_strcat (char*,char const*) ; 
 int /*<<< orphan*/  static_strcpy (char*,char const*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  uprintf (char*,char const*,...) ; 

BOOL WimExtractFile_7z(const char* image, int index, const char* src, const char* dst)
{
	int n;
	size_t i;
	char cmdline[MAX_PATH];
	char tmpdst[MAX_PATH];
	char index_prefix[] = "#\\";

	uprintf("Opening: %s:[%d] (7-Zip)", image, index);

	if ((image == NULL) || (src == NULL) || (dst == NULL))
		return FALSE;

	// If you shove more than 9 images in a WIM, don't come complaining
	// that this breaks!
	index_prefix[0] = '0' + index;

	uprintf("Extracting: %s (From %s)", dst, src);

	// 7z has a quirk where the image index MUST be specified if a
	// WIM has multiple indexes, but it MUST be removed if there is
	// only one image. Because of this (and because 7z will not
	// return an error code if it can't extract the file), we need
	// to issue 2 passes. See github issue #680.
	for (n = 0; n < 2; n++) {
		static_strcpy(tmpdst, dst);
		for (i = strlen(tmpdst) - 1; (i > 0) && (tmpdst[i] != '\\') && (tmpdst[i] != '/'); i--);
		tmpdst[i] = 0;

		static_sprintf(cmdline, "\"%s\" -y e \"%s\" %s%s", sevenzip_path,
			image, (n == 0) ? index_prefix : "", src);
		if (RunCommand(cmdline, tmpdst, FALSE) != 0) {
			uprintf("  Could not launch 7z.exe: %s", WindowsErrorString());
			return FALSE;
		}

		for (i = safe_strlen(src); (i > 0) && (src[i] != '\\') && (src[i] != '/'); i--);
		if (i == 0)
			static_strcat(tmpdst, "\\");
		static_strcat(tmpdst, &src[i]);
		if (_access(tmpdst, 0) == 0)
			// File was extracted => move on
			break;
	}

	if (n >= 2) {
		uprintf("  7z.exe did not extract %s", tmpdst);
		return FALSE;
	}

	// coverity[toctou]
	if (rename(tmpdst, dst) != 0) {
		uprintf("  Could not rename %s to %s: errno %d", tmpdst, dst, errno);
		return FALSE;
	}

	return TRUE;
}