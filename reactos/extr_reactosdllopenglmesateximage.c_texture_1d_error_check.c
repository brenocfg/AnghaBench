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
typedef  scalar_t__ GLint ;
typedef  scalar_t__ GLenum ;
typedef  int /*<<< orphan*/  GLcontext ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
#define  GL_ALPHA 143 
#define  GL_BGRA_EXT 142 
#define  GL_BGR_EXT 141 
#define  GL_BLUE 140 
#define  GL_BYTE 139 
#define  GL_COLOR_INDEX 138 
 int /*<<< orphan*/  GL_FALSE ; 
#define  GL_FLOAT 137 
#define  GL_GREEN 136 
 int /*<<< orphan*/  GL_INVALID_ENUM ; 
 int /*<<< orphan*/  GL_INVALID_VALUE ; 
#define  GL_LUMINANCE 135 
#define  GL_LUMINANCE_ALPHA 134 
 scalar_t__ GL_PROXY_TEXTURE_1D ; 
#define  GL_RED 133 
#define  GL_RGB 132 
#define  GL_RGBA 131 
#define  GL_SHORT 130 
 scalar_t__ GL_TEXTURE_1D ; 
 int /*<<< orphan*/  GL_TRUE ; 
#define  GL_UNSIGNED_BYTE 129 
#define  GL_UNSIGNED_SHORT 128 
 scalar_t__ MAX_TEXTURE_LEVELS ; 
 int MAX_TEXTURE_SIZE ; 
 scalar_t__ decode_internal_format (scalar_t__) ; 
 int /*<<< orphan*/  gl_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ logbase2 (scalar_t__) ; 

__attribute__((used)) static GLboolean texture_1d_error_check( GLcontext *ctx, GLenum target,
                                         GLint level, GLenum internalFormat,
                                         GLenum format, GLenum type,
                                         GLint width, GLint border )
{
   GLint iformat;
   if (target!=GL_TEXTURE_1D && target!=GL_PROXY_TEXTURE_1D) {
      gl_error( ctx, GL_INVALID_ENUM, "glTexImage1D" );
      return GL_TRUE;
   }
   if (level<0 || level>=MAX_TEXTURE_LEVELS) {
      gl_error( ctx, GL_INVALID_VALUE, "glTexImage1D(level)" );
      return GL_TRUE;
   }
   iformat = decode_internal_format( internalFormat );
   if (iformat<0) {
      gl_error( ctx, GL_INVALID_VALUE, "glTexImage1D(internalFormat)" );
      return GL_TRUE;
   }
   if (border!=0 && border!=1) {
      if (target!=GL_PROXY_TEXTURE_1D) {
         gl_error( ctx, GL_INVALID_VALUE, "glTexImage1D(border)" );
      }
      return GL_TRUE;
   }
   if (width<2*border || width>2+MAX_TEXTURE_SIZE) {
      if (target!=GL_PROXY_TEXTURE_1D) {
         gl_error( ctx, GL_INVALID_VALUE, "glTexImage1D(width)" );
      }
      return GL_TRUE;
   }
   if (logbase2( width-2*border )<0) {
      gl_error( ctx, GL_INVALID_VALUE,
               "glTexImage1D(width != 2^k + 2*border)");
      return GL_TRUE;
   }
   switch (format) {
      case GL_COLOR_INDEX:
      case GL_RED:
      case GL_GREEN:
      case GL_BLUE:
      case GL_ALPHA:
      case GL_RGB:
      case GL_BGR_EXT:
      case GL_RGBA:
      case GL_BGRA_EXT:
      case GL_LUMINANCE:
      case GL_LUMINANCE_ALPHA:
         /* OK */
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glTexImage1D(format)" );
         return GL_TRUE;
   }
   switch (type) {
      case GL_UNSIGNED_BYTE:
      case GL_BYTE:
      case GL_UNSIGNED_SHORT:
      case GL_SHORT:
      case GL_FLOAT:
         /* OK */
         break;
      default:
         gl_error( ctx, GL_INVALID_ENUM, "glTexImage1D(type)" );
         return GL_TRUE;
   }
   return GL_FALSE;
}