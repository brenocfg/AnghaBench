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
typedef  scalar_t__ LPSTR ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CURR_DIR ; 
 int /*<<< orphan*/  GetTempFileNameA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  strcpy (scalar_t__,scalar_t__) ; 
 scalar_t__ strrchr (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static void get_temp_filename(LPSTR path)
{
    CHAR temp[MAX_PATH];
    LPSTR ptr;

    GetTempFileNameA(CURR_DIR, "set", 0, temp);
    ptr = strrchr(temp, '\\');

    strcpy(path, ptr + 1);
}