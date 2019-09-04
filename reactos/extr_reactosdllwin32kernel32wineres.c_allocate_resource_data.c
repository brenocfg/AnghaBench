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
struct resource_data {int codepage; int cbData; struct resource_data* lpData; int /*<<< orphan*/  lang; } ;
typedef  int /*<<< orphan*/  WORD ;
typedef  struct resource_data* LPVOID ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct resource_data* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct resource_data*,struct resource_data*,int) ; 

__attribute__((used)) static struct resource_data *allocate_resource_data( WORD Language, DWORD codepage,
                                                     LPVOID lpData, DWORD cbData, BOOL copy_data )
{
    struct resource_data *resdata;

    if (!lpData || !cbData)
        return NULL;

    resdata = HeapAlloc( GetProcessHeap(), 0, sizeof *resdata + (copy_data ? cbData : 0) );
    if (resdata)
    {
        resdata->lang = Language;
        resdata->codepage = codepage;
        resdata->cbData = cbData;
        if (copy_data)
        {
            resdata->lpData = &resdata[1];
            memcpy( resdata->lpData, lpData, cbData );
        }
        else
            resdata->lpData = lpData;
    }

    return resdata;
}