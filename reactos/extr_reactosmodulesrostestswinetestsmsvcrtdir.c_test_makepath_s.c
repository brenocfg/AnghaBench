#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* buffer; int length; char* drive; char* dir; char* file; char* ext; int expected_length; int /*<<< orphan*/  expected_unicode; int /*<<< orphan*/  expected; } ;
typedef  TYPE_1__ makepath_s_case ;
struct TYPE_4__ {char* buffer; char* drive; char* dir; char* file; char* ext; int /*<<< orphan*/  expected; } ;
typedef  TYPE_2__ makepath_case ;
typedef  char WCHAR ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int EBADF ; 
 int EINVAL ; 
 int ERANGE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 char* USE_BUFF ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int errno ; 
 void* makepath_cases ; 
 void* makepath_s_cases ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int p_makepath_s (char*,int,char*,char*,char*,char*) ; 
 int p_wmakepath_s (char*,int,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_makepath_s(void)
{
    WCHAR driveW[MAX_PATH];
    WCHAR dirW[MAX_PATH];
    WCHAR fileW[MAX_PATH];
    WCHAR extW[MAX_PATH];
    WCHAR bufferW[MAX_PATH];
    char buffer[MAX_PATH];
    int ret;
    unsigned int i, n;

    if (!p_makepath_s || !p_wmakepath_s)
    {
        win_skip("Safe makepath functions are not available\n");
        return;
    }

    errno = EBADF;
    ret = p_makepath_s(NULL, 0, NULL, NULL, NULL, NULL);
    ok(ret == EINVAL, "Expected _makepath_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    errno = EBADF;
    ret = p_makepath_s(buffer, 0, NULL, NULL, NULL, NULL);
    ok(ret == EINVAL, "Expected _makepath_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    errno = EBADF;
    ret = p_wmakepath_s(NULL, 0, NULL, NULL, NULL, NULL);
    ok(ret == EINVAL, "Expected _wmakepath_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    errno = EBADF;
    ret = p_wmakepath_s(bufferW, 0, NULL, NULL, NULL, NULL);
    ok(ret == EINVAL, "Expected _wmakepath_s to return EINVAL, got %d\n", ret);
    ok(errno == EINVAL, "Expected errno to be EINVAL, got %d\n", errno);

    /* Test with the normal _makepath cases. */
    for (i = 0; i < ARRAY_SIZE(makepath_cases); i++)
    {
        const makepath_case *p = makepath_cases + i;

        memset(buffer, 'X', MAX_PATH);
        if (p->buffer)
            strcpy(buffer, p->buffer);

        /* Ascii */
        ret = p_makepath_s(buffer, MAX_PATH,
                           p->drive == USE_BUFF ? buffer : p->drive,
                           p->dir == USE_BUFF ? buffer : p->dir,
                           p->file == USE_BUFF? buffer : p->file,
                           p->ext == USE_BUFF ? buffer : p->ext);
        ok(ret == 0, "[%d] Expected _makepath_s to return 0, got %d\n", i, ret);

        buffer[MAX_PATH - 1] = '\0';
        ok(!strcmp(p->expected, buffer), "got '%s' for case %d\n", buffer, i);

        /* Unicode */
        if (p->drive != USE_BUFF) MultiByteToWideChar(CP_ACP, 0, p->drive, -1, driveW, MAX_PATH);
        if (p->dir != USE_BUFF) MultiByteToWideChar(CP_ACP, 0, p->dir, -1, dirW, MAX_PATH);
        if (p->file != USE_BUFF) MultiByteToWideChar(CP_ACP, 0, p->file, -1, fileW, MAX_PATH);
        if (p->ext != USE_BUFF) MultiByteToWideChar(CP_ACP, 0, p->ext, -1, extW, MAX_PATH);

        memset(buffer, 0, MAX_PATH);
        for (n = 0; n < MAX_PATH; ++n)
            bufferW[n] = 'X';
        if (p->buffer) MultiByteToWideChar( CP_ACP, 0, p->buffer, -1, bufferW, MAX_PATH);

        ret = p_wmakepath_s(bufferW, MAX_PATH,
                            p->drive == USE_BUFF ? bufferW : p->drive ? driveW : NULL,
                            p->dir == USE_BUFF ? bufferW : p->dir ? dirW : NULL,
                            p->file == USE_BUFF? bufferW : p->file ? fileW : NULL,
                            p->ext == USE_BUFF ? bufferW : p->ext ? extW : NULL);
        ok(ret == 0, "[%d] Expected _wmakepath_s to return 0, got %d\n", i, ret);

        bufferW[MAX_PATH - 1] = '\0';
        WideCharToMultiByte(CP_ACP, 0, bufferW, -1, buffer, MAX_PATH, NULL, NULL);
        ok(!strcmp(p->expected, buffer), "got '%s' for unicode case %d\n", buffer, i);
    }

    /* Try insufficient length cases. */
    for (i = 0; i < ARRAY_SIZE(makepath_s_cases); i++)
    {
        const makepath_s_case *p = makepath_s_cases + i;

        memset(buffer, 'X', MAX_PATH);
        if (p->buffer)
            strcpy(buffer, p->buffer);

        /* Ascii */
        errno = EBADF;
        ret = p_makepath_s(buffer, p->length,
                           p->drive == USE_BUFF ? buffer : p->drive,
                           p->dir == USE_BUFF ? buffer : p->dir,
                           p->file == USE_BUFF? buffer : p->file,
                           p->ext == USE_BUFF ? buffer : p->ext);
        ok(ret == ERANGE, "[%d] Expected _makepath_s to return ERANGE, got %d\n", i, ret);
        ok(errno == ERANGE, "[%d] Expected errno to be ERANGE, got %d\n", i, errno);
        ok(!memcmp(p->expected, buffer, p->expected_length), "unexpected output for case %d\n", i);

        /* Unicode */
        if (p->drive != USE_BUFF) MultiByteToWideChar(CP_ACP, 0, p->drive, -1, driveW, MAX_PATH);
        if (p->dir != USE_BUFF) MultiByteToWideChar(CP_ACP, 0, p->dir, -1, dirW, MAX_PATH);
        if (p->file != USE_BUFF) MultiByteToWideChar(CP_ACP, 0, p->file, -1, fileW, MAX_PATH);
        if (p->ext != USE_BUFF) MultiByteToWideChar(CP_ACP, 0, p->ext, -1, extW, MAX_PATH);

        memset(buffer, 0, MAX_PATH);
        for (n = 0; n < MAX_PATH; ++n)
            bufferW[n] = 'X';
        if (p->buffer) MultiByteToWideChar( CP_ACP, 0, p->buffer, -1, bufferW, MAX_PATH);

        errno = EBADF;
        ret = p_wmakepath_s(bufferW, p->length,
                            p->drive == USE_BUFF ? bufferW : p->drive ? driveW : NULL,
                            p->dir == USE_BUFF ? bufferW : p->dir ? dirW : NULL,
                            p->file == USE_BUFF? bufferW : p->file ? fileW : NULL,
                            p->ext == USE_BUFF ? bufferW : p->ext ? extW : NULL);
        ok(ret == ERANGE, "[%d] Expected _wmakepath_s to return ERANGE, got %d\n", i, ret);
        ok(errno == ERANGE, "[%d] Expected errno to be ERANGE, got %d\n", i, errno);

        ok(!memcmp(p->expected_unicode, bufferW, p->expected_length * sizeof(WCHAR)), "unexpected output for case %d\n", i);
    }
}