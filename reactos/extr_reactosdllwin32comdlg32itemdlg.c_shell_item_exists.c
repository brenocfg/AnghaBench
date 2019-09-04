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
typedef  int /*<<< orphan*/  SFGAOF ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  IShellItem ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ ) ; 
 scalar_t__ GetFileAttributesW (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  IShellItem_GetAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellItem_GetDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SFGAO_VALIDATE ; 
 int /*<<< orphan*/  SIGDN_FILESYSPATH ; 
 int SUCCEEDED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL shell_item_exists(IShellItem* shellitem)
{
    LPWSTR filename;
    HRESULT hr;
    BOOL result;

    hr = IShellItem_GetDisplayName(shellitem, SIGDN_FILESYSPATH, &filename);
    if (SUCCEEDED(hr))
    {
        /* FIXME: Implement SFGAO_VALIDATE in Wine and use it instead. */
        result = (GetFileAttributesW(filename) != INVALID_FILE_ATTRIBUTES);
        CoTaskMemFree(filename);
    }
    else
    {
        SFGAOF attributes;
        result = SUCCEEDED(IShellItem_GetAttributes(shellitem, SFGAO_VALIDATE, &attributes));
    }

    return result;
}