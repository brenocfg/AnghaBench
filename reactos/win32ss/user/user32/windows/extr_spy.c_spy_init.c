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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  char BOOL ;

/* Variables and functions */
 char FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ InterlockedCompareExchange (int /*<<< orphan*/  volatile*,int,scalar_t__) ; 
 scalar_t__ InterlockedCompareExchangePointer (void**,char*,int /*<<< orphan*/ *) ; 
 scalar_t__* MessageTypeNames ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 int SPY_MAX_MSGNUM ; 
 scalar_t__ TLS_OUT_OF_INDEXES ; 
 int /*<<< orphan*/  TRACE (char*,char*) ; 
 int /*<<< orphan*/  TRACE_ON (int /*<<< orphan*/ ) ; 
 char TRUE ; 
 int TlsAlloc () ; 
 int /*<<< orphan*/  TlsFree (int) ; 
 char atoi (char*) ; 
 scalar_t__ indent_tls_index ; 
 int /*<<< orphan*/  message ; 
 scalar_t__ spy_exclude ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strstr (char*,scalar_t__) ; 

__attribute__((used)) static BOOL spy_init(void)
{
    int i;
    char buffer[1024];
    HKEY hkey;
    char *exclude;

    if (!TRACE_ON(message)) return FALSE;

    if (indent_tls_index == TLS_OUT_OF_INDEXES)
    {
        DWORD index = TlsAlloc();
        if (InterlockedCompareExchange((volatile LONG *) &indent_tls_index, index, TLS_OUT_OF_INDEXES ) != TLS_OUT_OF_INDEXES)
            TlsFree( index );
    }

    if (spy_exclude) return TRUE;
    exclude = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, SPY_MAX_MSGNUM + 2 );

    /* @@ Wine registry key: HKCU\Software\Wine\Debug */
    if(!RegOpenKeyA(HKEY_CURRENT_USER, "Software\\Wine\\Debug", &hkey))
    {
        DWORD type, count = sizeof(buffer);

        buffer[0] = 0;
        if (!RegQueryValueExA(hkey, "SpyInclude", 0, &type, (LPBYTE) buffer, &count) &&
            strcmp( buffer, "INCLUDEALL" ))
        {
            TRACE("Include=%s\n", buffer );
            for (i = 0; i <= SPY_MAX_MSGNUM; i++)
                exclude[i] = (MessageTypeNames[i] && !strstr(buffer,MessageTypeNames[i]));
        }

        count = sizeof(buffer);
        buffer[0] = 0;
        if (!RegQueryValueExA(hkey, "SpyExclude", 0, &type, (LPBYTE) buffer, &count))
        {
            TRACE("Exclude=%s\n", buffer );
            if (!strcmp( buffer, "EXCLUDEALL" ))
                for (i = 0; i <= SPY_MAX_MSGNUM; i++) exclude[i] = TRUE;
            else
                for (i = 0; i <= SPY_MAX_MSGNUM; i++)
                    exclude[i] = (MessageTypeNames[i] && strstr(buffer,MessageTypeNames[i]));
        }

        count = sizeof(buffer);
        if(!RegQueryValueExA(hkey, "SpyExcludeDWP", 0, &type, (LPBYTE) buffer, &count))
            exclude[SPY_MAX_MSGNUM + 1] = atoi(buffer);

        RegCloseKey(hkey);
    }

    if (InterlockedCompareExchangePointer( (void **)&spy_exclude, exclude, NULL ))
        HeapFree( GetProcessHeap(), 0, exclude );

    return TRUE;
}