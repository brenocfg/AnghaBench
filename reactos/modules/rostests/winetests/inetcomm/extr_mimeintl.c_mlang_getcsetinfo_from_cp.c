#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/ * wszWebCharset; int /*<<< orphan*/ * wszHeaderCharset; int /*<<< orphan*/ * wszBodyCharset; } ;
typedef  int /*<<< orphan*/  MIMECSETINFO ;
typedef  TYPE_1__ MIMECPINFO ;
typedef  int /*<<< orphan*/  IMultiLanguage ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int CHARSETTYPE ;

/* Variables and functions */
#define  CHARSET_BODY 130 
#define  CHARSET_HEADER 129 
#define  CHARSET_WEB 128 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMultiLanguage_GetCharsetInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMultiLanguage_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_mlang (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mlang_getcodepageinfo (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static HRESULT mlang_getcsetinfo_from_cp(UINT cp, CHARSETTYPE charset_type, MIMECSETINFO *mlang_info)
{
    MIMECPINFO mlang_cp_info;
    WCHAR *charset_name;
    HRESULT hr;
    IMultiLanguage *ml;

    hr = mlang_getcodepageinfo(cp, &mlang_cp_info);
    if(FAILED(hr)) return hr;

    switch(charset_type)
    {
    case CHARSET_BODY:
        charset_name = mlang_cp_info.wszBodyCharset;
        break;
    case CHARSET_HEADER:
        charset_name = mlang_cp_info.wszHeaderCharset;
        break;
    case CHARSET_WEB:
        charset_name = mlang_cp_info.wszWebCharset;
        break;
    }

    hr = get_mlang(&ml);

    if(SUCCEEDED(hr))
    {
        hr = IMultiLanguage_GetCharsetInfo(ml, charset_name, mlang_info);
        IMultiLanguage_Release(ml);
    }
    return hr;
}