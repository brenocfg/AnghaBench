#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xform ;
typedef  int /*<<< orphan*/  rectangle ;
struct TYPE_3__ {double member_0; double member_3; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ XFORM ;
struct TYPE_4__ {int member_2; int member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ RECTL ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpMetafile ;
typedef  int /*<<< orphan*/  EmfPlusRecordType ;

/* Variables and functions */
 int /*<<< orphan*/  EMR_RECTANGLE ; 
 int /*<<< orphan*/  EMR_SETWORLDTRANSFORM ; 
 int /*<<< orphan*/  GdipPlayMetafileRecord (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_gditransform_cb(GpMetafile* metafile, EmfPlusRecordType record_type,
    unsigned int flags, unsigned int dataSize, const unsigned char *pStr)
{
    static const XFORM xform = {0.5, 0, 0, 0.5, 0, 0};
    static const RECTL rectangle = {0,0,100,100};
    GpStatus stat;

    stat = GdipPlayMetafileRecord(metafile, EMR_SETWORLDTRANSFORM, 0, sizeof(xform), (void*)&xform);
    expect(Ok, stat);

    stat = GdipPlayMetafileRecord(metafile, EMR_RECTANGLE, 0, sizeof(rectangle), (void*)&rectangle);
    expect(Ok, stat);
}