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
struct vertex_buffer {int /*<<< orphan*/ ** Material; int /*<<< orphan*/ * MaterialMask; int /*<<< orphan*/ * ClipMask; int /*<<< orphan*/ * Edgeflag; int /*<<< orphan*/ * Bindex; int /*<<< orphan*/ * Findex; int /*<<< orphan*/ * TexCoord; int /*<<< orphan*/ * Bcolor; int /*<<< orphan*/ * Fcolor; int /*<<< orphan*/ * Win; int /*<<< orphan*/ * Eye; int /*<<< orphan*/ * Clip; } ;
typedef  size_t GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_3V (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COPY_4V (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_vertex( struct vertex_buffer *vb, GLuint dst, GLuint src )
{
   COPY_4V( vb->Clip[dst], vb->Clip[src] );
   COPY_4V( vb->Eye[dst], vb->Eye[src] );
   COPY_3V( vb->Win[dst], vb->Win[src] );
   COPY_4V( vb->Fcolor[dst], vb->Fcolor[src] );
   COPY_4V( vb->Bcolor[dst], vb->Bcolor[src] );
   COPY_4V( vb->TexCoord[dst], vb->TexCoord[src] );
   vb->Findex[dst] = vb->Findex[src];
   vb->Bindex[dst] = vb->Bindex[src];
   vb->Edgeflag[dst] = vb->Edgeflag[src];
   vb->ClipMask[dst] = vb->ClipMask[src];
   vb->MaterialMask[dst] = vb->MaterialMask[src];
   vb->Material[dst][0] = vb->Material[src][0];
   vb->Material[dst][1] = vb->Material[src][1];
}