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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void test_asciimode(void)
{
    FILE *fp;
    char buf[64];
    int c, i, j;

    /* Simple test of CR CR LF handling.  Test both fgets and fread code paths, they're different! */
    fp = fopen("ascii.tst", "wb");
    fputs("\r\r\n", fp);
    fclose(fp);
    fp = fopen("ascii.tst", "rt");
    ok(fgets(buf, sizeof(buf), fp) != NULL, "fgets\n");
    ok(0 == strcmp(buf, "\r\n"), "CR CR LF not read as CR LF\n");
    rewind(fp);
    ok((fread(buf, 1, sizeof(buf), fp) == 2) && (0 == strcmp(buf, "\r\n")), "CR CR LF not read as CR LF\n");
    fclose(fp);
    unlink("ascii.tst");

    /* Simple test of foo ^Z [more than one block] bar handling */
    fp = fopen("ascii.tst", "wb");
    fputs("foo\032", fp);  /* foo, logical EOF, ... */
    fseek(fp, 65536L, SEEK_SET); /* ... more than MSVCRT_BUFSIZ, ... */
    fputs("bar", fp); /* ... bar */
    fclose(fp);
    fp = fopen("ascii.tst", "rt");
    ok(fgets(buf, sizeof(buf), fp) != NULL, "fgets foo\n");
    ok(0 == strcmp(buf, "foo"), "foo ^Z not read as foo by fgets\n");
    ok(fgets(buf, sizeof(buf), fp) == NULL, "fgets after logical EOF\n");
    rewind(fp);
    ok((fread(buf, 1, sizeof(buf), fp) == 3) && (0 == strcmp(buf, "foo")), "foo ^Z not read as foo by fread\n");
    ok((fread(buf, 1, sizeof(buf), fp) == 0), "fread after logical EOF\n");
    fclose(fp);

    /* Show ASCII mode handling*/
    fp= fopen("ascii.tst","wb");
    fputs("0\r\n1\r\n2\r\n3\r\n4\r\n5\r\n6\r\n7\r\n8\r\n9\r\n", fp);
    fclose(fp);

    fp = fopen("ascii.tst", "r");
    c= fgetc(fp);
    ok(c == '0', "fgetc failed, expected '0', got '%c'\n", c);
    c= fgetc(fp);
    ok(c == '\n', "fgetc failed, expected '\\n', got '%c'\n", c);
    fseek(fp,0,SEEK_CUR);
    for(i=1; i<10; i++) {
	ok((j = ftell(fp)) == i*3, "ftell fails in TEXT mode\n");
	fseek(fp,0,SEEK_CUR);
	ok((c = fgetc(fp)) == '0'+ i, "fgetc after fseek failed in line %d\n", i);
	c= fgetc(fp);
        ok(c == '\n', "fgetc failed, expected '\\n', got '%c'\n", c);
    }
    /* Show that fseek doesn't skip \\r !*/
    rewind(fp);
    c= fgetc(fp);
    ok(c == '0', "fgetc failed, expected '0', got '%c'\n", c);
    fseek(fp, 2 ,SEEK_CUR);
    for(i=1; i<10; i++) {
	ok((c = fgetc(fp)) == '0'+ i, "fgetc after fseek with pos Offset failed in line %d\n", i);
	fseek(fp, 2 ,SEEK_CUR);
    }
    fseek(fp, 9*3 ,SEEK_SET);
    c = fgetc(fp);
    ok(c == '9', "fgetc failed, expected '9', got '%c'\n", c);
    fseek(fp, -4 ,SEEK_CUR);
    for(i= 8; i>=0; i--) {
	ok((c = fgetc(fp)) == '0'+ i, "fgetc after fseek with neg Offset failed in line %d\n", i);
	fseek(fp, -4 ,SEEK_CUR);
    }
    /* Show what happens if fseek positions filepointer on \\r */
    fclose(fp);
    fp = fopen("ascii.tst", "r");
    fseek(fp, 3 ,SEEK_SET);
    ok((c = fgetc(fp)) == '1', "fgetc fails to read next char when positioned on \\r\n");
    fclose(fp);

    unlink("ascii.tst");
}