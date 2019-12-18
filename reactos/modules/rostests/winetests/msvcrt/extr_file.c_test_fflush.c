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
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf1 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ *) ; 
 int _flushall () ; 
 int /*<<< orphan*/  _lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* _tempnam (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (char const*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void test_fflush( void )
{
  static const char obuf[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
  char buf1[16], buf2[24];
  char *tempf;
  FILE *tempfh;
  int ret;

  tempf=_tempnam(".","wne");

  /* Prepare the file. */
  tempfh = fopen(tempf,"wb");
  ok(tempfh != NULL, "Can't open test file.\n");
  fwrite(obuf, 1, sizeof(obuf), tempfh);
  fclose(tempfh);

  /* Open the file for input. */
  tempfh = fopen(tempf,"rb");
  ok(tempfh != NULL, "Can't open test file.\n");
  fread(buf1, 1, sizeof(buf1), tempfh);

  /* Using fflush() on input stream is undefined in ANSI.
   * But MSDN says that it clears input buffer. */
  _lseek(_fileno(tempfh), 0, SEEK_SET);
  ret = fflush(tempfh);
  ok(ret == 0, "expected 0, got %d\n", ret);
  memset(buf2, '?', sizeof(buf2));
  fread(buf2, 1, sizeof(buf2), tempfh);
  ok(memcmp(buf1, buf2, sizeof(buf1)) == 0, "Got unexpected data (%c)\n", buf2[0]);

  /* fflush(NULL) doesn't clear input buffer. */
  _lseek(_fileno(tempfh), 0, SEEK_SET);
  ret = fflush(NULL);
  ok(ret == 0, "expected 0, got %d\n", ret);
  memset(buf2, '?', sizeof(buf2));
  fread(buf2, 1, sizeof(buf2), tempfh);
  ok(memcmp(buf1, buf2, sizeof(buf1)) != 0, "Got unexpected data (%c)\n", buf2[0]);

  /* _flushall() clears input buffer. */
  _lseek(_fileno(tempfh), 0, SEEK_SET);
  ret = _flushall();
  ok(ret >= 0, "unexpected ret %d\n", ret);
  memset(buf2, '?', sizeof(buf2));
  fread(buf2, 1, sizeof(buf2), tempfh);
  ok(memcmp(buf1, buf2, sizeof(buf1)) == 0, "Got unexpected data (%c)\n", buf2[0]);

  fclose(tempfh);

  unlink(tempf);
  free(tempf);
}