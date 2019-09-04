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
struct vertex_buffer {void*** TexCoord; void*** Eye; void*** Fcolor; } ;
struct TYPE_3__ {struct vertex_buffer* VB; } ;
typedef  size_t GLuint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  TYPE_1__ GLcontext ;

/* Variables and functions */
 void* LINTERP (int /*<<< orphan*/ ,void*,void*) ; 

void interpolate_aux_color_tex2( GLcontext* ctx, GLuint space,
				 GLuint dst, GLfloat t, GLuint in, GLuint out )
{
   struct vertex_buffer* VB = ctx->VB;

   VB->Fcolor[dst][0] = LINTERP( t, VB->Fcolor[in][0], VB->Fcolor[out][0] );
   VB->Fcolor[dst][1] = LINTERP( t, VB->Fcolor[in][1], VB->Fcolor[out][1] );
   VB->Fcolor[dst][2] = LINTERP( t, VB->Fcolor[in][2], VB->Fcolor[out][2] );
   VB->Fcolor[dst][3] = LINTERP( t, VB->Fcolor[in][3], VB->Fcolor[out][3] );

   VB->Eye[dst][2] = LINTERP( t, VB->Eye[in][2], VB->Eye[out][2] );
   VB->TexCoord[dst][0] = LINTERP(t,VB->TexCoord[in][0],VB->TexCoord[out][0]);
   VB->TexCoord[dst][1] = LINTERP(t,VB->TexCoord[in][1],VB->TexCoord[out][1]);
}