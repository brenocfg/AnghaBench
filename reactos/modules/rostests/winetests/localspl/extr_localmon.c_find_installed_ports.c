#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_4__ {char* pName; } ;
typedef  TYPE_1__ PORT_INFO_1W ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  size_t DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int PORTNAME_MAXSIZE ; 
 size_t PORTNAME_MINSIZE ; 
 int PORTNAME_PREFIX ; 
 char* have_com ; 
 char* have_file ; 
 char* have_lpt ; 
 scalar_t__ lstrcmpiW (char*,int /*<<< orphan*/ ) ; 
 size_t lstrlenW (char*) ; 
 int /*<<< orphan*/  memcpy (char**,char*,size_t) ; 
 size_t pEnumPorts (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t,size_t*,size_t*) ; 
 int /*<<< orphan*/  portname_comW ; 
 int /*<<< orphan*/  portname_fileW ; 
 int /*<<< orphan*/  portname_lptW ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void find_installed_ports(void)
{
    PORT_INFO_1W * pi = NULL;
    WCHAR   nameW[PORTNAME_MAXSIZE];
    DWORD   needed;
    DWORD   returned;
    DWORD   res;
    DWORD   id;

    have_com[0] = '\0';
    have_lpt[0] = '\0';
    have_file[0] = '\0';

    if (!pEnumPorts) return;

    res = pEnumPorts(NULL, 1, NULL, 0, &needed, &returned);
    if (!res && (GetLastError() == ERROR_INSUFFICIENT_BUFFER)) {
        pi = HeapAlloc(GetProcessHeap(), 0, needed);
    }
    res = pEnumPorts(NULL, 1, (LPBYTE) pi, needed, &needed, &returned);

    if (!res) {
        skip("no ports found\n");
        HeapFree(GetProcessHeap(), 0, pi);
        return;
    }

    id = 0;
    while (id < returned) {
        res = lstrlenW(pi[id].pName);
        if ((res >= PORTNAME_MINSIZE) && (res < PORTNAME_MAXSIZE) &&
            (pi[id].pName[res-1] == ':')) {
            /* copy only the prefix ("LPT" or "COM") */
            memcpy(&nameW, pi[id].pName, PORTNAME_PREFIX * sizeof(WCHAR));
            nameW[PORTNAME_PREFIX] = '\0';

            if (!have_com[0] && (lstrcmpiW(nameW, portname_comW) == 0)) {
                memcpy(&have_com, pi[id].pName, (res+1) * sizeof(WCHAR));
            }

            if (!have_lpt[0] && (lstrcmpiW(nameW, portname_lptW) == 0)) {
                memcpy(&have_lpt, pi[id].pName, (res+1) * sizeof(WCHAR));
            }

            if (!have_file[0] && (lstrcmpiW(pi[id].pName, portname_fileW) == 0)) {
                memcpy(&have_file, pi[id].pName, (res+1) * sizeof(WCHAR));
            }
        }
        id++;
    }

    HeapFree(GetProcessHeap(), 0, pi);
}