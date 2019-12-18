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
typedef  int UINT ;
struct TYPE_5__ {int /*<<< orphan*/  FormatDescription; } ;
typedef  TYPE_1__ ImageCodecInfo ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ CSTR_EQUAL ; 
 scalar_t__ CompareStringA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char const*,int) ; 
 int FALSE ; 
 TYPE_1__* GdipAlloc (int) ; 
 int /*<<< orphan*/  GdipFree (TYPE_1__*) ; 
 int /*<<< orphan*/  GdipGetImageEncoders (int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  GdipGetImageEncodersSize (int*,int*) ; 
 int /*<<< orphan*/  GenericError ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 int /*<<< orphan*/  Ok ; 
 int TRUE ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_encoders(void)
{
    GpStatus stat;
    UINT n;
    UINT s;
    ImageCodecInfo *codecs;
    int i;
    int bmp_found;

    static const CHAR bmp_format[] = "BMP";

    stat = GdipGetImageEncodersSize(&n, &s);
    expect(stat, Ok);

    codecs = GdipAlloc(s);
    if (!codecs)
        return;

    stat = GdipGetImageEncoders(n, s, NULL);
    expect(GenericError, stat);

    stat = GdipGetImageEncoders(0, s, codecs);
    expect(GenericError, stat);

    stat = GdipGetImageEncoders(n, s-1, codecs);
    expect(GenericError, stat);

    stat = GdipGetImageEncoders(n, s+1, codecs);
    expect(GenericError, stat);

    stat = GdipGetImageEncoders(n, s, codecs);
    expect(stat, Ok);

    bmp_found = FALSE;
    for (i = 0; i < n; i++)
        {
            CHAR desc[32];

            WideCharToMultiByte(CP_ACP, 0, codecs[i].FormatDescription, -1,
                                desc, 32, 0, 0);

            if (CompareStringA(LOCALE_SYSTEM_DEFAULT, 0,
                               desc, -1,
                               bmp_format, -1) == CSTR_EQUAL) {
                bmp_found = TRUE;
                break;
            }
        }
    if (!bmp_found)
        ok(FALSE, "No BMP codec found.\n");

    GdipFree(codecs);
}