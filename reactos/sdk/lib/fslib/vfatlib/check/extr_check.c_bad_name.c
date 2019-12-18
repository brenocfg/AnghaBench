#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* name; int lcase; } ;
struct TYPE_5__ {TYPE_1__ dir_ent; int /*<<< orphan*/ * lfn; } ;
typedef  TYPE_2__ DOS_FILE ;

/* Variables and functions */
 int FAT_NO_83NAME ; 
 int MSDOS_NAME ; 
 scalar_t__ atari_format ; 
 scalar_t__ interactive ; 
 scalar_t__ strchr (char const*,unsigned char const) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int bad_name(DOS_FILE * file)
{
    int i, spc, suspicious = 0;
    const char *bad_chars = atari_format ? "*?\\/:" : "*?<>|\"\\/:";
    const unsigned char *name = file->dir_ent.name;
    const unsigned char *ext = name + 8;

    /* Do not complain about (and auto-correct) the extended attribute files
     * of OS/2. */
    if (strncmp((const char *)name, "EA DATA  SF", 11) == 0 ||
	strncmp((const char *)name, "WP ROOT  SF", 11) == 0)
	return 0;

    /* check if we have neither a long filename nor a short name */
    if ((file->lfn == NULL) && (file->dir_ent.lcase & FAT_NO_83NAME)) {
	return 1;
    }

    /* don't complain about the dummy 11 bytes used by patched Linux
       kernels */
    if (file->dir_ent.lcase & FAT_NO_83NAME)
	return 0;

    for (i = 0; i < MSDOS_NAME; i++) {
	if (name[i] < ' ' || name[i] == 0x7f)
	    return 1;
	if (name[i] > 0x7f)
	    ++suspicious;
	if (strchr(bad_chars, name[i]))
	    return 1;
    }

    spc = 0;
    for (i = 0; i < 8; i++) {
	if (name[i] == ' ')
	    spc = 1;
	else if (spc)
	    /* non-space after a space not allowed, space terminates the name
	     * part */
	    return 1;
    }

    spc = 0;
    for (i = 0; i < 3; i++) {
	if (ext[i] == ' ')
	    spc = 1;
	else if (spc)
	    /* non-space after a space not allowed, space terminates the ext
	     * part */
	    return 1;
    }

    /* Under GEMDOS, chars >= 128 are never allowed. */
    if (atari_format && suspicious)
	return 1;

#ifdef __REACTOS__ // Old !!!!!!!!!!!!!!!

    /* Only complain about too much suspicious chars in interactive mode,
     * never correct them automatically. The chars are all basically ok, so we
     * shouldn't auto-correct such names. */
    if (interactive && suspicious > 6)
	return 1;
    return 0;

#else

    /* Under MS-DOS and Windows, chars >= 128 in short names are valid
     * (but these characters can be visualised differently depending on
     * local codepage: CP437, CP866, etc). The chars are all basically ok,
     * so we shouldn't auto-correct such names. */
    return 0;

#endif
}