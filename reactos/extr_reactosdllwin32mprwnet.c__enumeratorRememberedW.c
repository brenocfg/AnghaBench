#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_9__ {int dwType; char* lpLocalName; char* lpProvider; char* lpRemoteName; int /*<<< orphan*/ * lpComment; int /*<<< orphan*/  dwUsage; int /*<<< orphan*/  dwDisplayType; int /*<<< orphan*/  dwScope; } ;
struct TYPE_6__ {int index; int /*<<< orphan*/  registry; } ;
struct TYPE_7__ {TYPE_1__ remembered; } ;
struct TYPE_8__ {int dwType; TYPE_2__ specific; } ;
typedef  TYPE_3__* PWNetEnumerator ;
typedef  TYPE_4__ NETRESOURCEW ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ARRAY_SIZE (char*) ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RESOURCEDISPLAYTYPE_GENERIC ; 
 int RESOURCETYPE_ANY ; 
 int /*<<< orphan*/  RESOURCEUSAGE_CONNECTABLE ; 
 int /*<<< orphan*/  RESOURCE_REMEMBERED ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int RegEnumKeyExW (int /*<<< orphan*/ ,int,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int WN_MORE_DATA ; 
 int WN_NO_MORE_ENTRIES ; 
 int WN_SUCCESS ; 
 int /*<<< orphan*/  connectionType ; 
 char* get_reg_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 
 int /*<<< orphan*/  providerName ; 
 int /*<<< orphan*/  remotePath ; 

__attribute__((used)) static DWORD _enumeratorRememberedW(PWNetEnumerator enumerator, DWORD* user_count,
                                    void* user_buffer, DWORD* user_size)
{
    HKEY registry, connection;
    WCHAR buffer[255];
    LONG size_left;
    DWORD index, ret, type, len, size, registry_size, full_size = 0, total_count;
    NETRESOURCEW * net_buffer = user_buffer;
    WCHAR * str, * registry_string;

    /* we will do the work in a single loop, so here is some things:
     * we write netresource at the begin of the user buffer
     * we write strings at the end of the user buffer
     */
    size_left = *user_size;
    total_count = 0;
    type = enumerator->dwType;
    registry = enumerator->specific.remembered.registry;
    str = (WCHAR *)((ULONG_PTR)user_buffer + *user_size - sizeof(WCHAR));
    for (index = enumerator->specific.remembered.index; ; ++index)
    {
        enumerator->specific.remembered.index = index;

        if (*user_count != -1 && total_count == *user_count)
        {
            ret = WN_SUCCESS;
            break;
        }

        len = ARRAY_SIZE(buffer);
        ret = RegEnumKeyExW(registry, index, buffer, &len, NULL, NULL, NULL, NULL);
        if (ret != ERROR_SUCCESS)
        {
            if (ret == ERROR_NO_MORE_ITEMS) ret = WN_SUCCESS;
            break;
        }

        if (RegOpenKeyExW(registry, buffer, 0, KEY_READ, &connection) != ERROR_SUCCESS)
        {
            continue;
        }

        full_size = sizeof(NETRESOURCEW);
        size_left -= sizeof(NETRESOURCEW);

        if (size_left > 0)
        {
            size = sizeof(DWORD);
            RegQueryValueExW(connection, connectionType, NULL, NULL, (BYTE *)&net_buffer->dwType, &size);
            if (type != RESOURCETYPE_ANY && net_buffer->dwType != type)
            {
                size_left += sizeof(NETRESOURCEW);
                RegCloseKey(connection);
                continue;
            }

            net_buffer->dwScope = RESOURCE_REMEMBERED;
            net_buffer->dwDisplayType = RESOURCEDISPLAYTYPE_GENERIC;
            net_buffer->dwUsage = RESOURCEUSAGE_CONNECTABLE;
        }
        else
            ret = WN_MORE_DATA;

        /* FIXME: this only supports drive letters */
        full_size += 3 * sizeof(WCHAR);
        size_left -= 3 * sizeof(WCHAR);
        if (size_left > 0)
        {
            str -= 3;
            str[0] = buffer[0];
            str[1] = ':';
            str[2] = 0;
            net_buffer->lpLocalName = str;
        }

        registry_size = 0;
        registry_string = get_reg_str(connection, providerName, &registry_size);
        if (registry_string)
        {
            full_size += registry_size;
            size_left -= registry_size;

            if (size_left > 0)
            {
                str -= (registry_size / sizeof(WCHAR));
                lstrcpyW(str, registry_string);
                net_buffer->lpProvider = str;
            }
            else
                ret = WN_MORE_DATA;

            HeapFree(GetProcessHeap(), 0, registry_string);
        }

        registry_size = 0;
        registry_string = get_reg_str(connection, remotePath, &registry_size);
        if (registry_string)
        {
            full_size += registry_size;
            size_left -= registry_size;

            if (size_left > 0)
            {
                str -= (registry_size / sizeof(WCHAR));
                lstrcpyW(str, registry_string);
                net_buffer->lpRemoteName = str;
            }
            else
                ret = WN_MORE_DATA;

            HeapFree(GetProcessHeap(), 0, registry_string);
        }

        RegCloseKey(connection);

        net_buffer->lpComment = NULL;

        if (size_left < 0)
            break;

        ++total_count;
        ++net_buffer;
    }

    if (total_count == 0)
        ret = WN_NO_MORE_ENTRIES;

    *user_count = total_count;

    if (ret != WN_MORE_DATA && ret != WN_NO_MORE_ENTRIES)
        ret = WN_SUCCESS;

    if (ret == WN_MORE_DATA)
        *user_size = *user_size + full_size;

    return ret;
}