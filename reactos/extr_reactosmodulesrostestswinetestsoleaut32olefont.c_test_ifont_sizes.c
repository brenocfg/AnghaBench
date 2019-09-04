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
typedef  int LONG ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*,int) ; 
 int /*<<< orphan*/  test_ifont_size (int,int,int,int,char*) ; 

__attribute__((used)) static void test_ifont_sizes(void)
{
  /* Test various size operations and conversions. */
  /* Add more as needed. */

  /* Results of first 2 tests depend on display resolution. */
  HDC hdc = GetDC(0);
  LONG dpi = GetDeviceCaps(hdc, LOGPIXELSY); /* expected results depend on display DPI */
  ReleaseDC(0, hdc);
  if(dpi == 96) /* normal resolution display */
  {
    test_ifont_size(180000, 0, 0, -24, "default");     /* normal font */
    test_ifont_size(186000, 0, 0, -25, "rounding");    /* test rounding */
  } else if(dpi == 72) /* low resolution display */
  {
    test_ifont_size(180000, 0, 0, -18, "default");     /* normal font */
    test_ifont_size(186000, 0, 0, -19, "rounding");    /* test rounding */
  } else if(dpi == 120) /* high resolution display */
  {
    test_ifont_size(180000, 0, 0, -30, "default");     /* normal font */
    test_ifont_size(186000, 0, 0, -31, "rounding");    /* test rounding */
  } else
    skip("Skipping resolution dependent font size tests - display resolution is %d\n", dpi);

  /* Next 4 tests specify a scaling ratio, so display resolution is not a factor. */
    test_ifont_size(180000, 72,  2540, -18, "ratio1");  /* change ratio */
    test_ifont_size(180000, 144, 2540, -36, "ratio2");  /* another ratio */
    test_ifont_size(180000, 72,  1270, -36, "ratio3");  /* yet another ratio */
    test_ifont_size(186000, 72,  2540, -19, "rounding+ratio"); /* test rounding with ratio */

    /* test various combinations of logical == himetric */
    test_ifont_size(180000, 10, 10, -635, "identical ratio 1");
    test_ifont_size(240000, 10, 10, -848, "identical ratio 2");
    test_ifont_size(300000, 10, 10, -1058, "identical ratio 3");

    /* test various combinations of logical and himetric both set to 1 */
    test_ifont_size(180000, 1, 1, -24, "1:1 ratio 1");
    test_ifont_size(240000, 1, 1, -32, "1:1 ratio 2");
    test_ifont_size(300000, 1, 1, -40, "1:1 ratio 3");

    /* test various combinations of logical set to 1 */
    test_ifont_size(180000, 1, 0, -24, "1:0 ratio 1");
    test_ifont_size(240000, 1, 0, -32, "1:0 ratio 2");
    test_ifont_size(300000, 1, 0, -40, "1:0 ratio 3");

    /* test various combinations of himetric set to 1 */
    test_ifont_size(180000, 0, 1, -24, "0:1 ratio 1");
    test_ifont_size(240000, 0, 1, -32, "0:1 ratio 2");
    test_ifont_size(300000, 0, 1, -40, "0:1 ratio 3");

    /* test various combinations of 2:1 logical:himetric */
    test_ifont_size(180000, 2, 1, -1270, "2:1 ratio 1");
    test_ifont_size(240000, 2, 1, -1694, "2:1 ratio 2");
    test_ifont_size(300000, 2, 1, -2117, "2:1 ratio 3");

    /* test various combinations of 1:2 logical:himetric */
    test_ifont_size(180000, 1, 2, -318, "1:2 ratio 1");
    test_ifont_size(240000, 1, 2, -424, "1:2 ratio 2");
    test_ifont_size(300000, 1, 2, -529, "1:2 ratio 3");

    /* test various combinations of logical and himetric both set to 2 */
    test_ifont_size(180000, 2, 2, -635, "2:2 ratio 1");
    test_ifont_size(240000, 2, 2, -848, "2:2 ratio 2");
    test_ifont_size(300000, 2, 2, -1058, "2:2 ratio 3");
}