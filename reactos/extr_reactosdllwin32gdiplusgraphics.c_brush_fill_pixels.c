#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_51__   TYPE_9__ ;
typedef  struct TYPE_50__   TYPE_8__ ;
typedef  struct TYPE_49__   TYPE_7__ ;
typedef  struct TYPE_48__   TYPE_6__ ;
typedef  struct TYPE_47__   TYPE_5__ ;
typedef  struct TYPE_46__   TYPE_4__ ;
typedef  struct TYPE_45__   TYPE_3__ ;
typedef  struct TYPE_44__   TYPE_2__ ;
typedef  struct TYPE_43__   TYPE_1__ ;
typedef  struct TYPE_42__   TYPE_15__ ;
typedef  struct TYPE_41__   TYPE_14__ ;
typedef  struct TYPE_40__   TYPE_13__ ;
typedef  struct TYPE_39__   TYPE_12__ ;
typedef  struct TYPE_38__   TYPE_11__ ;
typedef  struct TYPE_37__   TYPE_10__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_45__ {int Count; int* Types; TYPE_7__* Points; } ;
struct TYPE_51__ {TYPE_3__ pathdata; } ;
struct TYPE_49__ {int X; int Y; } ;
struct TYPE_44__ {double X; double Y; } ;
struct TYPE_50__ {void* centercolor; int /*<<< orphan*/  surroundcolorcount; void** surroundcolors; TYPE_7__ center; int /*<<< orphan*/  path; int /*<<< orphan*/  transform; int /*<<< orphan*/  pblendcount; int /*<<< orphan*/  blendcount; int /*<<< orphan*/  gamma; TYPE_2__ focus; } ;
struct TYPE_48__ {int Width; int Height; int X; int Y; } ;
struct TYPE_47__ {void* color; } ;
struct TYPE_46__ {int /*<<< orphan*/  imageattributes; int /*<<< orphan*/ * bitmap_bits; int /*<<< orphan*/  transform; TYPE_1__* image; } ;
struct TYPE_43__ {int /*<<< orphan*/  type; } ;
struct TYPE_42__ {int Width; int Height; int Stride; int /*<<< orphan*/  PixelFormat; int /*<<< orphan*/ * Scan0; } ;
struct TYPE_41__ {int width; int height; } ;
struct TYPE_40__ {int bt; } ;
struct TYPE_39__ {int /*<<< orphan*/  pixeloffset; int /*<<< orphan*/  interpolation; } ;
struct TYPE_38__ {void* backcol; void* forecol; int /*<<< orphan*/  hatchstyle; } ;
struct TYPE_37__ {int /*<<< orphan*/  transform; } ;
typedef  int REAL ;
typedef  int INT ;
typedef  TYPE_4__ GpTexture ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_5__ GpSolidFill ;
typedef  TYPE_6__ GpRect ;
typedef  TYPE_7__ GpPointF ;
typedef  TYPE_8__ GpPathGradient ;
typedef  TYPE_9__ GpPath ;
typedef  int /*<<< orphan*/  GpMatrix ;
typedef  TYPE_10__ GpLineGradient ;
typedef  TYPE_11__ GpHatch ;
typedef  TYPE_12__ GpGraphics ;
typedef  TYPE_13__ GpBrush ;
typedef  TYPE_14__ GpBitmap ;
typedef  void* DWORD ;
typedef  TYPE_15__ BitmapData ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  void* ARGB ;

