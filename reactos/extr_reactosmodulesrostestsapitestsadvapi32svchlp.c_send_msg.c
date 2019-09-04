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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  StringCbPrintfA (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hClientPipe ; 
 scalar_t__ strlen (char*) ; 

void send_msg(const char *type, const char *msg)
{
    DWORD written = 0;
    char buf[512];

    StringCbPrintfA(buf, sizeof(buf), "%s:%s", type, msg);
    WriteFile(hClientPipe, buf, strlen(buf)+1, &written, NULL);
}