#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int Mask; } ;
struct TYPE_6__ {TYPE_1__ Feedback; } ;
typedef  int /*<<< orphan*/  const GLfloat ;
typedef  TYPE_2__ GLcontext ;

/* Variables and functions */
 int FB_3D ; 
 int FB_4D ; 
 int FB_COLOR ; 
 int FB_INDEX ; 
 int FB_TEXTURE ; 
 int /*<<< orphan*/  FEEDBACK_TOKEN (TYPE_2__*,int /*<<< orphan*/  const) ; 

void gl_feedback_vertex( GLcontext *ctx,
                         GLfloat x, GLfloat y, GLfloat z, GLfloat w,
			 const GLfloat color[4], GLfloat index,
			 const GLfloat texcoord[4] )
{
   FEEDBACK_TOKEN( ctx, x );
   FEEDBACK_TOKEN( ctx, y );
   if (ctx->Feedback.Mask & FB_3D) {
      FEEDBACK_TOKEN( ctx, z );
   }
   if (ctx->Feedback.Mask & FB_4D) {
      FEEDBACK_TOKEN( ctx, w );
   }
   if (ctx->Feedback.Mask & FB_INDEX) {
      FEEDBACK_TOKEN( ctx, index );
   }
   if (ctx->Feedback.Mask & FB_COLOR) {
      FEEDBACK_TOKEN( ctx, color[0] );
      FEEDBACK_TOKEN( ctx, color[1] );
      FEEDBACK_TOKEN( ctx, color[2] );
      FEEDBACK_TOKEN( ctx, color[3] );
   }
   if (ctx->Feedback.Mask & FB_TEXTURE) {
      FEEDBACK_TOKEN( ctx, texcoord[0] );
      FEEDBACK_TOKEN( ctx, texcoord[1] );
      FEEDBACK_TOKEN( ctx, texcoord[2] );
      FEEDBACK_TOKEN( ctx, texcoord[3] );
   }
}