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
typedef  int GLuint ;

/* Variables and functions */
#define  GL_ALPHA 146 
 int GL_DEPTH_COMPONENT ; 
 int GL_FLOAT ; 
#define  GL_INTENSITY 145 
#define  GL_LINEAR 144 
 int GL_LINEAR_MIPMAP_LINEAR ; 
 int GL_LINEAR_MIPMAP_NEAREST ; 
#define  GL_LUMINANCE 143 
#define  GL_LUMINANCE_ALPHA 142 
#define  GL_NEAREST 141 
#define  GL_RED 140 
 int GL_REPEAT ; 
#define  GL_RGB 139 
#define  GL_RGBA 138 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
 int GL_UNSIGNED_BYTE ; 
 int STBGL_CLAMP_TO_BORDER ; 
 int STBGL_CLAMP_TO_EDGE ; 
#define  STBGL_COMPRESSED_RGBA_S3TC_DXT1 137 
#define  STBGL_COMPRESSED_RGBA_S3TC_DXT3 136 
#define  STBGL_COMPRESSED_RGBA_S3TC_DXT5 135 
#define  STBGL_COMPRESSED_RGB_S3TC_DXT1 134 
 int STBGL_DEPTH_COMPONENT16 ; 
 int STBGL_DEPTH_COMPONENT24 ; 
 int STBGL_DEPTH_COMPONENT32 ; 
#define  STBGL_GEN_MIPMAPS 133 
#define  STBGL_MIPMAPS 132 
#define  STBGL_NO_DOWNLOAD 131 
#define  STBGL_UNDEFINED 130 
#define  STBGL_YCOCG 129 
#define  STBGL_YCOCGJ 128 
 int abs (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glGenTextures (int,int*) ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int,int,void*) ; 
 int /*<<< orphan*/  glTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gluBuild2DMipmaps (int /*<<< orphan*/ ,int,int,int,int,int,void*) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stbgl__initCompTex () ; 
 int stbgl_hasExtension (char*) ; 
 int /*<<< orphan*/  stbgl_m (char*,char*) ; 

