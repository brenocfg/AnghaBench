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
typedef  int /*<<< orphan*/  wszValueName ;
typedef  int /*<<< orphan*/  wszSourceFilterKeyName ;
typedef  int /*<<< orphan*/  wszMinorKeyName ;
typedef  int /*<<< orphan*/  wszMajorKeyName ;
typedef  char WCHAR ;
typedef  scalar_t__ LPWSTR ;
typedef  char* LPCOLESTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IAsyncReader ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CHARS_IN_GUID ; 
 int /*<<< orphan*/  CLSIDFromString (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GUID_NULL ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HKEY_CLASSES_ROOT ; 
 scalar_t__ HRESULT_FROM_WIN32 (scalar_t__) ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  KEY_READ ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ *,int,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegEnumValueW (int /*<<< orphan*/ *,int,char*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ RegQueryInfoKeyW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 scalar_t__ process_extensions (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ process_pattern_string (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qzdebugstr_guid (int /*<<< orphan*/ *) ; 
 char* source_filter_name ; 
 scalar_t__ strcmpW (char const*,char*) ; 

HRESULT GetClassMediaFile(IAsyncReader * pReader, LPCOLESTR pszFileName, GUID * majorType, GUID * minorType, GUID * sourceFilter)
{
    HKEY hkeyMediaType = NULL;
    LONG lRet;
    HRESULT hr = S_OK;
    BOOL bFound = FALSE;
    static const WCHAR wszMediaType[] = {'M','e','d','i','a',' ','T','y','p','e',0};

    TRACE("(%p, %s, %p, %p)\n", pReader, debugstr_w(pszFileName), majorType, minorType);

    if(majorType)
        *majorType = GUID_NULL;
    if(minorType)
        *minorType = GUID_NULL;
    if(sourceFilter)
        *sourceFilter = GUID_NULL;

    lRet = RegOpenKeyExW(HKEY_CLASSES_ROOT, wszMediaType, 0, KEY_READ, &hkeyMediaType);
    hr = HRESULT_FROM_WIN32(lRet);

    if (SUCCEEDED(hr))
    {
        DWORD indexMajor;

        for (indexMajor = 0; !bFound; indexMajor++)
        {
            HKEY hkeyMajor;
            WCHAR wszMajorKeyName[CHARS_IN_GUID];
            DWORD dwKeyNameLength = sizeof(wszMajorKeyName) / sizeof(wszMajorKeyName[0]);
            static const WCHAR wszExtensions[] = {'E','x','t','e','n','s','i','o','n','s',0};

            if (RegEnumKeyExW(hkeyMediaType, indexMajor, wszMajorKeyName, &dwKeyNameLength, NULL, NULL, NULL, NULL) != ERROR_SUCCESS)
                break;
            if (RegOpenKeyExW(hkeyMediaType, wszMajorKeyName, 0, KEY_READ, &hkeyMajor) != ERROR_SUCCESS)
                break;
            TRACE("%s\n", debugstr_w(wszMajorKeyName));
            if (!strcmpW(wszExtensions, wszMajorKeyName))
            {
                if (process_extensions(hkeyMajor, pszFileName, majorType, minorType, sourceFilter) == S_OK)
                    bFound = TRUE;
            }
            /* We need a reader interface to check bytes */
            else if (pReader)
            {
                DWORD indexMinor;

                for (indexMinor = 0; !bFound; indexMinor++)
                {
                    HKEY hkeyMinor;
                    WCHAR wszMinorKeyName[CHARS_IN_GUID];
                    DWORD dwMinorKeyNameLen = sizeof(wszMinorKeyName) / sizeof(wszMinorKeyName[0]);
                    WCHAR wszSourceFilterKeyName[CHARS_IN_GUID];
                    DWORD dwSourceFilterKeyNameLen = sizeof(wszSourceFilterKeyName);
                    DWORD maxValueLen;
                    DWORD indexValue;

                    if (RegEnumKeyExW(hkeyMajor, indexMinor, wszMinorKeyName, &dwMinorKeyNameLen, NULL, NULL, NULL, NULL) != ERROR_SUCCESS)
                        break;

                    if (RegOpenKeyExW(hkeyMajor, wszMinorKeyName, 0, KEY_READ, &hkeyMinor) != ERROR_SUCCESS)
                        break;

                    TRACE("\t%s\n", debugstr_w(wszMinorKeyName));
        
                    if (RegQueryInfoKeyW(hkeyMinor, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &maxValueLen, NULL, NULL) != ERROR_SUCCESS)
                        break;

                    for (indexValue = 0; !bFound; indexValue++)
                    {
                        DWORD dwType;
                        WCHAR wszValueName[14]; /* longest name we should encounter will be "Source Filter" */
                        LPWSTR wszPatternString = HeapAlloc(GetProcessHeap(), 0, maxValueLen);
                        DWORD dwValueNameLen = sizeof(wszValueName) / sizeof(wszValueName[0]); /* remember this is in chars */
                        DWORD dwDataLen = maxValueLen; /* remember this is in bytes */

                        if (RegEnumValueW(hkeyMinor, indexValue, wszValueName, &dwValueNameLen, NULL, &dwType, (LPBYTE)wszPatternString, &dwDataLen) != ERROR_SUCCESS)
                        {
                            HeapFree(GetProcessHeap(), 0, wszPatternString);
                            break;
                        }

                        if (strcmpW(wszValueName, source_filter_name)==0) {
                            HeapFree(GetProcessHeap(), 0, wszPatternString);
                            continue;
                        }

                        /* if it is not the source filter value */
                        if (process_pattern_string(wszPatternString, pReader) == S_OK)
                        {
                            HeapFree(GetProcessHeap(), 0, wszPatternString);
                            if (majorType && FAILED(CLSIDFromString(wszMajorKeyName, majorType)))
                                break;
                            if (minorType && FAILED(CLSIDFromString(wszMinorKeyName, minorType)))
                                break;
                            if (sourceFilter)
                            {
                                /* Look up the source filter key */
                                if (RegQueryValueExW(hkeyMinor, source_filter_name, NULL, NULL, (LPBYTE)wszSourceFilterKeyName, &dwSourceFilterKeyNameLen))
                                    break;
                                if (FAILED(CLSIDFromString(wszSourceFilterKeyName, sourceFilter)))
                                    break;
                            }
                            bFound = TRUE;
                        } else
                            HeapFree(GetProcessHeap(), 0, wszPatternString);
                    }
                    CloseHandle(hkeyMinor);
                }
            }
            CloseHandle(hkeyMajor);
        }
    }
    CloseHandle(hkeyMediaType);

    if (SUCCEEDED(hr) && !bFound)
    {
        ERR("Media class not found\n");
        hr = E_FAIL;
    }
    else if (bFound)
    {
        TRACE("Found file's class:\n");
	if(majorType)
		TRACE("\tmajor = %s\n", qzdebugstr_guid(majorType));
	if(minorType)
		TRACE("\tsubtype = %s\n", qzdebugstr_guid(minorType));
	if(sourceFilter)
		TRACE("\tsource filter = %s\n", qzdebugstr_guid(sourceFilter));
    }

    return hr;
}