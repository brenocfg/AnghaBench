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
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpFontCollection ;

/* Variables and functions */
 int /*<<< orphan*/  GdipNewInstalledFontCollection (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_installedfonts (void)
{
    GpStatus stat;
    GpFontCollection* collection=NULL;

    stat = GdipNewInstalledFontCollection(NULL);
    expect (InvalidParameter, stat);

    stat = GdipNewInstalledFontCollection(&collection);
    expect (Ok, stat);
    ok (collection != NULL, "got NULL font collection\n");
}