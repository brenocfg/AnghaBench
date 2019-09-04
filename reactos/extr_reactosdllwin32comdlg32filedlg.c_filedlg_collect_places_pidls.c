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
typedef  char WCHAR ;
struct TYPE_3__ {int const* places; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  TYPE_1__ FileOpenDlgInfos ;
typedef  int const DWORD ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int const*) ; 
#define  CSIDL_DESKTOP 130 
#define  CSIDL_DRIVES 129 
#define  CSIDL_MYDOCUMENTS 128 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHGetSpecialFolderLocation (int /*<<< orphan*/ *,int const,int const*) ; 
 int /*<<< orphan*/  SHParseDisplayName (char*,int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,int const) ; 
 int const debugstr_w (char*) ; 
 scalar_t__ get_config_key_dword (int /*<<< orphan*/ ,char*,int const*) ; 
 scalar_t__ get_config_key_string (int /*<<< orphan*/ ,char*,char**) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  sprintfW (char*,char const*,unsigned int) ; 

__attribute__((used)) static void filedlg_collect_places_pidls(FileOpenDlgInfos *fodInfos)
{
    static const int default_places[] =
    {
        CSIDL_DESKTOP,
        CSIDL_MYDOCUMENTS,
        CSIDL_DRIVES,
    };
    unsigned int i;
    HKEY hkey;

    if (!RegOpenKeyA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Comdlg32\\Placesbar",
            &hkey))
    {
        for (i = 0; i < ARRAY_SIZE(fodInfos->places); i++)
        {
            static const WCHAR placeW[] = {'P','l','a','c','e','%','d',0};
            WCHAR nameW[8];
            DWORD value;
            HRESULT hr;
            WCHAR *str;

            sprintfW(nameW, placeW, i);
            if (get_config_key_dword(hkey, nameW, &value))
            {
                hr = SHGetSpecialFolderLocation(NULL, value, &fodInfos->places[i]);
                if (FAILED(hr))
                    WARN("Unrecognized special folder %u.\n", value);
            }
            else if (get_config_key_string(hkey, nameW, &str))
            {
                hr = SHParseDisplayName(str, NULL, &fodInfos->places[i], 0, NULL);
                if (FAILED(hr))
                    WARN("Failed to parse custom places location, %s.\n", debugstr_w(str));
                heap_free(str);
            }
        }

        /* FIXME: eliminate duplicates. */

        RegCloseKey(hkey);
        return;
    }

    for (i = 0; i < ARRAY_SIZE(default_places); i++)
        SHGetSpecialFolderLocation(NULL, default_places[i], &fodInfos->places[i]);
}