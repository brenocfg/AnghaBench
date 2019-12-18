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
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MsiRecordGetStringA (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL check_record( MSIHANDLE rec, UINT field, LPCSTR val )
{
    CHAR buffer[0x20];
    UINT r;
    DWORD sz;

    sz = sizeof buffer;
    r = MsiRecordGetStringA( rec, field, buffer, &sz );
    return (r == ERROR_SUCCESS ) && !strcmp(val, buffer);
}