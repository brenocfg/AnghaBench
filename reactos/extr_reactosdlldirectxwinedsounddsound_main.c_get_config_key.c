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
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ HKEY ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  RegQueryValueExA (scalar_t__,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline DWORD get_config_key( HKEY defkey, HKEY appkey, const char *name,
                                    char *buffer, DWORD size )
{
    if (appkey && !RegQueryValueExA( appkey, name, 0, NULL, (LPBYTE)buffer, &size )) return 0;
    if (defkey && !RegQueryValueExA( defkey, name, 0, NULL, (LPBYTE)buffer, &size )) return 0;
    return ERROR_FILE_NOT_FOUND;
}