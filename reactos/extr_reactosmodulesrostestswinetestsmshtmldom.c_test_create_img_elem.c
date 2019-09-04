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
typedef  int /*<<< orphan*/  IHTMLImgElement ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLImgElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_img_elem (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  test_img_put_height (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_img_put_width (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_create_img_elem(IHTMLDocument2 *doc)
{
    IHTMLImgElement *img;

    img = create_img_elem(doc, 10, 15);

    if(img){
        test_img_put_width(img, 5);
        test_img_put_height(img, 20);

        IHTMLImgElement_Release(img);
        img = NULL;
    }

    img = create_img_elem(doc, -1, -1);

    if(img){
        test_img_put_width(img, 5);
        test_img_put_height(img, 20);

        IHTMLImgElement_Release(img);
    }
}