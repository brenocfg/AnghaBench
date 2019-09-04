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
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpFontFamily ;
typedef  int /*<<< orphan*/  GpFontCollection ;

/* Variables and functions */
 int /*<<< orphan*/  GdipDeleteFontFamily (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetFontCollectionFamilyCount (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipGetFontCollectionFamilyList (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  GdipNewInstalledFontCollection (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_GdipGetFontCollectionFamilyList(void)
{
    GpFontFamily *family, *family2;
    GpFontCollection *collection;
    INT found, count;
    GpStatus status;

    status = GdipNewInstalledFontCollection(&collection);
    ok(status == Ok, "Failed to get system collection, status %d.\n", status);

    count = 0;
    status = GdipGetFontCollectionFamilyCount(collection, &count);
    ok(status == Ok, "Failed to get family count, status %d.\n", status);
    ok(count > 0, "Unexpected empty collection.\n");

    status = GdipGetFontCollectionFamilyList(NULL, 0, NULL, NULL);
    ok(status == InvalidParameter, "Unexpected status %d.\n", status);

    found = 123;
    status = GdipGetFontCollectionFamilyList(NULL, 0, NULL, &found);
    ok(status == InvalidParameter, "Unexpected status %d.\n", status);
    ok(found == 123, "Unexpected list count %d.\n", found);

    status = GdipGetFontCollectionFamilyList(collection, 0, NULL, NULL);
    ok(status == InvalidParameter, "Unexpected status %d.\n", status);

    found = 123;
    status = GdipGetFontCollectionFamilyList(collection, 0, NULL, &found);
    ok(status == InvalidParameter, "Unexpected status %d.\n", status);
    ok(found == 123, "Unexpected list count %d.\n", found);

    found = 123;
    status = GdipGetFontCollectionFamilyList(collection, 1, NULL, &found);
    ok(status == InvalidParameter, "Unexpected status %d.\n", status);
    ok(found == 123, "Unexpected list count %d.\n", found);

    family = NULL;
    found = 0;
    status = GdipGetFontCollectionFamilyList(collection, 1, &family, &found);
    ok(status == Ok, "Failed to get family list, status %d.\n", status);
    ok(found == 1, "Unexpected list count %d.\n", found);
    ok(family != NULL, "Expected family instance.\n");

    family = NULL;
    found = 0;
    status = GdipGetFontCollectionFamilyList(collection, 1, &family2, &found);
    ok(status == Ok, "Failed to get family list, status %d.\n", status);
    ok(found == 1, "Unexpected list count %d.\n", found);
    ok(family2 != family, "Unexpected family instance.\n");

    GdipDeleteFontFamily(family);
    GdipDeleteFontFamily(family2);
}