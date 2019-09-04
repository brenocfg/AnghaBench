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
typedef  int /*<<< orphan*/  item ;
typedef  char WCHAR ;
struct TYPE_3__ {int cbSize; char* dwTypeData; int /*<<< orphan*/  fMask; } ;
typedef  TYPE_1__ MENUITEMINFOW ;
typedef  scalar_t__ LSTATUS ;
typedef  int /*<<< orphan*/ * HUSKEY ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetMenuItemCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertMenuItemW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  MIIM_STRING ; 
 int /*<<< orphan*/  SHREGENUM_HKLM ; 
 int /*<<< orphan*/  SHRegCloseUSKey (int /*<<< orphan*/ *) ; 
 scalar_t__ SHRegEnumUSValueW (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SHRegOpenUSKeyW (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ SHRegQueryUSValueW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (char const*) ; 
 int lstrlenW (char*) ; 

__attribute__((used)) static void add_tbs_to_menu(HMENU menu)
{
    static const WCHAR toolbar_key[] = {'S','o','f','t','w','a','r','e','\\',
                                        'M','i','c','r','o','s','o','f','t','\\',
                                        'I','n','t','e','r','n','e','t',' ',
                                        'E','x','p','l','o','r','e','r','\\',
                                        'T','o','o','l','b','a','r',0};
    HUSKEY toolbar_handle;

    if(SHRegOpenUSKeyW(toolbar_key, KEY_READ, NULL, &toolbar_handle, TRUE) == ERROR_SUCCESS)
    {
        static const WCHAR classes_key[] = {'S','o','f','t','w','a','r','e','\\',
                                            'C','l','a','s','s','e','s','\\','C','L','S','I','D',0};
        HUSKEY classes_handle;
        WCHAR guid[39];
        DWORD value_len = ARRAY_SIZE(guid);
        int i;

        if(SHRegOpenUSKeyW(classes_key, KEY_READ, NULL, &classes_handle, TRUE) != ERROR_SUCCESS)
        {
            SHRegCloseUSKey(toolbar_handle);
            ERR("Failed to open key %s\n", debugstr_w(classes_key));
            return;
        }

        for(i = 0; SHRegEnumUSValueW(toolbar_handle, i, guid, &value_len, NULL, NULL, NULL, SHREGENUM_HKLM) == ERROR_SUCCESS; i++)
        {
            WCHAR tb_name[100];
            DWORD tb_name_len = ARRAY_SIZE(tb_name);
            HUSKEY tb_class_handle;
            MENUITEMINFOW item;
            LSTATUS ret;
            value_len = ARRAY_SIZE(guid);

            if(lstrlenW(guid) != 38)
            {
                TRACE("Found invalid IE toolbar entry: %s\n", debugstr_w(guid));
                continue;
            }

            if(SHRegOpenUSKeyW(guid, KEY_READ, classes_handle, &tb_class_handle, TRUE) != ERROR_SUCCESS)
            {
                ERR("Failed to get class info for %s\n", debugstr_w(guid));
                continue;
            }

            ret = SHRegQueryUSValueW(tb_class_handle, NULL, NULL, tb_name, &tb_name_len, TRUE, NULL, 0);

            SHRegCloseUSKey(tb_class_handle);

            if(ret != ERROR_SUCCESS)
            {
                ERR("Failed to get toolbar name for %s\n", debugstr_w(guid));
                continue;
            }

            item.cbSize = sizeof(item);
            item.fMask = MIIM_STRING;
            item.dwTypeData = tb_name;
            InsertMenuItemW(menu, GetMenuItemCount(menu), TRUE, &item);
        }

        SHRegCloseUSKey(classes_handle);
        SHRegCloseUSKey(toolbar_handle);
    }
}