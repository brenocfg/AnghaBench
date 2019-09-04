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
struct TYPE_3__ {int y0; int y1; int y2; int y3; int u; int v; int* r; int* g; int* b; } ;
typedef  TYPE_1__ cvid_codebook ;

/* Variables and functions */
 void* get_byte () ; 
 void** uiclp ; 

__attribute__((used)) static inline void read_codebook(cvid_codebook *c, int mode)
{
int uvr, uvg, uvb;

    if(mode)        /* black and white */
        {
        c->y0 = get_byte();
        c->y1 = get_byte();
        c->y2 = get_byte();
        c->y3 = get_byte();
        c->u = c->v = 0;

        c->r[0] = c->g[0] = c->b[0] = c->y0;
        c->r[1] = c->g[1] = c->b[1] = c->y1;
        c->r[2] = c->g[2] = c->b[2] = c->y2;
        c->r[3] = c->g[3] = c->b[3] = c->y3;
        }
    else            /* colour */
        {
        c->y0 = get_byte();  /* luma */
        c->y1 = get_byte();
        c->y2 = get_byte();
        c->y3 = get_byte();
        c->u = get_byte(); /* chroma */
        c->v = get_byte();

        uvr = c->v << 1;
        uvg = -((c->u+1) >> 1) - c->v;
        uvb = c->u << 1;

        c->r[0] = uiclp[c->y0 + uvr]; c->g[0] = uiclp[c->y0 + uvg]; c->b[0] = uiclp[c->y0 + uvb];
        c->r[1] = uiclp[c->y1 + uvr]; c->g[1] = uiclp[c->y1 + uvg]; c->b[1] = uiclp[c->y1 + uvb];
        c->r[2] = uiclp[c->y2 + uvr]; c->g[2] = uiclp[c->y2 + uvg]; c->b[2] = uiclp[c->y2 + uvb];
        c->r[3] = uiclp[c->y3 + uvr]; c->g[3] = uiclp[c->y3 + uvg]; c->b[3] = uiclp[c->y3 + uvb];
        }
}