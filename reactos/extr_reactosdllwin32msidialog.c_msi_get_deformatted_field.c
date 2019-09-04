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
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  scalar_t__ LPCWSTR ;

/* Variables and functions */
 scalar_t__ MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  deformat_string (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ **) ; 

__attribute__((used)) static LPWSTR msi_get_deformatted_field( MSIPACKAGE *package, MSIRECORD *rec, int field )
{
    LPCWSTR str = MSI_RecordGetString( rec, field );
    LPWSTR ret = NULL;

    if (str)
        deformat_string( package, str, &ret );
    return ret;
}