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
struct bitmap_data {int dummy; } ;
struct TYPE_3__ {int Width; int Height; scalar_t__ Y; scalar_t__ X; } ;
typedef  TYPE_1__ WICRect ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_WICTiffDecoder ; 
 int /*<<< orphan*/  CLSID_WICTiffEncoder ; 
 int /*<<< orphan*/  test_multi_encoder (struct bitmap_data const**,int /*<<< orphan*/ *,struct bitmap_data const**,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 struct bitmap_data testdata_24bppBGR ; 

__attribute__((used)) static void test_encoder_rects(void)
{
    const struct bitmap_data *srcs[2];
    const struct bitmap_data *dsts[2];
    WICRect rc;

    srcs[0] = &testdata_24bppBGR;
    srcs[1] = NULL;
    dsts[0] = &testdata_24bppBGR;
    dsts[1] = NULL;

    rc.X = 0;
    rc.Y = 0;
    rc.Width = 32;
    rc.Height = 2;

    test_multi_encoder(srcs, &CLSID_WICTiffEncoder, dsts, &CLSID_WICTiffDecoder, &rc, NULL, "test_encoder_rects full", NULL);

    rc.Width = 0;
    test_multi_encoder(srcs, &CLSID_WICTiffEncoder, dsts, &CLSID_WICTiffDecoder, &rc, NULL, "test_encoder_rects width=0", NULL);

    rc.Width = -1;
    test_multi_encoder(srcs, &CLSID_WICTiffEncoder, dsts, &CLSID_WICTiffDecoder, &rc, NULL, "test_encoder_rects width=-1", NULL);

    rc.Width = 32;
    rc.Height = 0;
    test_multi_encoder(srcs, &CLSID_WICTiffEncoder, dsts, &CLSID_WICTiffDecoder, &rc, NULL, "test_encoder_rects height=0", NULL);

    rc.Height = -1;
    test_multi_encoder(srcs, &CLSID_WICTiffEncoder, dsts, &CLSID_WICTiffDecoder, &rc, NULL, "test_encoder_rects height=-1", NULL);
}