#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct test_data   TYPE_1__ ;

/* Type definitions */
struct test_data {int /*<<< orphan*/  grey; int const cx; int const cy; int const cur; int const max; int const bpp; char const* comment; } ;
typedef  int const INT ;
typedef  int /*<<< orphan*/  HIMAGELIST ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__ const*) ; 
#define  BMP_CX 128 
 int const ILC_COLOR24 ; 
 int /*<<< orphan*/  check_iml_data (int /*<<< orphan*/ ,int const,int const,int const,int,int const,int const,char*) ; 
 int /*<<< orphan*/  image_list_add_bitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void image_list_init(HIMAGELIST himl, INT grow)
{
    unsigned int i;
    static const struct test_data
    {
        BYTE grey;
        INT cx, cy, cur, max, bpp;
        const char *comment;
    } td[] =
    {
        { 255, BMP_CX, BMP_CX, 1, 2, 24, "total 1" },
        { 170, BMP_CX, BMP_CX, 2, 7, 24, "total 2" },
        { 85, BMP_CX, BMP_CX, 3, 7, 24, "total 3" },
        { 0, BMP_CX, BMP_CX, 4, 7, 24, "total 4" },
        { 0, BMP_CX, BMP_CX, 5, 7, 24, "total 5" },
        { 85, BMP_CX, BMP_CX, 6, 7, 24, "total 6" },
        { 170, BMP_CX, BMP_CX, 7, 12, 24, "total 7" },
        { 255, BMP_CX, BMP_CX, 8, 12, 24, "total 8" },
        { 255, BMP_CX, BMP_CX, 9, 12, 24, "total 9" },
        { 170, BMP_CX, BMP_CX, 10, 12, 24, "total 10" },
        { 85, BMP_CX, BMP_CX, 11, 12, 24, "total 11" },
        { 0, BMP_CX, BMP_CX, 12, 17, 24, "total 12" },
        { 0, BMP_CX, BMP_CX, 13, 17, 24, "total 13" },
        { 85, BMP_CX, BMP_CX, 14, 17, 24, "total 14" },
        { 170, BMP_CX, BMP_CX, 15, 17, 24, "total 15" },
        { 255, BMP_CX, BMP_CX, 16, 17, 24, "total 16" },
        { 255, BMP_CX, BMP_CX, 17, 22, 24, "total 17" },
        { 170, BMP_CX, BMP_CX, 18, 22, 24, "total 18" },
        { 85, BMP_CX, BMP_CX, 19, 22, 24, "total 19" },
        { 0, BMP_CX, BMP_CX, 20, 22, 24, "total 20" },
        { 0, BMP_CX, BMP_CX, 21, 22, 24, "total 21" },
        { 85, BMP_CX, BMP_CX, 22, 27, 24, "total 22" },
        { 170, BMP_CX, BMP_CX, 23, 27, 24, "total 23" },
        { 255, BMP_CX, BMP_CX, 24, 27, 24, "total 24" }
    };

    check_iml_data(himl, BMP_CX, BMP_CX, 0, 2, grow, ILC_COLOR24, "total 0");

    for (i = 0; i < ARRAY_SIZE(td); i++)
    {
        image_list_add_bitmap(himl, td[i].grey, i + 1);
        check_iml_data(himl, td[i].cx, td[i].cy, td[i].cur, td[i].max, grow, td[i].bpp, td[i].comment);
    }
}