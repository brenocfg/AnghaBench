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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateFileA (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,char*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,char*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void check_file_matches(const char *filename, const char *text)
{
    char buffer[200];
    HANDLE file;
    DWORD size;

    file = CreateFileA(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    ReadFile(file, buffer, sizeof(buffer), &size, NULL);
    ok(size == strlen(text) && !memcmp(buffer, text, size), "got %.*s\n", size, buffer);
    CloseHandle(file);
}