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
typedef  int /*<<< orphan*/  obuf ;
typedef  int /*<<< orphan*/  ibuf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char const*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void test_asciimode2(void)
{
    /* Error sequence from one app was getchar followed by small fread
     * with one \r removed had last byte of buffer filled with
     * next byte of *unbuffered* data rather than next byte from buffer
     * Test case is a short string of one byte followed by a newline
     * followed by filler to fill out the sector, then a sector of
     * some different byte.
     */

    FILE *fp;
    char ibuf[4];
    int i;
    static const char obuf[] =
"00\n"
"000000000000000000000000000000000000000000000000000000000000000000000000000000\n"
"000000000000000000000000000000000000000000000000000000000000000000000000000000\n"
"000000000000000000000000000000000000000000000000000000000000000000000000000000\n"
"000000000000000000000000000000000000000000000000000000000000000000000000000000\n"
"000000000000000000000000000000000000000000000000000000000000000000000000000000\n"
"000000000000000000000000000000000000000000000000000000000000000000000000000000\n"
"000000000000000000\n"
"1111111111111111111";

    fp = fopen("ascii2.tst", "wt");
    fwrite(obuf, 1, sizeof(obuf), fp);
    fclose(fp);

    fp = fopen("ascii2.tst", "rt");
    ok(getc(fp) == '0', "first char not 0\n");
    memset(ibuf, 0, sizeof(ibuf));
    i = fread(ibuf, 1, sizeof(ibuf), fp);
    ok(i == sizeof(ibuf), "fread i %d != sizeof(ibuf)\n", i);
    ok(0 == strncmp(ibuf, obuf+1, sizeof(ibuf)), "ibuf != obuf\n");
    fclose(fp);
    unlink("ascii2.tst");
}