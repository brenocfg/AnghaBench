#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct gl_texture_image {scalar_t__ Border; size_t Width; scalar_t__ Height; int /*<<< orphan*/  IntFormat; int /*<<< orphan*/ * Data; int /*<<< orphan*/  Format; } ;
struct gl_image {scalar_t__ Type; size_t Components; scalar_t__ RefCount; scalar_t__ Data; } ;
struct TYPE_14__ {struct gl_texture_image** Image; void* Dirty; } ;
struct TYPE_12__ {TYPE_5__* Current2D; void* AnyDirty; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* TexImage ) (TYPE_3__*,scalar_t__,TYPE_5__*,size_t,int /*<<< orphan*/ ,struct gl_texture_image*) ;int /*<<< orphan*/  (* TexSubImage ) (TYPE_3__*,scalar_t__,TYPE_5__*,size_t,size_t,size_t,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct gl_texture_image*) ;} ;
struct TYPE_13__ {TYPE_2__ Texture; TYPE_1__ Driver; } ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  scalar_t__ GLsizei ;
typedef  size_t GLint ;
typedef  scalar_t__ GLenum ;
typedef  TYPE_3__ GLcontext ;

/* Variables and functions */
 scalar_t__ GL_BITMAP ; 
 scalar_t__ GL_COLOR_INDEX ; 
 scalar_t__ GL_DEPTH_COMPONENT ; 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_OPERATION ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
 int /*<<< orphan*/  GL_OUT_OF_MEMORY ; 
 scalar_t__ GL_STENCIL_INDEX ; 
 scalar_t__ GL_TEXTURE_2D ; 
 void* GL_TRUE ; 
 scalar_t__ GL_UNSIGNED_BYTE ; 
 size_t MAX_TEXTURE_LEVELS ; 
 int /*<<< orphan*/  MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 size_t components_in_intformat (int /*<<< orphan*/ ) ; 
 size_t gl_components_in_format (scalar_t__) ; 
 int /*<<< orphan*/  gl_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gl_free_image (struct gl_image*) ; 
 int /*<<< orphan*/  gl_free_texture_image (struct gl_texture_image*) ; 
 size_t gl_sizeof_type (scalar_t__) ; 
 struct gl_texture_image* image_to_texture (TYPE_3__*,struct gl_image*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,scalar_t__,TYPE_5__*,size_t,size_t,size_t,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct gl_texture_image*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,scalar_t__,TYPE_5__*,size_t,int /*<<< orphan*/ ,struct gl_texture_image*) ; 

void gl_TexSubImage2D( GLcontext *ctx,
                       GLenum target, GLint level,
                       GLint xoffset, GLint yoffset,
                       GLsizei width, GLsizei height,
                       GLenum format, GLenum type,
                       struct gl_image *image )
{
   struct gl_texture_image *destTex;

   if (target!=GL_TEXTURE_2D) {
      gl_error( ctx, GL_INVALID_ENUM, "glTexSubImage2D(target)" );
      return;
   }
   if (level<0 || level>=MAX_TEXTURE_LEVELS) {
      gl_error( ctx, GL_INVALID_ENUM, "glTexSubImage2D(level)" );
      return;
   }

   destTex = ctx->Texture.Current2D->Image[level];
   if (!destTex) {
      gl_error( ctx, GL_INVALID_OPERATION, "glTexSubImage2D" );
      return;
   }

   if (xoffset < -((GLint)destTex->Border)) {
      gl_error( ctx, GL_INVALID_VALUE, "glTexSubImage2D(xoffset)" );
      return;
   }
   if (yoffset < -((GLint)destTex->Border)) {
      gl_error( ctx, GL_INVALID_VALUE, "glTexSubImage2D(yoffset)" );
      return;
   }
   if (xoffset + width > destTex->Width + destTex->Border) {
      gl_error( ctx, GL_INVALID_VALUE, "glTexSubImage2D(xoffset+width)" );
      return;
   }
   if (yoffset + height > destTex->Height + destTex->Border) {
      gl_error( ctx, GL_INVALID_VALUE, "glTexSubImage2D(yoffset+height)" );
      return;
   }

   if (image) {
      /* unpacking must have been error-free */
      GLint texcomponents = components_in_intformat(destTex->Format);

      if (image->Type==GL_UNSIGNED_BYTE && texcomponents==image->Components) {
         /* Simple case, just byte copy image data into texture image */
         /* row by row. */
         GLubyte *dst = destTex->Data 
                      + (yoffset * destTex->Width + xoffset) * texcomponents;
         GLubyte *src = (GLubyte *) image->Data;
         GLint  j;
         for (j=0;j<height;j++) {
            MEMCPY( dst, src, width * texcomponents );
            dst += destTex->Width * texcomponents * sizeof(GLubyte);
            src += width * texcomponents * sizeof(GLubyte);
         }
      }
      else {
         /* General case, convert image pixels into texels, scale, bias, etc */
         struct gl_texture_image *subTexImg = image_to_texture(ctx, image,
                                        destTex->IntFormat, destTex->Border);
         GLubyte *dst = destTex->Data
                  + (yoffset * destTex->Width + xoffset) * texcomponents;
         GLubyte *src = subTexImg->Data;
         GLint j;
         for (j=0;j<height;j++) {
            MEMCPY( dst, src, width * texcomponents );
            dst += destTex->Width * texcomponents * sizeof(GLubyte);
            src += width * texcomponents * sizeof(GLubyte);
         }
         gl_free_texture_image(subTexImg);
      }

      /* if the image's reference count is zero, delete it now */
      if (image->RefCount==0) {
         gl_free_image(image);
      }

      ctx->Texture.Current2D->Dirty = GL_TRUE;
      ctx->Texture.AnyDirty = GL_TRUE;

      /* tell driver about change */
      if (ctx->Driver.TexSubImage) {
	(*ctx->Driver.TexSubImage)( ctx, GL_TEXTURE_2D, ctx->Texture.Current2D, level,
				    xoffset, yoffset, width, height,
				    ctx->Texture.Current2D->Image[level]->IntFormat,
				    destTex );
      }
      else {
	if (ctx->Driver.TexImage) {
	  (*ctx->Driver.TexImage)( ctx, GL_TEXTURE_2D, ctx->Texture.Current2D,
				   level, ctx->Texture.Current2D->Image[level]->IntFormat,
				   destTex );
	}
      }
   }
   else {
      /* if no image, an error must have occured, do more testing now */
      GLint components, size;

      if (width<0) {
         gl_error( ctx, GL_INVALID_VALUE, "glTexSubImage2D(width)" );
         return;
      }
      if (height<0) {
         gl_error( ctx, GL_INVALID_VALUE, "glTexSubImage2D(height)" );
         return;
      }
      if (type==GL_BITMAP && format!=GL_COLOR_INDEX) {
         gl_error( ctx, GL_INVALID_ENUM, "glTexSubImage1D(format)" );
         return;
      }
      components = gl_components_in_format( format );
      if (components<0 || format==GL_STENCIL_INDEX
          || format==GL_DEPTH_COMPONENT){
         gl_error( ctx, GL_INVALID_ENUM, "glTexSubImage2D(format)" );
         return;
      }
      size = gl_sizeof_type( type );
      if (size<=0) {
         gl_error( ctx, GL_INVALID_ENUM, "glTexSubImage2D(type)" );
         return;
      }
      /* if we get here, probably ran out of memory during unpacking */
      gl_error( ctx, GL_OUT_OF_MEMORY, "glTexSubImage2D" );
   }
}