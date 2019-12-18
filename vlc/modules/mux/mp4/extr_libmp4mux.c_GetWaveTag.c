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
typedef  int /*<<< orphan*/  mp4mux_trackinfo_t ;
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 int /*<<< orphan*/ * GetESDS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bo_add_32be (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_fourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  box_gather (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * box_new (char*) ; 

__attribute__((used)) static bo_t *GetWaveTag(mp4mux_trackinfo_t *p_track)
{
    bo_t *wave;
    bo_t *box;

    wave = box_new("wave");
    if(wave)
    {
        box = box_new("frma");
        if(box)
        {
            bo_add_fourcc(box, "mp4a");
            box_gather(wave, box);
        }

        box = box_new("mp4a");
        if(box)
        {
            bo_add_32be(box, 0);
            box_gather(wave, box);
        }

        box = GetESDS(p_track);
        box_gather(wave, box);

        box = box_new("srcq");
        if(box)
        {
            bo_add_32be(box, 0x40);
            box_gather(wave, box);
        }

        /* wazza ? */
        bo_add_32be(wave, 8); /* new empty box */
        bo_add_32be(wave, 0); /* box label */
    }
    return wave;
}