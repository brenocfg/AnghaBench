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
typedef  int /*<<< orphan*/  length ;
typedef  int /*<<< orphan*/  format_name ;
typedef  int /*<<< orphan*/  cf ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  scalar_t__ CLIPFORMAT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int GetClipboardFormatNameA (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  IStream_Write (int /*<<< orphan*/ *,...) ; 

__attribute__((used)) static HRESULT write_clipformat(IStream *stream, CLIPFORMAT clipformat)
{
    DWORD length;
    HRESULT hr;
    char format_name[256];

    if (clipformat == 0)
        length = 0;
    else if (clipformat < 0xc000)
        length = -1;
    else
    {
        length = GetClipboardFormatNameA(clipformat, format_name, sizeof(format_name));
        /* If there is a clipboard format name, we need to include its terminating \0 */
        if (length) length++;
    }
    hr = IStream_Write(stream, &length, sizeof(length), NULL);
    if (FAILED(hr) || clipformat == 0)
        return hr;

    if (clipformat < 0xc000)
    {
        DWORD cf = clipformat;
        hr = IStream_Write(stream, &cf, sizeof(cf), NULL);
    }
    else
    {
        hr = IStream_Write(stream, format_name, length, NULL);
    }
    return hr;
}