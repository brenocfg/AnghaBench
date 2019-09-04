#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct gl_texture_image {scalar_t__ Width; scalar_t__ Format; scalar_t__ Border; scalar_t__ Height; } ;
struct TYPE_13__ {TYPE_4__* Proxy2D; TYPE_3__* Proxy1D; TYPE_2__* Current2D; TYPE_1__* Current1D; } ;
struct TYPE_14__ {TYPE_5__ Texture; } ;
struct TYPE_12__ {struct gl_texture_image** Image; } ;
struct TYPE_11__ {struct gl_texture_image** Image; } ;
struct TYPE_10__ {struct gl_texture_image** Image; } ;
struct TYPE_9__ {struct gl_texture_image** Image; } ;
typedef  scalar_t__ GLint ;
typedef  int GLenum ;
typedef  TYPE_6__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
#define  GL_PROXY_TEXTURE_1D 142 
#define  GL_PROXY_TEXTURE_2D 141 
#define  GL_TEXTURE_1D 140 
#define  GL_TEXTURE_2D 139 
#define  GL_TEXTURE_ALPHA_SIZE 138 
#define  GL_TEXTURE_BLUE_SIZE 137 
#define  GL_TEXTURE_BORDER 136 
#define  GL_TEXTURE_COMPONENTS 135 
#define  GL_TEXTURE_GREEN_SIZE 134 
#define  GL_TEXTURE_HEIGHT 133 
#define  GL_TEXTURE_INDEX_SIZE_EXT 132 
#define  GL_TEXTURE_INTENSITY_SIZE 131 
#define  GL_TEXTURE_LUMINANCE_SIZE 130 
#define  GL_TEXTURE_RED_SIZE 129 
#define  GL_TEXTURE_WIDTH 128 
 scalar_t__ MAX_TEXTURE_LEVELS ; 
 int /*<<< orphan*/  gl_error (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 

void gl_GetTexLevelParameteriv( GLcontext *ctx, GLenum target, GLint level,
                                GLenum pname, GLint *params )
{
   struct gl_texture_image *tex;

   if (level<0 || level>=MAX_TEXTURE_LEVELS) {
      gl_error( ctx, GL_INVALID_VALUE, "glGetTexLevelParameter[if]v" );
      return;
   }

   switch (target) {
      case GL_TEXTURE_1D:
         tex = ctx->Texture.Current1D->Image[level];
         switch (pname) {
	    case GL_TEXTURE_WIDTH:
	       *params = tex->Width;
	       break;
	    case GL_TEXTURE_COMPONENTS:
	       *params = tex->Format;
	       break;
	    case GL_TEXTURE_BORDER:
	       *params = tex->Border;
	       break;
            case GL_TEXTURE_RED_SIZE:
            case GL_TEXTURE_GREEN_SIZE:
            case GL_TEXTURE_BLUE_SIZE:
            case GL_TEXTURE_ALPHA_SIZE:
            case GL_TEXTURE_INTENSITY_SIZE:
            case GL_TEXTURE_LUMINANCE_SIZE:
               *params = 8;  /* 8-bits */
               break;
            case GL_TEXTURE_INDEX_SIZE_EXT:
               *params = 8;
               break;
	    default:
	       gl_error( ctx, GL_INVALID_ENUM,
                         "glGetTexLevelParameter[if]v(pname)" );
	 }
	 break;
      case GL_TEXTURE_2D:
         tex = ctx->Texture.Current2D->Image[level];
	 switch (pname) {
	    case GL_TEXTURE_WIDTH:
	       *params = tex->Width;
	       break;
	    case GL_TEXTURE_HEIGHT:
	       *params = tex->Height;
	       break;
	    case GL_TEXTURE_COMPONENTS:
	       *params = tex->Format;
	       break;
	    case GL_TEXTURE_BORDER:
	       *params = tex->Border;
	       break;
            case GL_TEXTURE_RED_SIZE:
            case GL_TEXTURE_GREEN_SIZE:
            case GL_TEXTURE_BLUE_SIZE:
            case GL_TEXTURE_ALPHA_SIZE:
            case GL_TEXTURE_INTENSITY_SIZE:
            case GL_TEXTURE_LUMINANCE_SIZE:
               *params = 8;  /* 8-bits */
               break;
            case GL_TEXTURE_INDEX_SIZE_EXT:
               *params = 8;
               break;
	    default:
	       gl_error( ctx, GL_INVALID_ENUM,
                         "glGetTexLevelParameter[if]v(pname)" );
	 }
	 break;
      case GL_PROXY_TEXTURE_1D:
         tex = ctx->Texture.Proxy1D->Image[level];
         switch (pname) {
	    case GL_TEXTURE_WIDTH:
	       *params = tex->Width;
	       break;
	    case GL_TEXTURE_COMPONENTS:
	       *params = tex->Format;
	       break;
	    case GL_TEXTURE_BORDER:
	       *params = tex->Border;
	       break;
            case GL_TEXTURE_RED_SIZE:
            case GL_TEXTURE_GREEN_SIZE:
            case GL_TEXTURE_BLUE_SIZE:
            case GL_TEXTURE_ALPHA_SIZE:
            case GL_TEXTURE_INTENSITY_SIZE:
            case GL_TEXTURE_LUMINANCE_SIZE:
               *params = 8;  /* 8-bits */
               break;
            case GL_TEXTURE_INDEX_SIZE_EXT:
               *params = 8;
               break;
	    default:
	       gl_error( ctx, GL_INVALID_ENUM,
                         "glGetTexLevelParameter[if]v(pname)" );
	 }
	 break;
      case GL_PROXY_TEXTURE_2D:
         tex = ctx->Texture.Proxy2D->Image[level];
	 switch (pname) {
	    case GL_TEXTURE_WIDTH:
	       *params = tex->Width;
	       break;
	    case GL_TEXTURE_HEIGHT:
	       *params = tex->Height;
	       break;
	    case GL_TEXTURE_COMPONENTS:
	       *params = tex->Format;
	       break;
	    case GL_TEXTURE_BORDER:
	       *params = tex->Border;
	       break;
            case GL_TEXTURE_RED_SIZE:
            case GL_TEXTURE_GREEN_SIZE:
            case GL_TEXTURE_BLUE_SIZE:
            case GL_TEXTURE_ALPHA_SIZE:
            case GL_TEXTURE_INTENSITY_SIZE:
            case GL_TEXTURE_LUMINANCE_SIZE:
               *params = 8;  /* 8-bits */
               break;
            case GL_TEXTURE_INDEX_SIZE_EXT:
               *params = 8;
               break;
	    default:
	       gl_error( ctx, GL_INVALID_ENUM,
                         "glGetTexLevelParameter[if]v(pname)" );
	 }
	 break;
     default:
	 gl_error(ctx, GL_INVALID_ENUM, "glGetTexLevelParameter[if]v(target)");
   }	 
}