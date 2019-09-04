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
typedef  int /*<<< orphan*/  stbi ;

/* Variables and functions */
 int get16le (int /*<<< orphan*/ *) ; 
 int get8 (int /*<<< orphan*/ *) ; 
 int get8u (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stbi_rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tga_info(stbi *s, int *x, int *y, int *comp)
{
    int tga_w, tga_h, tga_comp;
    int sz;
    get8u(s);                   // discard Offset
    sz = get8u(s);              // color type
    if( sz > 1 ) {
        stbi_rewind(s);
        return 0;      // only RGB or indexed allowed
    }
    sz = get8u(s);              // image type
    // only RGB or grey allowed, +/- RLE
    if ((sz != 1) && (sz != 2) && (sz != 3) && (sz != 9) && (sz != 10) && (sz != 11)) return 0;
    skip(s,9);
    tga_w = get16le(s);
    if( tga_w < 1 ) {
        stbi_rewind(s);
        return 0;   // test width
    }
    tga_h = get16le(s);
    if( tga_h < 1 ) {
        stbi_rewind(s);
        return 0;   // test height
    }
    sz = get8(s);               // bits per pixel
    // only RGB or RGBA or grey allowed
    if ((sz != 8) && (sz != 16) && (sz != 24) && (sz != 32)) {
        stbi_rewind(s);
        return 0;
    }
    tga_comp = sz;
    if (x) *x = tga_w;
    if (y) *y = tga_h;
    if (comp) *comp = tga_comp / 8;
    return 1;                   // seems to have passed everything
}