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
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  INDEX_HTML ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 

__attribute__((used)) static void set_file_url(char *path)
{
    char INDEX_HTML_A[MAX_PATH];

    lstrcpyA(INDEX_HTML_A, "file:///");
    lstrcatA(INDEX_HTML_A, path);
    MultiByteToWideChar(CP_ACP, 0, INDEX_HTML_A, -1, INDEX_HTML, MAX_PATH);
}