#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {scalar_t__ height; int /*<<< orphan*/  width; } ;
struct TYPE_24__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_30__ {TYPE_4__ size; TYPE_3__ origin; } ;
struct TYPE_26__ {int offscreen_bitmap_size; int /*<<< orphan*/ * offscreen_bitmap; scalar_t__ offscreen_context; TYPE_9__ offscreen_rect; int /*<<< orphan*/  display_id; scalar_t__ height; int /*<<< orphan*/  width; scalar_t__ screen_top; scalar_t__ screen_left; } ;
typedef  TYPE_5__ screen_data_t ;
struct TYPE_27__ {TYPE_7__* p_sys; } ;
typedef  TYPE_6__ demux_t ;
struct TYPE_22__ {int i_width; int i_height; } ;
struct TYPE_23__ {TYPE_1__ video; } ;
struct TYPE_28__ {scalar_t__ i_top; scalar_t__ i_left; TYPE_2__ fmt; scalar_t__ b_follow_mouse; scalar_t__ p_data; } ;
typedef  TYPE_7__ demux_sys_t ;
struct TYPE_29__ {int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_8__ block_t ;
struct TYPE_21__ {scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_9__ CGRect ;
typedef  TYPE_10__ CGPoint ;
typedef  int /*<<< orphan*/  CGImageRef ;
typedef  int /*<<< orphan*/  CGEventRef ;
typedef  int /*<<< orphan*/  CGColorSpaceRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 scalar_t__ CGBitmapContextCreate (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CGColorSpaceCreateWithName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGColorSpaceRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGContextDrawImage (scalar_t__,TYPE_9__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGDisplayCreateImageForRect (int /*<<< orphan*/ ,TYPE_9__) ; 
 int /*<<< orphan*/  CGEventCreate (int /*<<< orphan*/ *) ; 
 TYPE_10__ CGEventGetLocation (int /*<<< orphan*/ ) ; 
 scalar_t__ CGImageGetHeight (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGImageGetWidth (int /*<<< orphan*/ ) ; 
 TYPE_9__ CGRectMake (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CGSCreateRegisteredCursorImage (int,char*,TYPE_10__*) ; 
 int CGSMainConnectionID () ; 
 int /*<<< orphan*/  FollowMouse (TYPE_7__*,scalar_t__,scalar_t__) ; 
 TYPE_8__* block_Alloc (int) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int kCGBitmapByteOrder32Little ; 
 int /*<<< orphan*/  kCGColorSpaceGenericRGB ; 
 int kCGImageAlphaPremultipliedFirst ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_6__*,char*) ; 

block_t *screen_Capture(demux_t *p_demux)
{
    demux_sys_t *p_sys = p_demux->p_sys;
    screen_data_t *p_data = (screen_data_t *)p_sys->p_data;
    block_t *p_block;
    CGRect capture_rect;
    CGImageRef image;

    /* forward cursor location */
    CGPoint cursor_pos;

    CGEventRef event = CGEventCreate(NULL);
    cursor_pos = CGEventGetLocation(event);
    CFRelease(event);

    cursor_pos.x -= p_data->screen_left;
    cursor_pos.y -= p_data->screen_top;

    if (p_sys->b_follow_mouse)
        FollowMouse(p_sys, cursor_pos.x, cursor_pos.y);

    capture_rect.origin.x = p_sys->i_left;
    capture_rect.origin.y = p_sys->i_top;
    capture_rect.size.width = p_data->width;
    capture_rect.size.height = p_data->height;

    /* fetch image data */
    image = CGDisplayCreateImageForRect(p_data->display_id, capture_rect);
    if (!image) {
        msg_Warn(p_demux, "no image!");
        return NULL;
    }

    /* create offscreen context */
    if (!p_data->offscreen_context) {
        CGColorSpaceRef colorspace;

        colorspace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);

        p_data->offscreen_bitmap_size = p_sys->fmt.video.i_width * p_sys->fmt.video.i_height * 4;
        p_data->offscreen_bitmap = calloc(1, p_data->offscreen_bitmap_size);
        if (p_data->offscreen_bitmap == NULL) {
            msg_Warn(p_demux, "can't allocate offscreen bitmap");
            CFRelease(image);
            return NULL;
        }

        p_data->offscreen_context = CGBitmapContextCreate(p_data->offscreen_bitmap, p_sys->fmt.video.i_width, p_sys->fmt.video.i_height, 8, p_sys->fmt.video.i_width * 4, colorspace, kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Little);
        if (!p_data->offscreen_context) {
            msg_Warn(p_demux, "can't create offscreen bitmap context");
            CFRelease(image);
            return NULL;
        }

        CGColorSpaceRelease(colorspace);

        p_data->offscreen_rect = CGRectMake(0, 0, p_sys->fmt.video.i_width, p_sys->fmt.video.i_height);
    }

    /* fetch cursor image */
    CGImageRef cursor_image;
    int cid = CGSMainConnectionID();
    CGPoint outHotSpot;
    cursor_image = CGSCreateRegisteredCursorImage(cid, (char *)"com.apple.coregraphics.GlobalCurrent", &outHotSpot);

    /* draw screen image and cursor image */
    CGRect cursor_rect;
    cursor_rect.size.width = CGImageGetWidth(cursor_image);
    cursor_rect.size.height = CGImageGetHeight(cursor_image);
    cursor_rect.origin.x = cursor_pos.x - p_sys->i_left - outHotSpot.x;
    cursor_rect.origin.y = p_data->offscreen_rect.size.height
        - (cursor_pos.y + cursor_rect.size.height - p_sys->i_top - outHotSpot.y);

    CGContextDrawImage(p_data->offscreen_context, p_data->offscreen_rect, image);
    CGContextDrawImage(p_data->offscreen_context, cursor_rect, cursor_image);

    /* build block */
    p_block = block_Alloc(p_data->offscreen_bitmap_size);
    if (!p_block) {
        msg_Warn(p_demux, "can't get block");
        CFRelease(image);
        return NULL;
    }

    memmove(p_block->p_buffer, p_data->offscreen_bitmap, p_data->offscreen_bitmap_size);

    CFRelease(image);

    return p_block;
}