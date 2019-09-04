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
struct hostent {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 char* WSAEFAULT ; 
 char* WSAGetLastError () ; 
 int /*<<< orphan*/  WSASetLastError (int) ; 
 struct hostent* gethostbyname (char*) ; 
 int gethostname (char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void test_gethostname(void)
{
    struct hostent *he;
    char name[256];
    int ret, len;

    WSASetLastError(0xdeadbeef);
    ret = gethostname(NULL, 256);
    ok(ret == -1, "gethostname() returned %d\n", ret);
    ok(WSAGetLastError() == WSAEFAULT, "gethostname with null buffer "
            "failed with %d, expected %d\n", WSAGetLastError(), WSAEFAULT);

    ret = gethostname(name, sizeof(name));
    ok(ret == 0, "gethostname() call failed: %d\n", WSAGetLastError());
    he = gethostbyname(name);
    ok(he != NULL, "gethostbyname(\"%s\") failed: %d\n", name, WSAGetLastError());

    len = strlen(name);
    WSASetLastError(0xdeadbeef);
    strcpy(name, "deadbeef");
    ret = gethostname(name, len);
    ok(ret == -1, "gethostname() returned %d\n", ret);
    ok(!strcmp(name, "deadbeef"), "name changed unexpected!\n");
    ok(WSAGetLastError() == WSAEFAULT, "gethostname with insufficient length "
            "failed with %d, expected %d\n", WSAGetLastError(), WSAEFAULT);

    len++;
    ret = gethostname(name, len);
    ok(ret == 0, "gethostname() call failed: %d\n", WSAGetLastError());
    he = gethostbyname(name);
    ok(he != NULL, "gethostbyname(\"%s\") failed: %d\n", name, WSAGetLastError());
}