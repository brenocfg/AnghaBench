#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sds ;
struct TYPE_4__ {int height; int width; } ;
typedef  TYPE_1__ lwCanvas ;

/* Variables and functions */
 scalar_t__ lwGetPixel (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  lwTranslatePixelsGroup (int,char*) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdsempty () ; 

__attribute__((used)) static sds renderCanvas(lwCanvas *canvas) {
    sds text = sdsempty();
    for (int y = 0; y < canvas->height; y += 4) {
        for (int x = 0; x < canvas->width; x += 2) {
            /* We need to emit groups of 8 bits according to a specific
             * arrangement. See lwTranslatePixelsGroup() for more info. */
            int byte = 0;
            if (lwGetPixel(canvas,x,y)) byte |= (1<<0);
            if (lwGetPixel(canvas,x,y+1)) byte |= (1<<1);
            if (lwGetPixel(canvas,x,y+2)) byte |= (1<<2);
            if (lwGetPixel(canvas,x+1,y)) byte |= (1<<3);
            if (lwGetPixel(canvas,x+1,y+1)) byte |= (1<<4);
            if (lwGetPixel(canvas,x+1,y+2)) byte |= (1<<5);
            if (lwGetPixel(canvas,x,y+3)) byte |= (1<<6);
            if (lwGetPixel(canvas,x+1,y+3)) byte |= (1<<7);
            char unicode[3];
            lwTranslatePixelsGroup(byte,unicode);
            text = sdscatlen(text,unicode,3);
        }
        if (y != canvas->height-1) text = sdscatlen(text,"\n",1);
    }
    return text;
}