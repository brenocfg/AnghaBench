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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/ * MSI_QueryGetRecord (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MSIRECORD *msi_get_binary_record( MSIDATABASE *db, LPCWSTR name )
{
    static const WCHAR query[] = {
        's','e','l','e','c','t',' ','*',' ',
        'f','r','o','m',' ','B','i','n','a','r','y',' ',
        'w','h','e','r','e',' ',
            '`','N','a','m','e','`',' ','=',' ','\'','%','s','\'',0
    };

    return MSI_QueryGetRecord( db, query, name );
}