#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  TYPE_2__ MSIQUERY ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 scalar_t__ MSI_OpenQuery (int /*<<< orphan*/ *,TYPE_2__**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MSI_ViewExecute (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ MSI_ViewFetch (TYPE_2__*,TYPE_1__**) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL check_column_exists(MSIDATABASE *db, LPCWSTR table, LPCWSTR column)
{
    MSIQUERY *view;
    MSIRECORD *rec;
    UINT r;

    static const WCHAR query[] = {
        'S','E','L','E','C','T',' ','*',' ','F','R','O','M',' ',
        '`','_','C','o','l','u','m','n','s','`',' ','W','H','E','R','E',' ',
        '`','T','a','b','l','e','`','=','\'','%','s','\'',' ','A','N','D',' ',
        '`','N','a','m','e','`','=','\'','%','s','\'',0
    };

    r = MSI_OpenQuery(db, &view, query, table, column);
    if (r != ERROR_SUCCESS)
        return FALSE;

    r = MSI_ViewExecute(view, NULL);
    if (r != ERROR_SUCCESS)
        goto done;

    r = MSI_ViewFetch(view, &rec);
    if (r == ERROR_SUCCESS)
        msiobj_release(&rec->hdr);

done:
    msiobj_release(&view->hdr);
    return (r == ERROR_SUCCESS);
}