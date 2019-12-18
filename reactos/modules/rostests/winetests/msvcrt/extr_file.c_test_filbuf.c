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
typedef  int fpos_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int _filbuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgetpos (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void test_filbuf( void )
{
    FILE *fp;
    int c;
    fpos_t pos;

    fp = fopen("filbuf.tst", "wb");
    fwrite("\n\n\n\n", 1, 4, fp);
    fclose(fp);

    fp = fopen("filbuf.tst", "rt");
    c = _filbuf(fp);
    ok(c == '\n', "read wrong byte\n");
    /* See bug 16970 for why we care about _filbuf.
     * ftell returns screwy values on files with lots
     * of bare LFs in ascii mode because it assumes
     * that ascii files contain only CRLFs, removes
     * the CR's early in _filbuf, and adjusts the return
     * value of ftell to compensate.
     * native _filbuf will read the whole file, then consume and return
     * the first one.  That leaves fp->_fd at offset 4, and fp->_ptr
     * pointing to a buffer of three bare LFs, so
     * ftell will return 4 - 3 - 3 = -2.
     */
    ok(ftell(fp) == -2, "ascii crlf removal does not match native\n");
    ok(fgetpos(fp, &pos) == 0, "fgetpos fail\n");
    ok(pos == -2, "ftell does not match fgetpos\n");
    fclose(fp);
    unlink("filbuf.tst");
}