/* Variables and functions */
#define  BrushTypeHatchFill 132 
#define  BrushTypeLinearGradient 131 
#define  BrushTypePathGradient 130 
#define  BrushTypeSolidColor 129 
#define  BrushTypeTextureFill 128 
 int /*<<< orphan*/  ColorAdjustTypeBitmap ; 
 int /*<<< orphan*/  CoordinateSpaceWorld ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GdipBitmapLockBits (TYPE_14__*,TYPE_6__*,int,int /*<<< orphan*/ ,TYPE_15__*) ; 
 int /*<<< orphan*/  GdipBitmapUnlockBits (TYPE_14__*,TYPE_15__*) ; 
 int /*<<< orphan*/  GdipClonePath (int /*<<< orphan*/ ,TYPE_9__**) ; 
 int /*<<< orphan*/  GdipDeletePath (TYPE_9__*) ; 
 int /*<<< orphan*/  GdipFlattenPath (TYPE_9__*,int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  GdipInvertMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipIsMatrixIdentity (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipTransformMatrixPoints (int /*<<< orphan*/ *,TYPE_7__*,int) ; 
 int /*<<< orphan*/  GdipTransformPath (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int ImageLockModeRead ; 
 int ImageLockModeUserInputBuf ; 
 int /*<<< orphan*/  ImageTypeBitmap ; 
 int /*<<< orphan*/  NotImplemented ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  OutOfMemory ; 
 int PathPointTypeCloseSubpath ; 
 int PathPointTypeLine ; 
 int PathPointTypePathTypeMask ; 
 int PathPointTypeStart ; 
 int /*<<< orphan*/  PixelFormat32bppARGB ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WineCoordinateSpaceGdiDevice ; 
 int /*<<< orphan*/  apply_image_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* blend_colors (void*,void*,int) ; 
 void* blend_line_gradient (TYPE_10__*,int) ; 
 int /*<<< orphan*/  ceil (int) ; 
 double fabs (int) ; 
 int /*<<< orphan*/  gdip_transform_points (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,int) ; 
 int /*<<< orphan*/  get_graphics_transform (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_hatch_data (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/ * heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int intersect_line_scanline (TYPE_7__*,TYPE_7__*,int) ; 
 size_t min (int,int /*<<< orphan*/ ) ; 
 void* resample_bitmap_pixel (TYPE_6__*,int /*<<< orphan*/ *,int,int,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static GpStatus brush_fill_pixels(GpGraphics *graphics, GpBrush *brush,
    DWORD *argb_pixels, GpRect *fill_area, UINT cdwStride)
{
    switch (brush->bt)
    {
    case BrushTypeSolidColor:
    {
        int x, y;
        GpSolidFill *fill = (GpSolidFill*)brush;
        for (x=0; x<fill_area->Width; x++)
            for (y=0; y<fill_area->Height; y++)
                argb_pixels[x + y*cdwStride] = fill->color;
        return Ok;
    }
    case BrushTypeHatchFill:
    {
        int x, y;
        GpHatch *fill = (GpHatch*)brush;
        const char *hatch_data;

        if (get_hatch_data(fill->hatchstyle, &hatch_data) != Ok)
            return NotImplemented;

        for (x=0; x<fill_area->Width; x++)
            for (y=0; y<fill_area->Height; y++)
            {
                int hx, hy;

                /* FIXME: Account for the rendering origin */
                hx = (x + fill_area->X) % 8;
                hy = (y + fill_area->Y) % 8;

                if ((hatch_data[7-hy] & (0x80 >> hx)) != 0)
                    argb_pixels[x + y*cdwStride] = fill->forecol;
                else
                    argb_pixels[x + y*cdwStride] = fill->backcol;
            }

        return Ok;
    }
    case BrushTypeLinearGradient:
    {
        GpLineGradient *fill = (GpLineGradient*)brush;
        GpPointF draw_points[3];
        GpStatus stat;
        int x, y;

        draw_points[0].X = fill_area->X;
        draw_points[0].Y = fill_area->Y;
        draw_points[1].X = fill_area->X+1;
        draw_points[1].Y = fill_area->Y;
        draw_points[2].X = fill_area->X;
        draw_points[2].Y = fill_area->Y+1;

        /* Transform the points to a co-ordinate space where X is the point's
         * position in the gradient, 0.0 being the start point and 1.0 the
         * end point. */
        stat = gdip_transform_points(graphics, CoordinateSpaceWorld,
            WineCoordinateSpaceGdiDevice, draw_points, 3);

        if (stat == Ok)
        {
            GpMatrix world_to_gradient = fill->transform;

            stat = GdipInvertMatrix(&world_to_gradient);
            if (stat == Ok)
                stat = GdipTransformMatrixPoints(&world_to_gradient, draw_points, 3);
        }

        if (stat == Ok)
        {
            REAL x_delta = draw_points[1].X - draw_points[0].X;
            REAL y_delta = draw_points[2].X - draw_points[0].X;

            for (y=0; y<fill_area->Height; y++)
            {
                for (x=0; x<fill_area->Width; x++)
                {
                    REAL pos = draw_points[0].X + x * x_delta + y * y_delta;

                    argb_pixels[x + y*cdwStride] = blend_line_gradient(fill, pos);
                }
            }
        }

        return stat;
    }
    case BrushTypeTextureFill:
    {
        GpTexture *fill = (GpTexture*)brush;
        GpPointF draw_points[3];
        GpStatus stat;
        int x, y;
        GpBitmap *bitmap;
        int src_stride;
        GpRect src_area;

        if (fill->image->type != ImageTypeBitmap)
        {
            FIXME("metafile texture brushes not implemented\n");
            return NotImplemented;
        }

        bitmap = (GpBitmap*)fill->image;
        src_stride = sizeof(ARGB) * bitmap->width;

        src_area.X = src_area.Y = 0;
        src_area.Width = bitmap->width;
        src_area.Height = bitmap->height;

        draw_points[0].X = fill_area->X;
        draw_points[0].Y = fill_area->Y;
        draw_points[1].X = fill_area->X+1;
        draw_points[1].Y = fill_area->Y;
        draw_points[2].X = fill_area->X;
        draw_points[2].Y = fill_area->Y+1;

        /* Transform the points to the co-ordinate space of the bitmap. */
        stat = gdip_transform_points(graphics, CoordinateSpaceWorld,
            WineCoordinateSpaceGdiDevice, draw_points, 3);

        if (stat == Ok)
        {
            GpMatrix world_to_texture = fill->transform;

            stat = GdipInvertMatrix(&world_to_texture);
            if (stat == Ok)
                stat = GdipTransformMatrixPoints(&world_to_texture, draw_points, 3);
        }

        if (stat == Ok && !fill->bitmap_bits)
        {
            BitmapData lockeddata;

            fill->bitmap_bits = heap_alloc_zero(sizeof(ARGB) * bitmap->width * bitmap->height);
            if (!fill->bitmap_bits)
                stat = OutOfMemory;

            if (stat == Ok)
            {
                lockeddata.Width = bitmap->width;
                lockeddata.Height = bitmap->height;
                lockeddata.Stride = src_stride;
                lockeddata.PixelFormat = PixelFormat32bppARGB;
                lockeddata.Scan0 = fill->bitmap_bits;

                stat = GdipBitmapLockBits(bitmap, &src_area, ImageLockModeRead|ImageLockModeUserInputBuf,
                    PixelFormat32bppARGB, &lockeddata);
            }

            if (stat == Ok)
                stat = GdipBitmapUnlockBits(bitmap, &lockeddata);

            if (stat == Ok)
                apply_image_attributes(fill->imageattributes, fill->bitmap_bits,
                    bitmap->width, bitmap->height,
                    src_stride, ColorAdjustTypeBitmap, lockeddata.PixelFormat);

            if (stat != Ok)
            {
                heap_free(fill->bitmap_bits);
                fill->bitmap_bits = NULL;
            }
        }

        if (stat == Ok)
        {
            REAL x_dx = draw_points[1].X - draw_points[0].X;
            REAL x_dy = draw_points[1].Y - draw_points[0].Y;
            REAL y_dx = draw_points[2].X - draw_points[0].X;
            REAL y_dy = draw_points[2].Y - draw_points[0].Y;

            for (y=0; y<fill_area->Height; y++)
            {
                for (x=0; x<fill_area->Width; x++)
                {
                    GpPointF point;
                    point.X = draw_points[0].X + x * x_dx + y * y_dx;
                    point.Y = draw_points[0].Y + y * x_dy + y * y_dy;

                    argb_pixels[x + y*cdwStride] = resample_bitmap_pixel(
                        &src_area, fill->bitmap_bits, bitmap->width, bitmap->height,
                        &point, fill->imageattributes, graphics->interpolation,
                        graphics->pixeloffset);
                }
            }
        }

        return stat;
    }
    case BrushTypePathGradient:
    {
        GpPathGradient *fill = (GpPathGradient*)brush;
        GpPath *flat_path;
        GpMatrix world_to_device;
        GpStatus stat;
        int i, figure_start=0;
        GpPointF start_point, end_point, center_point;
        BYTE type;
        REAL min_yf, max_yf, line1_xf, line2_xf;
        INT min_y, max_y, min_x, max_x;
        INT x, y;
        ARGB outer_color;
        static BOOL transform_fixme_once;

        if (fill->focus.X != 0.0 || fill->focus.Y != 0.0)
        {
            static int once;
            if (!once++)
                FIXME("path gradient focus not implemented\n");
        }

        if (fill->gamma)
        {
            static int once;
            if (!once++)
                FIXME("path gradient gamma correction not implemented\n");
        }

        if (fill->blendcount)
        {
            static int once;
            if (!once++)
                FIXME("path gradient blend not implemented\n");
        }

        if (fill->pblendcount)
        {
            static int once;
            if (!once++)
                FIXME("path gradient preset blend not implemented\n");
        }

        if (!transform_fixme_once)
        {
            BOOL is_identity=TRUE;
            GdipIsMatrixIdentity(&fill->transform, &is_identity);
            if (!is_identity)
            {
                FIXME("path gradient transform not implemented\n");
                transform_fixme_once = TRUE;
            }
        }

        stat = GdipClonePath(fill->path, &flat_path);

        if (stat != Ok)
            return stat;

        stat = get_graphics_transform(graphics, WineCoordinateSpaceGdiDevice,
            CoordinateSpaceWorld, &world_to_device);
        if (stat == Ok)
        {
            stat = GdipTransformPath(flat_path, &world_to_device);

            if (stat == Ok)
            {
                center_point = fill->center;
                stat = GdipTransformMatrixPoints(&world_to_device, &center_point, 1);
            }

            if (stat == Ok)
                stat = GdipFlattenPath(flat_path, NULL, 0.5);
        }

        if (stat != Ok)
        {
            GdipDeletePath(flat_path);
            return stat;
        }

        for (i=0; i<flat_path->pathdata.Count; i++)
        {
            int start_center_line=0, end_center_line=0;
            BOOL seen_start = FALSE, seen_end = FALSE, seen_center = FALSE;
            REAL center_distance;
            ARGB start_color, end_color;
            REAL dy, dx;

            type = flat_path->pathdata.Types[i];

            if ((type&PathPointTypePathTypeMask) == PathPointTypeStart)
                figure_start = i;

            start_point = flat_path->pathdata.Points[i];

            start_color = fill->surroundcolors[min(i, fill->surroundcolorcount-1)];

            if ((type&PathPointTypeCloseSubpath) == PathPointTypeCloseSubpath || i+1 >= flat_path->pathdata.Count)
            {
                end_point = flat_path->pathdata.Points[figure_start];
                end_color = fill->surroundcolors[min(figure_start, fill->surroundcolorcount-1)];
            }
            else if ((flat_path->pathdata.Types[i+1] & PathPointTypePathTypeMask) == PathPointTypeLine)
            {
                end_point = flat_path->pathdata.Points[i+1];
                end_color = fill->surroundcolors[min(i+1, fill->surroundcolorcount-1)];
            }
            else
                continue;

            outer_color = start_color;

            min_yf = center_point.Y;
            if (min_yf > start_point.Y) min_yf = start_point.Y;
            if (min_yf > end_point.Y) min_yf = end_point.Y;

            if (min_yf < fill_area->Y)
                min_y = fill_area->Y;
            else
                min_y = (INT)ceil(min_yf);

            max_yf = center_point.Y;
            if (max_yf < start_point.Y) max_yf = start_point.Y;
            if (max_yf < end_point.Y) max_yf = end_point.Y;

            if (max_yf > fill_area->Y + fill_area->Height)
                max_y = fill_area->Y + fill_area->Height;
            else
                max_y = (INT)ceil(max_yf);

            dy = end_point.Y - start_point.Y;
            dx = end_point.X - start_point.X;

            /* This is proportional to the distance from start-end line to center point. */
            center_distance = dy * (start_point.X - center_point.X) +
                dx * (center_point.Y - start_point.Y);

            for (y=min_y; y<max_y; y++)
            {
                REAL yf = (REAL)y;

                if (!seen_start && yf >= start_point.Y)
                {
                    seen_start = TRUE;
                    start_center_line ^= 1;
                }
                if (!seen_end && yf >= end_point.Y)
                {
                    seen_end = TRUE;
                    end_center_line ^= 1;
                }
                if (!seen_center && yf >= center_point.Y)
                {
                    seen_center = TRUE;
                    start_center_line ^= 1;
                    end_center_line ^= 1;
                }

                if (start_center_line)
                    line1_xf = intersect_line_scanline(&start_point, &center_point, yf);
                else
                    line1_xf = intersect_line_scanline(&start_point, &end_point, yf);

                if (end_center_line)
                    line2_xf = intersect_line_scanline(&end_point, &center_point, yf);
                else
                    line2_xf = intersect_line_scanline(&start_point, &end_point, yf);

                if (line1_xf < line2_xf)
                {
                    min_x = (INT)ceil(line1_xf);
                    max_x = (INT)ceil(line2_xf);
                }
                else
                {
                    min_x = (INT)ceil(line2_xf);
                    max_x = (INT)ceil(line1_xf);
                }

                if (min_x < fill_area->X)
                    min_x = fill_area->X;
                if (max_x > fill_area->X + fill_area->Width)
                    max_x = fill_area->X + fill_area->Width;

                for (x=min_x; x<max_x; x++)
                {
                    REAL xf = (REAL)x;
                    REAL distance;

                    if (start_color != end_color)
                    {
                        REAL blend_amount, pdy, pdx;
                        pdy = yf - center_point.Y;
                        pdx = xf - center_point.X;

                        if (fabs(pdx) <= 0.001 && fabs(pdy) <= 0.001)
                        {
                            /* Too close to center point, don't try to calculate outer color */
                            outer_color = start_color;
                        }
                        else
                        {
                            blend_amount = ( (center_point.Y - start_point.Y) * pdx + (start_point.X - center_point.X) * pdy ) / ( dy * pdx - dx * pdy );
                            outer_color = blend_colors(start_color, end_color, blend_amount);
                        }
                    }

                    distance = (end_point.Y - start_point.Y) * (start_point.X - xf) +
                        (end_point.X - start_point.X) * (yf - start_point.Y);

                    distance = distance / center_distance;

                    argb_pixels[(x-fill_area->X) + (y-fill_area->Y)*cdwStride] =
                        blend_colors(outer_color, fill->centercolor, distance);
                }
            }
        }

        GdipDeletePath(flat_path);
        return stat;
    }
    default:
        return NotImplemented;
    }
}