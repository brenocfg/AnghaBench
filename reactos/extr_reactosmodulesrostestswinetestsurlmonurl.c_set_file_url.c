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
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int INTERNET_MAX_URL_LENGTH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  file_url ; 
 int /*<<< orphan*/  lstrcatA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lstrcpyA (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void set_file_url(char *path)
{
    CHAR file_urlA[INTERNET_MAX_URL_LENGTH];

    lstrcpyA(file_urlA, "file://");
    lstrcatA(file_urlA, path);
    MultiByteToWideChar(CP_ACP, 0, file_urlA, -1, file_url, INTERNET_MAX_URL_LENGTH);
}