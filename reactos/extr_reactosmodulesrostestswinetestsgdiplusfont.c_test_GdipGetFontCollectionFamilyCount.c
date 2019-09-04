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
typedef  int INT ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpFontCollection ;

/* Variables and functions */
 int GdipGetFontCollectionFamilyCount (int /*<<< orphan*/ *,int*) ; 
 int GdipNewInstalledFontCollection (int /*<<< orphan*/ **) ; 
 int InvalidParameter ; 
 int Ok ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_GdipGetFontCollectionFamilyCount(void)
{
    GpFontCollection *collection;
    GpStatus status;
    INT count;

    status = GdipGetFontCollectionFamilyCount(NULL, NULL);
    ok(status == InvalidParameter, "Unexpected status %d.\n", status);

    count = 123;
    status = GdipGetFontCollectionFamilyCount(NULL, &count);
    ok(status == InvalidParameter, "Unexpected status %d.\n", status);
    ok(count == 123, "Unexpected family count %d.\n", count);

    status = GdipNewInstalledFontCollection(&collection);
    ok(status == Ok, "Failed to get system collection, status %d.\n", status);

    status = GdipGetFontCollectionFamilyCount(collection, NULL);
    ok(status == InvalidParameter, "Unexpected status %d.\n", status);
}