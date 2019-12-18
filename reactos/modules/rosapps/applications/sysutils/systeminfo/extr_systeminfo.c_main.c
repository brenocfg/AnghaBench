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
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 int /*<<< orphan*/  AllSysInfo () ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  Usage () ; 
 int /*<<< orphan*/  WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int
main(int argc, char *argv[])
{
    WSADATA WsaData;
    int i;

    setlocale(LC_ALL, "");

    WSAStartup(MAKEWORD(2, 2), &WsaData);

    for (i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], "/?") || !strcmp(argv[i], "-?"))
        {
            Usage();
            return 0;
        }
        else
        {
            printf("Unsupported argument: %s\n", argv[i]);
            return -1;
        }
    }

    AllSysInfo();

    return 0;
}