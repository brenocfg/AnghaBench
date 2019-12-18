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
struct TYPE_3__ {int nbChannels; int scale; int /*<<< orphan*/ * i_values; } ;
typedef  TYPE_1__ BarGraph_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_CLIP (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atof (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int iec_scale (float) ; 
 int log10 (int /*<<< orphan*/ ) ; 
 char* strtok_r (char*,char*,char**) ; 
 int /*<<< orphan*/ * xrealloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void parse_i_values(BarGraph_t *p_BarGraph, char *i_values)
{
    char delim[] = ":";
    char* tok;

    p_BarGraph->nbChannels = 0;
    free(p_BarGraph->i_values);
    p_BarGraph->i_values = NULL;
    char *res = strtok_r(i_values, delim, &tok);
    while (res != NULL) {
        p_BarGraph->nbChannels++;
        p_BarGraph->i_values = xrealloc(p_BarGraph->i_values,
                                          p_BarGraph->nbChannels*sizeof(int));
        float db = log10(atof(res)) * 20;
        p_BarGraph->i_values[p_BarGraph->nbChannels-1] = VLC_CLIP(iec_scale(db)*p_BarGraph->scale, 0, p_BarGraph->scale);
        res = strtok_r(NULL, delim, &tok);
    }
}