#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_5__ {int s_b1; int s_b2; int s_b3; int s_b4; } ;
struct TYPE_6__ {TYPE_1__ S_un_b; } ;
struct TYPE_7__ {TYPE_2__ S_un; } ;
typedef  TYPE_3__ IN_ADDR ;
typedef  int DWORD_PTR ;
typedef  char CHAR ;

/* Variables and functions */
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,char*,...) ; 
 char* pRtlIpv4AddressToStringA (TYPE_3__*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  trace (char*,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlIpv4AddressToString(void)
{
    CHAR buffer[20];
    CHAR *res;
    IN_ADDR ip;
    DWORD_PTR len;

    if (!pRtlIpv4AddressToStringA)
    {
        win_skip("RtlIpv4AddressToStringA not available\n");
        return;
    }

    ip.S_un.S_un_b.s_b1 = 1;
    ip.S_un.S_un_b.s_b2 = 2;
    ip.S_un.S_un_b.s_b3 = 3;
    ip.S_un.S_un_b.s_b4 = 4;

    memset(buffer, '#', sizeof(buffer) - 1);
    buffer[sizeof(buffer) -1] = 0;
    res = pRtlIpv4AddressToStringA(&ip, buffer);
    len = strlen(buffer);
    ok(res == (buffer + len), "got %p with '%s' (expected %p)\n", res, buffer, buffer + len);

    res = pRtlIpv4AddressToStringA(&ip, NULL);
    ok( (res == (char *)~0) ||
        broken(res == (char *)len),        /* XP and w2003 */
        "got %p (expected ~0)\n", res);

    if (0) {
        /* this crashes in windows */
        memset(buffer, '#', sizeof(buffer) - 1);
        buffer[sizeof(buffer) -1] = 0;
        res = pRtlIpv4AddressToStringA(NULL, buffer);
        trace("got %p with '%s'\n", res, buffer);
    }

    if (0) {
        /* this crashes in windows */
        res = pRtlIpv4AddressToStringA(NULL, NULL);
        trace("got %p\n", res);
    }
}