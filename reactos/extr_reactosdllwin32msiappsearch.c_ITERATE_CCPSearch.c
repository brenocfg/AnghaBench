#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  MSISIGNATURE ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  TYPE_1__* LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_AppSearchSigName (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ACTION_FreeSignature (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_NO_MORE_ITEMS ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_set_property (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  szOne ; 

__attribute__((used)) static UINT ITERATE_CCPSearch(MSIRECORD *row, LPVOID param)
{
    MSIPACKAGE *package = param;
    LPCWSTR signature;
    LPWSTR value = NULL;
    MSISIGNATURE sig;
    UINT r = ERROR_SUCCESS;

    static const WCHAR success[] = {'C','C','P','_','S','u','c','c','e','s','s',0};

    signature = MSI_RecordGetString(row, 1);

    TRACE("%s\n", debugstr_w(signature));

    ACTION_AppSearchSigName(package, signature, &sig, &value);
    if (value)
    {
        TRACE("Found signature %s\n", debugstr_w(signature));
        msi_set_property( package->db, success, szOne, -1 );
        msi_free(value);
        r = ERROR_NO_MORE_ITEMS;
    }

    ACTION_FreeSignature(&sig);

    return r;
}