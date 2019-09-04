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
struct TYPE_3__ {int nColorTblLen; scalar_t__* colortbl; } ;
typedef  TYPE_1__ ME_OutStream ;
typedef  scalar_t__ COLORREF ;

/* Variables and functions */
 int STREAMOUT_COLORTBL_SIZE ; 

__attribute__((used)) static void add_color_to_colortbl( ME_OutStream *stream, COLORREF color )
{
    int i;

    for (i = 1; i < stream->nColorTblLen; i++)
        if (stream->colortbl[i] == color)
            break;

    if (i == stream->nColorTblLen && i < STREAMOUT_COLORTBL_SIZE)
    {
        stream->colortbl[i] = color;
        stream->nColorTblLen++;
    }
}