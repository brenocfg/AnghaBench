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
typedef  int stbi_uc ;
typedef  int stbi__uint8 ;
typedef  int /*<<< orphan*/  stbi ;

/* Variables and functions */
 int* convert_format (int*,int,int,int,int) ; 
 int* epuc (char*,char*) ; 
 int get16 (int /*<<< orphan*/ *) ; 
 int get32 (int /*<<< orphan*/ *) ; 
 int get8 (int /*<<< orphan*/ *) ; 
 int get8u (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static stbi_uc *psd_load(stbi *s, int *x, int *y, int *comp, int req_comp)
{
   int   pixelCount;
   int channelCount, compression;
   int channel, i, count, len;
   int w,h;
   stbi__uint8 *out;

   // Check identifier
   if (get32(s) != 0x38425053)   // "8BPS"
      return epuc("not PSD", "Corrupt PSD image");

   // Check file type version.
   if (get16(s) != 1)
      return epuc("wrong version", "Unsupported version of PSD image");

   // Skip 6 reserved bytes.
   skip(s, 6 );

   // Read the number of channels (R, G, B, A, etc).
   channelCount = get16(s);
   if (channelCount < 0 || channelCount > 16)
      return epuc("wrong channel count", "Unsupported number of channels in PSD image");

   // Read the rows and columns of the image.
   h = get32(s);
   w = get32(s);
   
   // Make sure the depth is 8 bits.
   if (get16(s) != 8)
      return epuc("unsupported bit depth", "PSD bit depth is not 8 bit");

   // Make sure the color mode is RGB.
   // Valid options are:
   //   0: Bitmap
   //   1: Grayscale
   //   2: Indexed color
   //   3: RGB color
   //   4: CMYK color
   //   7: Multichannel
   //   8: Duotone
   //   9: Lab color
   if (get16(s) != 3)
      return epuc("wrong color format", "PSD is not in RGB color format");

   // Skip the Mode Data.  (It's the palette for indexed color; other info for other modes.)
   skip(s,get32(s) );

   // Skip the image resources.  (resolution, pen tool paths, etc)
   skip(s, get32(s) );

   // Skip the reserved data.
   skip(s, get32(s) );

   // Find out if the data is compressed.
   // Known values:
   //   0: no compression
   //   1: RLE compressed
   compression = get16(s);
   if (compression > 1)
      return epuc("bad compression", "PSD has an unknown compression format");

   // Create the destination image.
   out = (stbi_uc *) malloc(4 * w*h);
   if (!out) return epuc("outofmem", "Out of memory");
   pixelCount = w*h;

   // Initialize the data to zero.
   //memset( out, 0, pixelCount * 4 );
   
   // Finally, the image data.
   if (compression) {
      // RLE as used by .PSD and .TIFF
      // Loop until you get the number of unpacked bytes you are expecting:
      //     Read the next source byte into n.
      //     If n is between 0 and 127 inclusive, copy the next n+1 bytes literally.
      //     Else if n is between -127 and -1 inclusive, copy the next byte -n+1 times.
      //     Else if n is 128, noop.
      // Endloop

      // The RLE-compressed data is preceeded by a 2-byte data count for each row in the data,
      // which we're going to just skip.
      skip(s, h * channelCount * 2 );

      // Read the RLE data by channel.
      for (channel = 0; channel < 4; channel++) {
         stbi__uint8 *p;
         
         p = out+channel;
         if (channel >= channelCount) {
            // Fill this channel with default data.
            for (i = 0; i < pixelCount; i++) *p = (channel == 3 ? 255 : 0), p += 4;
         } else {
            // Read the RLE data.
            count = 0;
            while (count < pixelCount) {
               len = get8(s);
               if (len == 128) {
                  // No-op.
               } else if (len < 128) {
                  // Copy next len+1 bytes literally.
                  len++;
                  count += len;
                  while (len) {
                     *p = get8u(s);
                     p += 4;
                     len--;
                  }
               } else if (len > 128) {
                  stbi__uint8   val;
                  // Next -len+1 bytes in the dest are replicated from next source byte.
                  // (Interpret len as a negative 8-bit int.)
                  len ^= 0x0FF;
                  len += 2;
                  val = get8u(s);
                  count += len;
                  while (len) {
                     *p = val;
                     p += 4;
                     len--;
                  }
               }
            }
         }
      }
      
   } else {
      // We're at the raw image data.  It's each channel in order (Red, Green, Blue, Alpha, ...)
      // where each channel consists of an 8-bit value for each pixel in the image.
      
      // Read the data by channel.
      for (channel = 0; channel < 4; channel++) {
         stbi__uint8 *p;
         
         p = out + channel;
         if (channel > channelCount) {
            // Fill this channel with default data.
            for (i = 0; i < pixelCount; i++) *p = channel == 3 ? 255 : 0, p += 4;
         } else {
            // Read the data.
            for (i = 0; i < pixelCount; i++)
               *p = get8u(s), p += 4;
         }
      }
   }

   if (req_comp && req_comp != 4) {
      out = convert_format(out, 4, req_comp, w, h);
      if (out == NULL) return out; // convert_format frees input on failure
   }

   if (comp) *comp = channelCount;
   *y = h;
   *x = w;
   
   return out;
}