#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtest ;
struct TYPE_2__ {int member_0; int member_1; int member_2; int member_3; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
#define  FALSE 131 
 scalar_t__ IsRectEmpty (int /*<<< orphan*/ *) ; 
#define  MAXLONG 130 
#define  MINLONG 129 
#define  TRUE 128 
 int /*<<< orphan*/  ok (int,char*,unsigned int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_IsRectEmpty(void)
{
    BOOL ret;
    unsigned int i;
    static const struct {
        RECT rect;
        BOOL ret;
    } rtest[] = {
        {{0, 0, 0, 0}, TRUE},
        {{127, 131, 127, 131}, TRUE},
        {{MAXLONG, MAXLONG, MAXLONG, MAXLONG}, TRUE},
        {{-1, -1, -1, -1}, TRUE},
        {{-2011, -2017, -2011, -2017}, TRUE},
        {{MINLONG, MINLONG, MINLONG, MINLONG}, TRUE},
        /* Only width or height are 0 */
        {{31, 37, 31, 41}, TRUE},
        {{881, 883, 887, 883}, TRUE},
        {{-1721, 1723, -1721, 7213}, TRUE},
        /* Negative width and/or height */
        {{11, 13, 5, 7}, TRUE},
        {{-11, -13, -19, -23}, TRUE},
        {{11, 13, -17, 19}, TRUE},
        {{11, 13, 17, 11}, TRUE},
        /* Non empty rects */
        {{101, 103, 107, 109}, FALSE},
        {{1, -9, 7, 3}, FALSE},
        {{-109, -107, -103, -101}, FALSE},
    };

    for (i = 0; i < sizeof(rtest)/sizeof(rtest[0]); i++) {
        ret = IsRectEmpty(&rtest[i].rect);
        ok(ret == rtest[i].ret, "Test %d: IsRectEmpty returned %s for %s\n", i,
           ret ? "TRUE" : "FALSE", wine_dbgstr_rect(&rtest[i].rect));
    }
}