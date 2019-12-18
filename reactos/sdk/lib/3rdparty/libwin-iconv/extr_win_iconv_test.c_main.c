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

/* Variables and functions */
 scalar_t__ check_enc (char*,int) ; 
 int /*<<< orphan*/  eilseq (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  einval (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ setdll (char*) ; 
 int /*<<< orphan*/  success (char*,char*,char*,char*) ; 

int
main(int argc, char **argv)
{
#ifdef USE_LIBICONV_DLL
    /* test use of dll if $DEFAULT_LIBICONV_DLL was defined. */
    if (setdll(""))
    {
        success("ascii", "ABC", "ascii", "ABC");
        success("ascii", "ABC", "utf-16be", "\x00\x41\x00\x42\x00\x43");
    }
    else
    {
        printf("\nDLL TEST IS SKIPPED\n\n");
    }

    setdll("none");
#endif

    if (check_enc("ascii", 20127))
    {
        success("ascii", "ABC", "ascii", "ABC");
        /* MSB is dropped.  Hmm... */
        success("ascii", "\x80\xFF", "ascii", "\x00\x7F");
    }

    /* unicode (CP1200 CP1201 CP12000 CP12001 CP65001) */
    if (check_enc("utf-8", 65001)
            && check_enc("utf-16be", 1201) && check_enc("utf-16le", 1200)
            && check_enc("utf-32be", 12001) && check_enc("utf-32le", 12000)
            )
    {
        /* Test the BOM behavior
         * 1. Remove the BOM when "fromcode" is utf-16 or utf-32.
         * 2. Add the BOM when "tocode" is utf-16 or utf-32.  */
        success("utf-16", "\xFE\xFF\x01\x02", "utf-16be", "\x01\x02");
        success("utf-16", "\xFF\xFE\x02\x01", "utf-16be", "\x01\x02");
        success("utf-32", "\x00\x00\xFE\xFF\x00\x00\x01\x02", "utf-32be", "\x00\x00\x01\x02");
        success("utf-32", "\xFF\xFE\x00\x00\x02\x01\x00\x00", "utf-32be", "\x00\x00\x01\x02");
        success("utf-16", "\xFE\xFF\x00\x01", "utf-8", "\x01");
#ifndef GLIB_COMPILATION
        success("utf-8", "\x01", "utf-16", "\xFE\xFF\x00\x01");
        success("utf-8", "\x01", "utf-32", "\x00\x00\xFE\xFF\x00\x00\x00\x01");
#else
        success("utf-8", "\x01", "utf-16", "\xFF\xFE\x01\x00");
        success("utf-8", "\x01", "utf-32", "\xFF\xFE\x00\x00\x01\x00\x00\x00");
#endif

        success("utf-16be", "\xFE\xFF\x01\x02", "utf-16be", "\xFE\xFF\x01\x02");
        success("utf-16le", "\xFF\xFE\x02\x01", "utf-16be", "\xFE\xFF\x01\x02");
        success("utf-32be", "\x00\x00\xFE\xFF\x00\x00\x01\x02", "utf-32be", "\x00\x00\xFE\xFF\x00\x00\x01\x02");
        success("utf-32le", "\xFF\xFE\x00\x00\x02\x01\x00\x00", "utf-32be", "\x00\x00\xFE\xFF\x00\x00\x01\x02");
        success("utf-16be", "\xFE\xFF\x00\x01", "utf-8", "\xEF\xBB\xBF\x01");
        success("utf-8", "\xEF\xBB\xBF\x01", "utf-8", "\xEF\xBB\xBF\x01");

        success("utf-16be", "\x01\x02", "utf-16le", "\x02\x01");
        success("utf-16le", "\x02\x01", "utf-16be", "\x01\x02");
        success("utf-16be", "\xFE\xFF", "utf-16le", "\xFF\xFE");
        success("utf-16le", "\xFF\xFE", "utf-16be", "\xFE\xFF");
        success("utf-32be", "\x00\x00\x03\x04", "utf-32le", "\x04\x03\x00\x00");
        success("utf-32le", "\x04\x03\x00\x00", "utf-32be", "\x00\x00\x03\x04");
        success("utf-32be", "\x00\x00\xFF\xFF", "utf-16be", "\xFF\xFF");
        success("utf-16be", "\xFF\xFF", "utf-32be", "\x00\x00\xFF\xFF");
        success("utf-32be", "\x00\x01\x00\x00", "utf-16be", "\xD8\x00\xDC\x00");
        success("utf-16be", "\xD8\x00\xDC\x00", "utf-32be", "\x00\x01\x00\x00");
        success("utf-32be", "\x00\x10\xFF\xFF", "utf-16be", "\xDB\xFF\xDF\xFF");
        success("utf-16be", "\xDB\xFF\xDF\xFF", "utf-32be", "\x00\x10\xFF\xFF");
        eilseq("utf-32be", "\x00\x11\x00\x00", "utf-16be", "");
        eilseq("utf-16be", "\xDB\xFF\xE0\x00", "utf-32be", "");
        success("utf-8", "\xE3\x81\x82", "utf-16be", "\x30\x42");
        einval("utf-8", "\xE3", "utf-16be", "");
    }

    /* Japanese (CP932 CP20932 CP50220 CP50221 CP50222 CP51932) */
    if (check_enc("cp932", 932)
            && check_enc("cp20932", 20932) && check_enc("euc-jp", 51932)
            && check_enc("cp50220", 50220) && check_enc("cp50221", 50221)
            && check_enc("cp50222", 50222) && check_enc("iso-2022-jp", 50221))
    {
        /* Test the compatibility for each other Japanese codepage.
         * And validate the escape sequence handling for iso-2022-jp. */
        success("utf-16be", "\xFF\x5E", "cp932", "\x81\x60");
        success("utf-16be", "\x30\x1C", "cp932", "\x81\x60");
        success("utf-16be", "\xFF\x5E", "cp932//nocompat", "\x81\x60");
        eilseq("utf-16be", "\x30\x1C", "cp932//nocompat", "");
        success("euc-jp", "\xA4\xA2", "utf-16be", "\x30\x42");
        einval("euc-jp", "\xA4\xA2\xA4", "utf-16be", "\x30\x42");
        eilseq("euc-jp", "\xA4\xA2\xFF\xFF", "utf-16be", "\x30\x42");
        success("cp932", "\x81\x60", "iso-2022-jp", "\x1B\x24\x42\x21\x41\x1B\x28\x42");
        success("UTF-16BE", "\xFF\x5E", "iso-2022-jp", "\x1B\x24\x42\x21\x41\x1B\x28\x42");
        eilseq("UTF-16BE", "\x30\x1C", "iso-2022-jp//nocompat", "");
        success("UTF-16BE", "\x30\x42\x30\x44", "iso-2022-jp", "\x1B\x24\x42\x24\x22\x24\x24\x1B\x28\x42");
        success("iso-2022-jp", "\x1B\x24\x42\x21\x41\x1B\x28\x42", "UTF-16BE", "\xFF\x5E");
    }

    /*
     * test for //translit
     * U+FF41 (FULLWIDTH LATIN SMALL LETTER A) <-> U+0062 (LATIN SMALL LETTER A)
     */
    eilseq("UTF-16BE", "\xFF\x41", "iso-8859-1", "");
    success("UTF-16BE", "\xFF\x41", "iso-8859-1//translit", "a");

    /*
     * test for //translit
     * Some character, not in "to" encoding -> DEFAULT CHARACTER (maybe "?")
     */
    eilseq("UTF-16BE", "\x30\x42", "ascii", "");
    success("UTF-16BE", "\x30\x42", "ascii//translit", "?");

    /*
     * test for //ignore
     */
    eilseq("UTF-8", "\xFF A \xFF B", "ascii//ignore", " A  B");
    eilseq("UTF-8", "\xEF\xBC\xA1 A \xEF\xBC\xA2 B", "ascii//ignore", " A  B");
    eilseq("UTF-8", "\xEF\x01 A \xEF\x02 B", "ascii//ignore", "\x01 A \x02 B");

    /*
     * TODO:
     * Test for state after iconv() failed.
     * Ensure iconv() error is safe and continuable.
     */

    return 0;
}