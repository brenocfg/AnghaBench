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
struct TYPE_3__ {int x; int y; } ;
typedef  TYPE_1__ POINT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HIMAGELIST ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int HOTSPOTS_MAX ; 
#define  SIZEX1 129 
 int SIZEX2 ; 
#define  SIZEY1 128 
 int SIZEY2 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  createImageList (int const,int const) ; 
 int /*<<< orphan*/  create_window () ; 
 int max (int const,int const) ; 
 int /*<<< orphan*/  ok (int,char*,int,int,...) ; 
 int pImageList_BeginDrag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pImageList_Destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pImageList_EndDrag () ; 
 int /*<<< orphan*/  pImageList_GetDragImage (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pImageList_GetIconSize (int /*<<< orphan*/ ,int*,int*) ; 
 int pImageList_SetDragCursorImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  show_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static void test_hotspot(void)
{
    struct hotspot {
        int dx;
        int dy;
    };

#define SIZEX1 47
#define SIZEY1 31
#define SIZEX2 11
#define SIZEY2 17
#define HOTSPOTS_MAX 4       /* Number of entries in hotspots */
    static const struct hotspot hotspots[HOTSPOTS_MAX] = {
        { 10, 7 },
        { SIZEX1, SIZEY1 },
        { -9, -8 },
        { -7, 35 }
    };
    int i, j, ret;
    HIMAGELIST himl1 = createImageList(SIZEX1, SIZEY1);
    HIMAGELIST himl2 = createImageList(SIZEX2, SIZEY2);
    HWND hwnd = create_window();


    for (i = 0; i < HOTSPOTS_MAX; i++) {
        for (j = 0; j < HOTSPOTS_MAX; j++) {
            int dx1 = hotspots[i].dx;
            int dy1 = hotspots[i].dy;
            int dx2 = hotspots[j].dx;
            int dy2 = hotspots[j].dy;
            int correctx, correcty, newx, newy;
            char loc[256];
            HIMAGELIST himlNew;
            POINT ppt;

            ret = pImageList_BeginDrag(himl1, 0, dx1, dy1);
            ok(ret != 0, "BeginDrag failed for { %d, %d }\n", dx1, dy1);
            sprintf(loc, "BeginDrag (%d,%d)\n", i, j);
            show_image(hwnd, himl1, 0, max(SIZEX1, SIZEY1), loc, TRUE);

            /* check merging the dragged image with a second image */
            ret = pImageList_SetDragCursorImage(himl2, 0, dx2, dy2);
            ok(ret != 0, "SetDragCursorImage failed for {%d, %d}{%d, %d}\n",
                    dx1, dy1, dx2, dy2);
            sprintf(loc, "SetDragCursorImage (%d,%d)\n", i, j);
            show_image(hwnd, himl2, 0, max(SIZEX2, SIZEY2), loc, TRUE);

            /* check new hotspot, it should be the same like the old one */
            himlNew = pImageList_GetDragImage(NULL, &ppt);
            ok(ppt.x == dx1 && ppt.y == dy1,
                    "Expected drag hotspot [%d,%d] got [%d,%d]\n",
                    dx1, dy1, ppt.x, ppt.y);
            /* check size of new dragged image */
            pImageList_GetIconSize(himlNew, &newx, &newy);
            correctx = max(SIZEX1, max(SIZEX2 + dx2, SIZEX1 - dx2));
            correcty = max(SIZEY1, max(SIZEY2 + dy2, SIZEY1 - dy2));
            ok(newx == correctx && newy == correcty,
                    "Expected drag image size [%d,%d] got [%d,%d]\n",
                    correctx, correcty, newx, newy);
            sprintf(loc, "GetDragImage (%d,%d)\n", i, j);
            show_image(hwnd, himlNew, 0, max(correctx, correcty), loc, TRUE);
            pImageList_EndDrag();
        }
    }
#undef SIZEX1
#undef SIZEY1
#undef SIZEX2
#undef SIZEY2
#undef HOTSPOTS_MAX
    pImageList_Destroy(himl2);
    pImageList_Destroy(himl1);
    DestroyWindow(hwnd);
}