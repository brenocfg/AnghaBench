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
typedef  size_t UINT ;
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  MSISUMMARYINFO ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  int /*<<< orphan*/ **** LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 size_t ERROR_FUNCTION_FAILED ; 
 size_t ERROR_SUCCESS ; 
 int /*<<< orphan*/  PID_TEMPLATE ; 
 int /*<<< orphan*/ ****** msi_dup_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ ****) ; 
 int /*<<< orphan*/ ******* msi_split_string (int /*<<< orphan*/ ****,char) ; 
 int /*<<< orphan*/ ****** msi_suminfo_dup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/ ****,int /*<<< orphan*/ ****) ; 
 int /*<<< orphan*/  szProductCode ; 

UINT msi_check_patch_applicable( MSIPACKAGE *package, MSISUMMARYINFO *si )
{
    LPWSTR guid_list, *guids, product_code;
    UINT i, ret = ERROR_FUNCTION_FAILED;

    product_code = msi_dup_property( package->db, szProductCode );
    if (!product_code)
    {
        /* FIXME: the property ProductCode should be written into the DB somewhere */
        ERR("no product code to check\n");
        return ERROR_SUCCESS;
    }
    guid_list = msi_suminfo_dup_string( si, PID_TEMPLATE );
    guids = msi_split_string( guid_list, ';' );
    for (i = 0; guids[i] && ret != ERROR_SUCCESS; i++)
    {
        if (!strcmpW( guids[i], product_code )) ret = ERROR_SUCCESS;
    }
    msi_free( guids );
    msi_free( guid_list );
    msi_free( product_code );
    return ret;
}