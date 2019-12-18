#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int i_visible_lines; int i_visible_pitch; int i_pitch; int /*<<< orphan*/ * p_pixels; } ;
typedef  TYPE_1__ plane_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_8__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* emms ) () ;int /*<<< orphan*/  (* blend ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ;} ;
typedef  TYPE_3__ filter_sys_t ;

/* Variables and functions */
 int BANK_SIZE ; 
 int BLEND_SIZE ; 
 int /*<<< orphan*/  BlockBlend (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __MIN (int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub2 () ; 
 int urand (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void PlaneFilter(filter_t *filter,
                        plane_t *dst, const plane_t *src,
                        int16_t *bank, uint32_t *seed)
{
    filter_sys_t *sys = filter->p_sys;

    for (int y = 0; y < dst->i_visible_lines; y += BLEND_SIZE) {
        for (int x = 0; x < dst->i_visible_pitch; x += BLEND_SIZE) {
            int bx = urand(seed) % (BANK_SIZE - BLEND_SIZE + 1);
            int by = urand(seed) % (BANK_SIZE - BLEND_SIZE + 1);
            const int16_t *noise = &bank[by * BANK_SIZE + bx];

            int w  = dst->i_visible_pitch - x;
            int h  = dst->i_visible_lines - y;

            const uint8_t *srcp = &src->p_pixels[y * src->i_pitch + x];
            uint8_t       *dstp = &dst->p_pixels[y * dst->i_pitch + x];

            if (w >= BLEND_SIZE && h >= BLEND_SIZE)
                sys->blend(dstp, dst->i_pitch, srcp, src->i_pitch, noise);
            else
                BlockBlend(dstp, dst->i_pitch, srcp, src->i_pitch, noise,
                           __MIN(w, BLEND_SIZE), __MIN(h, BLEND_SIZE));
        }
    }
    if (sys->emms)
        sys->emms();
}