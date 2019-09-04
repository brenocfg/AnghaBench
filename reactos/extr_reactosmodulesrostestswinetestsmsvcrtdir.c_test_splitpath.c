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
 int MAX_PATH ; 
 int _getmbcp () ; 
 int /*<<< orphan*/  _setmbcp (int) ; 
 int /*<<< orphan*/  _splitpath (char const*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void test_splitpath(void)
{
    const char* path = "c:\\\x83\x5c\x83\x74\x83\x67.bin";
    char drive[3], dir[MAX_PATH], fname[MAX_PATH], ext[MAX_PATH];
    int prev_cp = _getmbcp();

    /* SBCS codepage */
    _setmbcp(1252);
    _splitpath(path, drive, dir, fname, ext);
    ok(!strcmp(drive, "c:"), "got %s\n", drive);
    ok(!strcmp(dir, "\\\x83\x5c"), "got %s\n", dir);
    ok(!strcmp(fname, "\x83\x74\x83\x67"), "got %s\n", fname);
    ok(!strcmp(ext, ".bin"), "got %s\n", ext);

    /* MBCS (Japanese) codepage */
    _setmbcp(932);
    _splitpath(path, drive, dir, fname, ext);
    ok(!strcmp(drive, "c:"), "got %s\n", drive);
    ok(!strcmp(dir, "\\"), "got %s\n", dir);
    ok(!strcmp(fname, "\x83\x5c\x83\x74\x83\x67"), "got %s\n", fname);
    ok(!strcmp(ext, ".bin"), "got %s\n", ext);

    _setmbcp(prev_cp);
}