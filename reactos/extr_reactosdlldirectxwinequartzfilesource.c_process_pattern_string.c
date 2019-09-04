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
typedef  int ULONG ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  IAsyncReader ;
typedef  scalar_t__ HRESULT ;
typedef  int BYTE ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ IAsyncReader_SyncRead (int /*<<< orphan*/ *,int,int,int*) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int byte_from_hex_char (char) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 scalar_t__ isxdigitW (char) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 char* strchrW (char*,char) ; 
 int strtolW (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HRESULT process_pattern_string(LPCWSTR wszPatternString, IAsyncReader * pReader)
{
    ULONG ulOffset;
    ULONG ulBytes;
    BYTE * pbMask;
    BYTE * pbValue;
    BYTE * pbFile;
    HRESULT hr = S_OK;
    ULONG strpos;

    TRACE("\t\tPattern string: %s\n", debugstr_w(wszPatternString));
    
    /* format: "offset, bytestocompare, mask, value" */

    ulOffset = strtolW(wszPatternString, NULL, 10);

    if (!(wszPatternString = strchrW(wszPatternString, ',')))
        return E_INVALIDARG;

    wszPatternString++; /* skip ',' */

    ulBytes = strtolW(wszPatternString, NULL, 10);

    pbMask = HeapAlloc(GetProcessHeap(), 0, ulBytes);
    pbValue = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, ulBytes);
    pbFile = HeapAlloc(GetProcessHeap(), 0, ulBytes);

    /* default mask is match everything */
    memset(pbMask, 0xFF, ulBytes);

    if (!(wszPatternString = strchrW(wszPatternString, ',')))
        hr = E_INVALIDARG;

    if (hr == S_OK)
    {
        wszPatternString++; /* skip ',' */
        while (!isxdigitW(*wszPatternString) && (*wszPatternString != ',')) wszPatternString++;

        for (strpos = 0; isxdigitW(*wszPatternString) && (strpos/2 < ulBytes); wszPatternString++, strpos++)
        {
            if ((strpos % 2) == 1) /* odd numbered position */
                pbMask[strpos / 2] |= byte_from_hex_char(*wszPatternString);
            else
                pbMask[strpos / 2] = byte_from_hex_char(*wszPatternString) << 4;
        }

        if (!(wszPatternString = strchrW(wszPatternString, ',')))
            hr = E_INVALIDARG;
        else
            wszPatternString++; /* skip ',' */
    }

    if (hr == S_OK)
    {
        for ( ; !isxdigitW(*wszPatternString) && (*wszPatternString != ','); wszPatternString++)
            ;

        for (strpos = 0; isxdigitW(*wszPatternString) && (strpos/2 < ulBytes); wszPatternString++, strpos++)
        {
            if ((strpos % 2) == 1) /* odd numbered position */
                pbValue[strpos / 2] |= byte_from_hex_char(*wszPatternString);
            else
                pbValue[strpos / 2] = byte_from_hex_char(*wszPatternString) << 4;
        }
    }

    if (hr == S_OK)
        hr = IAsyncReader_SyncRead(pReader, ulOffset, ulBytes, pbFile);

    if (hr == S_OK)
    {
        ULONG i;
        for (i = 0; i < ulBytes; i++)
            if ((pbFile[i] & pbMask[i]) != pbValue[i])
            {
                hr = S_FALSE;
                break;
            }
    }

    HeapFree(GetProcessHeap(), 0, pbMask);
    HeapFree(GetProcessHeap(), 0, pbValue);
    HeapFree(GetProcessHeap(), 0, pbFile);

    /* if we encountered no errors with this string, and there is a following tuple, then we
     * have to match that as well to succeed */
    if ((hr == S_OK) && (wszPatternString = strchrW(wszPatternString, ',')))
        return process_pattern_string(wszPatternString + 1, pReader);
    else
        return hr;
}