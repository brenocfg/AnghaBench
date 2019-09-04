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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 scalar_t__ ConvertSJIS2JIS (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_an (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT ConvertJapaneseUnicodeToJIS(LPCWSTR input, DWORD count,
                                        LPSTR output, DWORD out_count)
{
    CHAR *sjis_string;
    INT len;
    UINT rc = 0;

    len = WideCharToMultiByte(932,0,input,count,0,0,NULL,NULL);
    sjis_string = HeapAlloc(GetProcessHeap(),0,len);
    WideCharToMultiByte(932,0,input,count,sjis_string,len,NULL,NULL);
    TRACE("%s\n",debugstr_an(sjis_string,len));

    rc = ConvertSJIS2JIS(sjis_string, len, NULL);
    if (out_count >= rc)
    {
        ConvertSJIS2JIS(sjis_string, len, output);
    }
    HeapFree(GetProcessHeap(),0,sjis_string);
    return rc;

}