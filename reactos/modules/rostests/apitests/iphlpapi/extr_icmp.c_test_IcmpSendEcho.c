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
typedef  int /*<<< orphan*/  SendData ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  ICMP_ECHO_REPLY ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ GetLastError () ; 
 unsigned long INADDR_NONE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ IP_BUF_TOO_SMALL ; 
 scalar_t__ IP_GENERAL_FAILURE ; 
 int /*<<< orphan*/  IcmpCloseHandle (scalar_t__) ; 
 scalar_t__ IcmpCreateFile () ; 
 scalar_t__ IcmpSendEcho (scalar_t__,unsigned long,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  ok (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  skip (char*,scalar_t__) ; 

__attribute__((used)) static
void
test_IcmpSendEcho(void)
{
    HANDLE hIcmp;
    unsigned long ipaddr = INADDR_NONE;
    DWORD bRet = 0, error = 0;
    char SendData[32] = "Data Buffer";
    PVOID ReplyBuffer;
    DWORD ReplySize = 0;

    SetLastError(0xDEADBEEF);
    hIcmp = IcmpCreateFile();
    if (hIcmp == INVALID_HANDLE_VALUE)
    {
        skip("IcmpCreateFile failed unexpectedly: %lu\n", GetLastError());
        return;
    }

    ipaddr = 0x08080808; // 8.8.8.8
    ReplyBuffer = malloc(sizeof(ICMP_ECHO_REPLY) + sizeof(SendData));

    ReplySize = sizeof(ICMP_ECHO_REPLY);
    SetLastError(0xDEADBEEF);
    bRet = IcmpSendEcho(hIcmp, ipaddr, SendData, sizeof(SendData), 
        NULL, ReplyBuffer, ReplySize, 5000);

    ok(!bRet, "IcmpSendEcho succeeded unexpectedly\n");
    error = GetLastError();
    ok(error == IP_BUF_TOO_SMALL /* Win2003 */ ||
       error == IP_GENERAL_FAILURE /* Win10 */,
       "IcmpSendEcho returned unexpected error: %lu\n", error);

    ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData);
    SetLastError(0xDEADBEEF);
    bRet = IcmpSendEcho(hIcmp, ipaddr, SendData, sizeof(SendData), 
        NULL, ReplyBuffer, ReplySize, 5000);

    ok(bRet, "IcmpSendEcho failed unexpectedly: %lu\n", GetLastError());

    free(ReplyBuffer);
    IcmpCloseHandle(hIcmp);
}