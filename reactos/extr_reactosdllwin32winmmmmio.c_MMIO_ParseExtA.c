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
typedef  int LPSTR ;
typedef  int /*<<< orphan*/ * LPCSTR ;
typedef  int /*<<< orphan*/  FOURCC ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMIO_TOUPPER ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  debugstr_a (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpynA (int /*<<< orphan*/ *,int,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mmioStringToFOURCCA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strchr (int,char) ; 
 int strlen (int) ; 
 int strrchr (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static FOURCC MMIO_ParseExtA(LPCSTR szFileName)
{
    /* Filenames are of the form file.ext{+ABC}
       For now, we take the last '+' if present */

    FOURCC ret = 0;

    /* Note that ext{Start,End} point to the . and + respectively */
    LPSTR extEnd;
    LPSTR extStart;

    TRACE("(%s)\n", debugstr_a(szFileName));

    if (!szFileName)
	return ret;

    /* Find the last '.' */
    extStart = strrchr(szFileName,'.');

    if (!extStart) {
         ERR("No . in szFileName: %s\n", debugstr_a(szFileName));
    } else {
        CHAR ext[5];

        /* Find the '+' afterwards */
        extEnd = strchr(extStart,'+');
        if (extEnd) {

            if (extEnd - extStart - 1 > 4)
                WARN("Extension length > 4\n");
            lstrcpynA(ext, extStart + 1, min(extEnd-extStart,5));

        } else {
            /* No + so just an extension */
            if (strlen(extStart) > 4) {
                WARN("Extension length > 4\n");
            }
            lstrcpynA(ext, extStart + 1, 5);
        }
        TRACE("Got extension: %s\n", debugstr_a(ext));

        /* FOURCC codes identifying file-extensions must be uppercase */
        ret = mmioStringToFOURCCA(ext, MMIO_TOUPPER);
    }
    return ret;
}