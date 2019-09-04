#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  fill; } ;
struct TYPE_31__ {double height; TYPE_1__ cap; } ;
struct TYPE_26__ {int Count; int /*<<< orphan*/ * Types; int /*<<< orphan*/  Points; } ;
struct TYPE_30__ {scalar_t__ fill; TYPE_2__ pathdata; int /*<<< orphan*/  type; } ;
struct TYPE_29__ {int /*<<< orphan*/  hdc; } ;
struct TYPE_28__ {scalar_t__ lbHatch; int /*<<< orphan*/  lbColor; int /*<<< orphan*/  lbStyle; } ;
struct TYPE_27__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; scalar_t__ Y; scalar_t__ X; } ;
typedef  scalar_t__ REAL ;
typedef  TYPE_3__ PointF ;
typedef  TYPE_3__ POINT ;
typedef  TYPE_5__ LOGBRUSH ;
typedef  int INT ;
typedef  int /*<<< orphan*/ * HPEN ;
typedef  int /*<<< orphan*/ * HGDIOBJ ;
typedef  int /*<<< orphan*/ * HBRUSH ;
typedef  int /*<<< orphan*/  GpMatrix ;
typedef  int GpLineCap ;
typedef  TYPE_6__ GpGraphics ;
typedef  TYPE_7__ GpCustomLineCap ;
typedef  TYPE_8__ GpAdjustableArrowCap ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  TYPE_3__ BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 double ANCHOR_WIDTH ; 
 int /*<<< orphan*/  BS_SOLID ; 
 int /*<<< orphan*/  BeginPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoordinateSpaceWorld ; 
 int /*<<< orphan*/ * CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CustomLineCapTypeAdjustableArrow ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ellipse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EndPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ExtCreatePen (int,int,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipRotateMatrix (int /*<<< orphan*/ *,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipScaleMatrix (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetMatrixElements (int /*<<< orphan*/ *,double,double,double,double,double,double) ; 
 int /*<<< orphan*/  GdipTransformMatrixPoints (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  GdipTranslateMatrix (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
#define  LineCapArrowAnchor 136 
#define  LineCapCustom 135 
#define  LineCapDiamondAnchor 134 
#define  LineCapFlat 133 
 int LineCapNoAnchor ; 
#define  LineCapRound 132 
#define  LineCapRoundAnchor 131 
#define  LineCapSquare 130 
#define  LineCapSquareAnchor 129 
#define  LineCapTriangle 128 
 double M_PI ; 
 scalar_t__ M_PI_2 ; 
 scalar_t__ M_PI_4 ; 
 int /*<<< orphan*/  MatrixOrderAppend ; 
 int PS_ENDCAP_FLAT ; 
 int PS_GEOMETRIC ; 
 int PS_JOIN_MITER ; 
 int PS_SOLID ; 
 int /*<<< orphan*/  Pie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PolyDraw (int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  Polygon (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrokeAndFillPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WineCoordinateSpaceGdiDevice ; 
 TYPE_3__ convert_path_point_type (int /*<<< orphan*/ ) ; 
 scalar_t__ cos (scalar_t__) ; 
 int /*<<< orphan*/  gdip_transform_points (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 scalar_t__ gdiplus_atan2 (scalar_t__,scalar_t__) ; 
 TYPE_3__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  round_points (TYPE_3__*,TYPE_3__*,int) ; 
 scalar_t__ sin (scalar_t__) ; 
 scalar_t__ sqrt (double) ; 

__attribute__((used)) static void draw_cap(GpGraphics *graphics, COLORREF color, GpLineCap cap, REAL size,
    const GpCustomLineCap *custom, REAL x1, REAL y1, REAL x2, REAL y2)
{
    HGDIOBJ oldbrush = NULL, oldpen = NULL;
    GpMatrix matrix;
    HBRUSH brush = NULL;
    HPEN pen = NULL;
    PointF ptf[4], *custptf = NULL;
    POINT pt[4], *custpt = NULL;
    BYTE *tp = NULL;
    REAL theta, dsmall, dbig, dx, dy = 0.0;
    INT i, count;
    LOGBRUSH lb;
    BOOL customstroke;

    if((x1 == x2) && (y1 == y2))
        return;

    theta = gdiplus_atan2(y2 - y1, x2 - x1);

    customstroke = (cap == LineCapCustom) && custom && (!custom->fill);
    if(!customstroke){
        brush = CreateSolidBrush(color);
        lb.lbStyle = BS_SOLID;
        lb.lbColor = color;
        lb.lbHatch = 0;
        pen = ExtCreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT |
                           PS_JOIN_MITER, 1, &lb, 0,
                           NULL);
        oldbrush = SelectObject(graphics->hdc, brush);
        oldpen = SelectObject(graphics->hdc, pen);
    }

    switch(cap){
        case LineCapFlat:
            break;
        case LineCapSquare:
        case LineCapSquareAnchor:
        case LineCapDiamondAnchor:
            size = size * (cap & LineCapNoAnchor ? ANCHOR_WIDTH : 1.0) / 2.0;
            if(cap == LineCapDiamondAnchor){
                dsmall = cos(theta + M_PI_2) * size;
                dbig = sin(theta + M_PI_2) * size;
            }
            else{
                dsmall = cos(theta + M_PI_4) * size;
                dbig = sin(theta + M_PI_4) * size;
            }

            ptf[0].X = x2 - dsmall;
            ptf[1].X = x2 + dbig;

            ptf[0].Y = y2 - dbig;
            ptf[3].Y = y2 + dsmall;

            ptf[1].Y = y2 - dsmall;
            ptf[2].Y = y2 + dbig;

            ptf[3].X = x2 - dbig;
            ptf[2].X = x2 + dsmall;

            gdip_transform_points(graphics, WineCoordinateSpaceGdiDevice, CoordinateSpaceWorld, ptf, 4);

            round_points(pt, ptf, 4);

            Polygon(graphics->hdc, pt, 4);

            break;
        case LineCapArrowAnchor:
            size = size * 4.0 / sqrt(3.0);

            dx = cos(M_PI / 6.0 + theta) * size;
            dy = sin(M_PI / 6.0 + theta) * size;

            ptf[0].X = x2 - dx;
            ptf[0].Y = y2 - dy;

            dx = cos(- M_PI / 6.0 + theta) * size;
            dy = sin(- M_PI / 6.0 + theta) * size;

            ptf[1].X = x2 - dx;
            ptf[1].Y = y2 - dy;

            ptf[2].X = x2;
            ptf[2].Y = y2;

            gdip_transform_points(graphics, WineCoordinateSpaceGdiDevice, CoordinateSpaceWorld, ptf, 3);

            round_points(pt, ptf, 3);

            Polygon(graphics->hdc, pt, 3);

            break;
        case LineCapRoundAnchor:
            dx = dy = ANCHOR_WIDTH * size / 2.0;

            ptf[0].X = x2 - dx;
            ptf[0].Y = y2 - dy;
            ptf[1].X = x2 + dx;
            ptf[1].Y = y2 + dy;

            gdip_transform_points(graphics, WineCoordinateSpaceGdiDevice, CoordinateSpaceWorld, ptf, 2);

            round_points(pt, ptf, 2);

            Ellipse(graphics->hdc, pt[0].x, pt[0].y, pt[1].x, pt[1].y);

            break;
        case LineCapTriangle:
            size = size / 2.0;
            dx = cos(M_PI_2 + theta) * size;
            dy = sin(M_PI_2 + theta) * size;

            ptf[0].X = x2 - dx;
            ptf[0].Y = y2 - dy;
            ptf[1].X = x2 + dx;
            ptf[1].Y = y2 + dy;

            dx = cos(theta) * size;
            dy = sin(theta) * size;

            ptf[2].X = x2 + dx;
            ptf[2].Y = y2 + dy;

            gdip_transform_points(graphics, WineCoordinateSpaceGdiDevice, CoordinateSpaceWorld, ptf, 3);

            round_points(pt, ptf, 3);

            Polygon(graphics->hdc, pt, 3);

            break;
        case LineCapRound:
            dx = dy = size / 2.0;

            ptf[0].X = x2 - dx;
            ptf[0].Y = y2 - dy;
            ptf[1].X = x2 + dx;
            ptf[1].Y = y2 + dy;

            dx = -cos(M_PI_2 + theta) * size;
            dy = -sin(M_PI_2 + theta) * size;

            ptf[2].X = x2 - dx;
            ptf[2].Y = y2 - dy;
            ptf[3].X = x2 + dx;
            ptf[3].Y = y2 + dy;

            gdip_transform_points(graphics, WineCoordinateSpaceGdiDevice, CoordinateSpaceWorld, ptf, 4);

            round_points(pt, ptf, 4);

            Pie(graphics->hdc, pt[0].x, pt[0].y, pt[1].x, pt[1].y, pt[2].x,
                pt[2].y, pt[3].x, pt[3].y);

            break;
        case LineCapCustom:
            if(!custom)
                break;

            if (custom->type == CustomLineCapTypeAdjustableArrow)
            {
                GpAdjustableArrowCap *arrow = (GpAdjustableArrowCap *)custom;
                if (arrow->cap.fill && arrow->height <= 0.0)
                    break;
            }

            count = custom->pathdata.Count;
            custptf = heap_alloc_zero(count * sizeof(PointF));
            custpt = heap_alloc_zero(count * sizeof(POINT));
            tp = heap_alloc_zero(count);

            if(!custptf || !custpt || !tp)
                goto custend;

            memcpy(custptf, custom->pathdata.Points, count * sizeof(PointF));

            GdipSetMatrixElements(&matrix, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
            GdipScaleMatrix(&matrix, size, size, MatrixOrderAppend);
            GdipRotateMatrix(&matrix, (180.0 / M_PI) * (theta - M_PI_2),
                             MatrixOrderAppend);
            GdipTranslateMatrix(&matrix, x2, y2, MatrixOrderAppend);
            GdipTransformMatrixPoints(&matrix, custptf, count);

            gdip_transform_points(graphics, WineCoordinateSpaceGdiDevice, CoordinateSpaceWorld, custptf, count);

            round_points(custpt, custptf, count);

            for(i = 0; i < count; i++)
                tp[i] = convert_path_point_type(custom->pathdata.Types[i]);

            if(custom->fill){
                BeginPath(graphics->hdc);
                PolyDraw(graphics->hdc, custpt, tp, count);
                EndPath(graphics->hdc);
                StrokeAndFillPath(graphics->hdc);
            }
            else
                PolyDraw(graphics->hdc, custpt, tp, count);

custend:
            heap_free(custptf);
            heap_free(custpt);
            heap_free(tp);
            break;
        default:
            break;
    }

    if(!customstroke){
        SelectObject(graphics->hdc, oldbrush);
        SelectObject(graphics->hdc, oldpen);
        DeleteObject(brush);
        DeleteObject(pen);
    }
}