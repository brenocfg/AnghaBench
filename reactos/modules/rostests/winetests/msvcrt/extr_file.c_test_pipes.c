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
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int N_TEST_MESSAGES ; 
 int /*<<< orphan*/  O_BINARY ; 
 int /*<<< orphan*/  O_TEXT ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  _O_WTEXT ; 
 int /*<<< orphan*/  _P_NOWAIT ; 
 scalar_t__ _pipe (int*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ _spawnvp (int /*<<< orphan*/ ,char const*,char const**) ; 
 int close (int) ; 
 int /*<<< orphan*/  errno ; 
 int fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ *) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 char* get_base_name (char const*) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ p_fopen_s ; 
 char* pipe_string ; 
 scalar_t__* proc_handles ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  setmode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void test_pipes(const char* selfname)
{
    int pipes[2];
    char str_fdr[12], str_fdw[12];
    FILE* file;
    const char* arg_v[6];
    char buf[4096];
    char expected[4096];
    int r;
    int i;

    /* Test reading from a pipe with read() */
    if (_pipe(pipes, 1024, O_BINARY) < 0)
    {
        ok(0, "pipe failed with errno %d\n", errno);
        return;
    }

    arg_v[0] = get_base_name(selfname);
    arg_v[1] = "tests/file.c";
    arg_v[2] = "pipes";
    arg_v[3] = str_fdr; sprintf(str_fdr, "%d", pipes[0]);
    arg_v[4] = str_fdw; sprintf(str_fdw, "%d", pipes[1]);
    arg_v[5] = NULL;
    proc_handles[0] = (HANDLE)_spawnvp(_P_NOWAIT, selfname, arg_v);
    i=close(pipes[1]);
    ok(!i, "unable to close %d: %d\n", pipes[1], errno);

    for (i=0; i<N_TEST_MESSAGES; i++) {
       r=read(pipes[0], buf, sizeof(buf)-1);
       ok(r == strlen(pipe_string), "i %d, got %d\n", i, r);
       if (r > 0)
           buf[r]='\0';
       ok(strcmp(buf, pipe_string) == 0, "expected to read '%s', got '%s'\n", pipe_string, buf);
   }

    r=read(pipes[0], buf, sizeof(buf)-1);
    ok(r == 0, "expected to read 0 bytes, got %d\n", r);
    i=close(pipes[0]);
    ok(!i, "unable to close %d: %d\n", pipes[0], errno);

    /* Test reading from a pipe with fread() */
    if (_pipe(pipes, 1024, O_BINARY) < 0)
    {
        ok(0, "pipe failed with errno %d\n", errno);
        return;
    }

    arg_v[1] = "tests/file.c";
    arg_v[2] = "pipes";
    arg_v[3] = str_fdr; sprintf(str_fdr, "%d", pipes[0]);
    arg_v[4] = str_fdw; sprintf(str_fdw, "%d", pipes[1]);
    arg_v[5] = NULL;
    proc_handles[1] = (HANDLE)_spawnvp(_P_NOWAIT, selfname, arg_v);
    i=close(pipes[1]);
    ok(!i, "unable to close %d: %d\n", pipes[1], errno);
    file=fdopen(pipes[0], "r");

    /* In blocking mode, fread will keep calling read() until it gets
     * enough bytes, or EOF, even on Unix.  (If this were a Unix terminal
     * in cooked mode instead of a pipe, it would also stop on EOL.)
     */
    expected[0] = 0;
    for (i=0; i<N_TEST_MESSAGES; i++)
       strcat(expected, pipe_string);
    r=fread(buf, 1, sizeof(buf)-1, file);
    ok(r == strlen(expected), "fread() returned %d: ferror=%d\n", r, ferror(file));
    if (r > 0)
       buf[r]='\0';
    ok(strcmp(buf, expected) == 0, "got '%s' expected '%s'\n", buf, expected);

    /* Let child close the file before we read, so we can sense EOF reliably */
    Sleep(100);
    r=fread(buf, 1, sizeof(buf)-1, file);
    ok(r == 0, "fread() returned %d instead of 0\n", r);
    ok(ferror(file) == 0, "got ferror() = %d\n", ferror(file));
    ok(feof(file), "feof() is false!\n");

    i=fclose(file);
    ok(!i, "unable to close the pipe: %d\n", errno);

    /* test \r handling when it's the last character read */
    if (_pipe(pipes, 1024, O_BINARY) < 0)
    {
        ok(0, "pipe failed with errno %d\n", errno);
        return;
    }
    r = write(pipes[1], "\r\n\rab\r\n", 7);
    ok(r == 7, "write returned %d, errno = %d\n", r, errno);
    setmode(pipes[0], O_TEXT);
    r = read(pipes[0], buf, 1);
    ok(r == 1, "read returned %d, expected 1\n", r);
    ok(buf[0] == '\n', "buf[0] = %x, expected '\\n'\n", buf[0]);
    r = read(pipes[0], buf, 1);
    ok(r == 1, "read returned %d, expected 1\n", r);
    ok(buf[0] == '\r', "buf[0] = %x, expected '\\r'\n", buf[0]);
    r = read(pipes[0], buf, 1);
    ok(r == 1, "read returned %d, expected 1\n", r);
    ok(buf[0] == 'a', "buf[0] = %x, expected 'a'\n", buf[0]);
    r = read(pipes[0], buf, 2);
    ok(r == 2, "read returned %d, expected 1\n", r);
    ok(buf[0] == 'b', "buf[0] = %x, expected 'b'\n", buf[0]);
    ok(buf[1] == '\n', "buf[1] = %x, expected '\\n'\n", buf[1]);

    if (p_fopen_s)
    {
        /* test utf16 read with insufficient data */
        r = write(pipes[1], "a\0b", 3);
        ok(r == 3, "write returned %d, errno = %d\n", r, errno);
        buf[2] = 'z';
        buf[3] = 'z';
        setmode(pipes[0], _O_WTEXT);
        r = read(pipes[0], buf, 4);
        ok(r == 2, "read returned %d, expected 2\n", r);
        ok(!memcmp(buf, "a\0bz", 4), "read returned incorrect data\n");
        r = write(pipes[1], "\0", 1);
        ok(r == 1, "write returned %d, errno = %d\n", r, errno);
        buf[0] = 'z';
        buf[1] = 'z';
        r = read(pipes[0], buf, 2);
        ok(r == 0, "read returned %d, expected 0\n", r);
        ok(!memcmp(buf, "\0z", 2), "read returned incorrect data\n");
    }
    else
    {
        win_skip("unicode mode tests on pipe\n");
    }

    close(pipes[1]);
    close(pipes[0]);
}