int stbgl_TexImage2D_Extra(int texid, int w, int h, void *data, int chan, char *props, int preserve_data)
{
   static int has_s3tc = -1; // haven't checked yet
   int free_data = 0, is_compressed = 0;
   int pad_to_power_of_two = 0, non_power_of_two = 0;
   int premultiply_alpha = 0; // @TODO
   int float_tex   = 0; // @TODO
   int input_type  = GL_UNSIGNED_BYTE;
   int input_desc  = STBGL_UNDEFINED;
   int output_desc = STBGL_UNDEFINED;
   int mipmaps     = STBGL_UNDEFINED;
   int filter      = STBGL_UNDEFINED, mag_filter;
   int wrap_s = STBGL_UNDEFINED, wrap_t = STBGL_UNDEFINED;

   // parse out the properties
   if (props == NULL) props = "";
   while (*props) {
      switch (*props) {
         case '1' :  input_desc = GL_LUMINANCE; break;
         case '2' :  input_desc = GL_LUMINANCE_ALPHA; break;
         case '3' :  input_desc = GL_RGB; break;
         case '4' :  input_desc = GL_RGBA; break;
         case 'l' :  if (props[1] == 'a') { input_desc = GL_LUMINANCE_ALPHA; ++props; }
                     else input_desc = GL_LUMINANCE;
                     break;
         case 'a' :  input_desc = GL_ALPHA; break;
         case 'r' :  if (stbgl_m(props, "rgba")) { input_desc = GL_RGBA; props += 3; break; }
                     if (stbgl_m(props, "rgb")) { input_desc = GL_RGB; props += 2; break; }
                     input_desc = GL_RED;
                     break;
         case 'y' :  if (stbgl_m(props, "ycocg")) {
                        if (props[5] == 'j') { props += 5; input_desc = STBGL_YCOCGJ; }
                        else { props += 4; input_desc = STBGL_YCOCG; }
                        break;
                     }
                     return 0;
         case 'L' :  if (props[1] == 'A') { output_desc = GL_LUMINANCE_ALPHA; ++props; }
                     else output_desc = GL_LUMINANCE;
                     break;
         case 'I' :  output_desc = GL_INTENSITY; break;
         case 'A' :  output_desc = GL_ALPHA; break;
         case 'R' :  if (stbgl_m(props, "RGBA")) { output_desc = GL_RGBA; props += 3; break; }
                     if (stbgl_m(props, "RGB")) { output_desc = GL_RGB; props += 2; break; }
                     output_desc = GL_RED;
                     break;
         case 'Y' :  if (stbgl_m(props, "YCoCg") || stbgl_m(props, "YCOCG")) {
                        props += 4;
                        output_desc = STBGL_YCOCG;
                        break;
                     }
                     return 0;
         case 'D' :  if (stbgl_m(props, "DXT")) {
                        switch (props[3]) {
                           case '1': output_desc = STBGL_COMPRESSED_RGB_S3TC_DXT1; break;
                           case '3': output_desc = STBGL_COMPRESSED_RGBA_S3TC_DXT3; break;
                           case '5': output_desc = STBGL_COMPRESSED_RGBA_S3TC_DXT5; break;
                           default: return 0;
                        }
                        props += 3;
                     } else if (stbgl_m(props, "D16")) {
                        output_desc = STBGL_DEPTH_COMPONENT16;
                        input_desc  = GL_DEPTH_COMPONENT;
                        props += 2;
                     } else if (stbgl_m(props, "D24")) {
                        output_desc = STBGL_DEPTH_COMPONENT24;
                        input_desc  = GL_DEPTH_COMPONENT;
                        props += 2;
                     } else if (stbgl_m(props, "D32")) {
                        output_desc = STBGL_DEPTH_COMPONENT32;
                        input_desc  = GL_DEPTH_COMPONENT;
                        props += 2;
                     } else {
                        output_desc = GL_DEPTH_COMPONENT;
                        input_desc  = GL_DEPTH_COMPONENT;
                     }
                     break;
         case 'N' :  if (stbgl_m(props, "NONE")) {
                        props += 3;
                        input_desc = STBGL_NO_DOWNLOAD;
                        output_desc = STBGL_NO_DOWNLOAD;
                        break;
                     }
                     if (stbgl_m(props, "NP2")) {
                        non_power_of_two = 1;
                        props += 2;
                        break;
                     }
                     return 0;
         case 'm' :  mipmaps = STBGL_GEN_MIPMAPS; break;
         case 'M' :  mipmaps = STBGL_MIPMAPS; break;
         case 't' :  filter = GL_LINEAR_MIPMAP_LINEAR; break;
         case 'b' :  filter = GL_LINEAR; break;
         case 'n' :  filter = GL_NEAREST; break;
         case 'w' :  if (wrap_s == STBGL_UNDEFINED) wrap_s = GL_REPEAT; else wrap_t = GL_REPEAT; break;
         case 'C' :  if (wrap_s == STBGL_UNDEFINED) wrap_s = STBGL_CLAMP_TO_BORDER; else wrap_t = STBGL_CLAMP_TO_BORDER; break;
         case 'c' :  if (wrap_s == STBGL_UNDEFINED) wrap_s = STBGL_CLAMP_TO_EDGE; else wrap_t = STBGL_CLAMP_TO_EDGE; break;
         case 'f' :  input_type = GL_FLOAT; break;
         case 'F' :  input_type = GL_FLOAT; float_tex = 1; break;
         case 'p' :  premultiply_alpha = 1; break;
         case 'P' :  pad_to_power_of_two = 1; break;
         case '+' :  preserve_data = 0; break;
         case '!' :  preserve_data = 0; free_data = 1; break;
         case ' ' :  break;
         case '-' :  break;
         default  :  if (free_data) free(data);
                     return 0;
      }
      ++props;
   }
   
   // override input_desc based on channel count
   if (output_desc != STBGL_NO_DOWNLOAD) {
      switch (abs(chan)) {
         case 1: input_desc = GL_LUMINANCE; break;
         case 2: input_desc = GL_LUMINANCE_ALPHA; break;
         case 3: input_desc = GL_RGB; break;
         case 4: input_desc = GL_RGBA; break;
         case 0: break;
         default: return 0;
      }
   }

   // override input_desc based on channel info
   if (chan > 0) { input_type = GL_UNSIGNED_BYTE; }
   if (chan < 0) { input_type = GL_FLOAT; }

   if (output_desc == GL_ALPHA) {
      if (input_desc == GL_LUMINANCE)
         input_desc = GL_ALPHA;
      if (input_desc == GL_RGB) {
         // force a presumably-mono image to alpha
         // @TODO handle 'preserve_data' case?
         if (data && !preserve_data && input_type == GL_UNSIGNED_BYTE) {
            int i;
            unsigned char *p = (unsigned char *) data, *q = p;
            for (i=0; i < w*h; ++i) {
               *q = (p[0] + 2*p[1] + p[2]) >> 2;
               p += 3;
               q += 1;
            }
            input_desc = GL_ALPHA;
         }
      }
   }

   // set undefined input/output based on the other
   if (input_desc == STBGL_UNDEFINED && output_desc == STBGL_UNDEFINED) {
      input_desc = output_desc = GL_RGBA;
   } else if (output_desc == STBGL_UNDEFINED) {
      switch (input_desc) {
         case GL_LUMINANCE:
         case GL_ALPHA:
         case GL_LUMINANCE_ALPHA:
         case GL_RGB:
         case GL_RGBA:
            output_desc = input_desc;
            break;
         case GL_RED:
            output_desc = GL_INTENSITY;
            break;
         case STBGL_YCOCG:
         case STBGL_YCOCGJ:
            output_desc = STBGL_YCOCG;
            break;
         default: assert(0); return 0;
      }
   } else if (input_desc == STBGL_UNDEFINED) {
      switch (output_desc) {
         case GL_LUMINANCE:
         case GL_ALPHA:
         case GL_LUMINANCE_ALPHA:
         case GL_RGB:
         case GL_RGBA:
            input_desc = output_desc;
            break;
         case GL_INTENSITY:
            input_desc = GL_RED;
            break;
         case STBGL_YCOCG:
         case STBGL_COMPRESSED_RGB_S3TC_DXT1:
         case STBGL_COMPRESSED_RGBA_S3TC_DXT3:
         case STBGL_COMPRESSED_RGBA_S3TC_DXT5:
            input_desc = GL_RGBA;
            break;
      }
   } else {
      if (output_desc == STBGL_COMPRESSED_RGB_S3TC_DXT1) {
         // if input has alpha, force output alpha
         switch (input_desc) {
            case GL_ALPHA:
            case GL_LUMINANCE_ALPHA:
            case GL_RGBA:
               output_desc = STBGL_COMPRESSED_RGBA_S3TC_DXT5;
               break;
         }
      }
   }

   switch(input_desc) {
      case GL_LUMINANCE:
      case GL_RED:
      case GL_ALPHA:
         chan = 1;
         break;
      case GL_LUMINANCE_ALPHA:
         chan = 2;
         break;
      case GL_RGB:
         chan = 3;
         break;
      case GL_RGBA:
         chan = 4;
         break;
   }

   if (pad_to_power_of_two && ((w & (w-1)) || (h & (h-1)))) {
      if (output_desc != STBGL_NO_DOWNLOAD && input_type == GL_UNSIGNED_BYTE && chan > 0) {
         unsigned char *new_data;
         int w2 = w, h2 = h, j;
         while (w & (w-1))
            w = (w | (w>>1))+1;
         while (h & (h-1))
            h = (h | (h>>1))+1;
         new_data = malloc(w * h * chan);
         for (j=0; j < h2; ++j) {
            memcpy(new_data + j * w * chan, (char *) data+j*w2*chan, w2*chan);
            memset(new_data + (j * w+w2) * chan, 0, (w-w2)*chan);
         }
         for (; j < h; ++j)
            memset(new_data + j*w*chan, 0, w*chan);
         if (free_data)
            free(data);
         data = new_data;
         free_data = 1;
      }
   }

   switch (output_desc) {
      case STBGL_COMPRESSED_RGB_S3TC_DXT1:
      case STBGL_COMPRESSED_RGBA_S3TC_DXT1:
      case STBGL_COMPRESSED_RGBA_S3TC_DXT3:
      case STBGL_COMPRESSED_RGBA_S3TC_DXT5:
         is_compressed = 1;
         if (has_s3tc == -1) {
            has_s3tc = stbgl_hasExtension("GL_EXT_texture_compression_s3tc");
            if (has_s3tc) stbgl__initCompTex();
         }
         if (!has_s3tc) {
            is_compressed = 0;
            if (output_desc == STBGL_COMPRESSED_RGB_S3TC_DXT1)
               output_desc = GL_RGB;
            else
               output_desc = GL_RGBA;
         }
   }

   if (output_desc == STBGL_YCOCG) {
      assert(0);
      output_desc = GL_RGB; // @TODO!
      if (free_data) free(data);
      return 0;
   }

   mag_filter = 0;
   if (mipmaps != STBGL_UNDEFINED) {
      switch (filter) {
         case STBGL_UNDEFINED: filter = GL_LINEAR_MIPMAP_LINEAR; break;
         case GL_NEAREST     : mag_filter = GL_NEAREST; filter = GL_LINEAR_MIPMAP_LINEAR; break;
         case GL_LINEAR      : filter = GL_LINEAR_MIPMAP_NEAREST; break;
      }
   } else {
      if (filter == STBGL_UNDEFINED)
         filter = GL_LINEAR;
   }

   // update filtering
   if (!mag_filter) {
      if (filter == GL_NEAREST)
         mag_filter = GL_NEAREST;
      else
         mag_filter = GL_LINEAR;
   }

   // update wrap/clamp
   if (wrap_s == STBGL_UNDEFINED) wrap_s = GL_REPEAT;
   if (wrap_t == STBGL_UNDEFINED) wrap_t = wrap_s;

   // if no texture id, generate one
   if (texid == 0) {
      GLuint tex;
      glGenTextures(1, &tex);
      if (tex == 0) { if (free_data) free(data); return 0; }
      texid = tex;
   }

   if (data == NULL && mipmaps == STBGL_GEN_MIPMAPS)
      mipmaps = STBGL_MIPMAPS;

   if (output_desc == STBGL_NO_DOWNLOAD)
      mipmaps = STBGL_NO_DOWNLOAD;

   glBindTexture(GL_TEXTURE_2D, texid);

#ifdef STB_COMPRESS_DXT_BLOCK
   if (!is_compressed || !stbgl__CompressedTexImage2DARB || output_desc == STBGL_COMPRESSED_RGBA_S3TC_DXT3 || data == NULL)
#endif
   {
      switch (mipmaps) {
         case STBGL_NO_DOWNLOAD:
            break;

         case STBGL_UNDEFINED:
            // check if actually power-of-two
            if (non_power_of_two || ((w & (w-1)) == 0 && (h & (h-1)) == 0))
               glTexImage2D(GL_TEXTURE_2D, 0, output_desc, w, h, 0, input_desc, input_type, data);
            else
               gluBuild2DMipmaps(GL_TEXTURE_2D, output_desc, w, h, input_desc, input_type, data);
               // not power of two, so use glu to resize (generates mipmaps needlessly)
            break;

         case STBGL_MIPMAPS: {
            int level = 0;
            int size = input_type == GL_FLOAT ? sizeof(float) : 1;
            if (data == NULL) size = 0; // reuse same block of memory for all mipmaps
            assert((w & (w-1)) == 0 && (h & (h-1)) == 0); // verify power-of-two
            while (w > 1 && h > 1) {
               glTexImage2D(GL_TEXTURE_2D, level, output_desc, w, h, 0, input_desc, input_type, data);
               data = (void *) ((char *) data + w * h * size * chan);
               if (w > 1) w >>= 1;
               if (h > 1) h >>= 1;
               ++level;
            }
            break;
         }
         case STBGL_GEN_MIPMAPS:
            gluBuild2DMipmaps(GL_TEXTURE_2D, output_desc, w, h, input_desc, input_type, data);
            break;

         default:
            assert(0);
            if (free_data) free(data);
            return 0;
      }
#ifdef STB_COMPRESS_DXT_BLOCK
   } else {
      uint8 *out, *rgba=0, *end_out, *end_rgba;
      int level = 0, alpha = (output_desc != STBGL_COMPRESSED_RGB_S3TC_DXT1);
      int size = input_type == GL_FLOAT ? sizeof(float) : 1;
      int osize = alpha ? 16 : 8;
      if (!free_data && mipmaps == STBGL_GEN_MIPMAPS) {
         uint8 *temp = malloc(w*h*chan);
         if (!temp) { if (free_data) free(data); return 0; }
         memcpy(temp, data, w*h*chan);
         if (free_data) free(data);
         free_data = 1;
         data = temp;
      }
      if (chan != 4 || size != 1) {
         rgba = malloc(w*h*4);
         if (!rgba) return 0;
         end_rgba = rgba+w*h*4;
      }
      out = malloc((w+3)*(h+3)/16*osize); // enough storage for the s3tc data
      if (!out) return 0;
      end_out = out + ((w+3)*(h+3))/16*osize;

      for(;;) {
         if (chan != 4)
            stbgl__convert(rgba, data, w*h, input_desc, end_rgba);
         stbgl__compress(out, rgba ? rgba : data, w, h, output_desc, end_out);
         stbgl__CompressedTexImage2DARB(GL_TEXTURE_2D, level, output_desc, w, h, 0, ((w+3)&~3)*((h+3)&~3)/16*osize, out);
         //glTexImage2D(GL_TEXTURE_2D, level, alpha?GL_RGBA:GL_RGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba ? rgba : data);

         if (mipmaps == STBGL_UNDEFINED) break;
         if (w <= 1 && h <= 1) break;
         if (mipmaps == STBGL_MIPMAPS) data = (void *) ((char *) data + w * h * size * chan);
         if (mipmaps == STBGL_GEN_MIPMAPS) {
            int w2 = w>>1, h2=h>>1, i,j,k, s=w*chan;
            uint8 *p = data, *q=data;
            if (w == 1) {
               for (j=0; j < h2; ++j) {
                  for (k=0; k < chan; ++k)
                     *p++ = (q[k] + q[s+k] + 1) >> 1;
                  q += s*2;
               }
            } else if (h == 1) {
               for (i=0; i < w2; ++i) {
                  for (k=0; k < chan; ++k)
                     *p++ = (q[k] + q[k+chan] + 1) >> 1;
                  q += chan*2;
               }
            } else {
               for (j=0; j < h2; ++j) {
                  for (i=0; i < w2; ++i) {
                     for (k=0; k < chan; ++k)
                        *p++ = (q[k] + q[k+chan] + q[s+k] + q[s+k+chan] + 2) >> 2;
                     q += chan*2;
                  }
                  q += s;
               }
            }
         }
         if (w > 1) w >>= 1;
         if (h > 1) h >>= 1;
         ++level;
      }
      if (out) free(out);
      if (rgba) free(rgba);
#endif // STB_COMPRESS_DXT_BLOCK
   }

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);

   if (free_data) free(data);
   return texid;
}