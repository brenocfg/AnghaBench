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
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  IHTMLImgElement ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IHTMLImgElement_put_width (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  _test_img_width (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void _test_img_put_width(unsigned line, IHTMLImgElement *img, const LONG width)
{
    HRESULT hres;

    hres = IHTMLImgElement_put_width(img, width);
    ok(hres == S_OK, "put_width failed: %08x\n", hres);

    _test_img_width(line, img, width);
}