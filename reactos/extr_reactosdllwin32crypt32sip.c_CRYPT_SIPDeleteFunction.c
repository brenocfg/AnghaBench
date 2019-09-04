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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_guid2wstr (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  RegDeleteKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcatW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szOID ; 

__attribute__((used)) static LONG CRYPT_SIPDeleteFunction( const GUID *guid, LPCWSTR szKey )
{
    WCHAR szFullKey[ 0x100 ];
    LONG r = ERROR_SUCCESS;

    /* max length of szFullKey depends on our code only, so we won't overrun */
    lstrcpyW( szFullKey, szOID );
    lstrcatW( szFullKey, szKey );
    CRYPT_guid2wstr( guid, &szFullKey[ lstrlenW( szFullKey ) ] );

    r = RegDeleteKeyW(HKEY_LOCAL_MACHINE, szFullKey);

    return r;
}