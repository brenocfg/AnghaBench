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
struct TYPE_3__ {int array_length; int bytes_per_element; int type; scalar_t__ default_value; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ stbvox_uniform_info ;
typedef  int /*<<< orphan*/  GLint ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER_ARB ; 
 int /*<<< orphan*/  GL_RG32F ; 
 int /*<<< orphan*/  GL_RGB32F ; 
 int /*<<< orphan*/  GL_RGBA32F ; 
 int /*<<< orphan*/  GL_STATIC_DRAW_ARB ; 
 scalar_t__ GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_TEXTURE_BUFFER_ARB ; 
#define  STBVOX_UNIFORM_TYPE_vec2 130 
#define  STBVOX_UNIFORM_TYPE_vec3 129 
#define  STBVOX_UNIFORM_TYPE_vec4 128 
 int STBVOX_UNIFORM_color_table ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glActiveTextureARB (scalar_t__) ; 
 int /*<<< orphan*/  glBindBufferARB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferDataARB (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenBuffersARB (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexBufferARB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_prog ; 
 int /*<<< orphan*/  stbglUniform1i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stbglUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stbgl_find_uniform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stbvox_get_uniform_info (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * unibuf ; 
 int /*<<< orphan*/ * unitex ; 

void make_texture_buffer_for_uniform(int uniform, int slot)
{
   GLenum type;
   stbvox_uniform_info raw, *ui=&raw;
   GLint uloc;
   
   stbvox_get_uniform_info(ui, uniform);
   uloc = stbgl_find_uniform(main_prog, ui->name);

   if (uniform == STBVOX_UNIFORM_color_table)
      ((float *)ui->default_value)[63*4+3] = 2.0f; // emissive

   glGenBuffersARB(1, &unibuf[uniform]);
   glBindBufferARB(GL_ARRAY_BUFFER_ARB, unibuf[uniform]);
   glBufferDataARB(GL_ARRAY_BUFFER_ARB, ui->array_length * ui->bytes_per_element, ui->default_value, GL_STATIC_DRAW_ARB);
   glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

   glGenTextures(1, &unitex[uniform]);
   glBindTexture(GL_TEXTURE_BUFFER_ARB, unitex[uniform]);
   switch (ui->type) {
      case STBVOX_UNIFORM_TYPE_vec2: type = GL_RG32F; break;
      case STBVOX_UNIFORM_TYPE_vec3: type = GL_RGB32F; break;
      case STBVOX_UNIFORM_TYPE_vec4: type = GL_RGBA32F; break;
      default: assert(0);
   }
   glTexBufferARB(GL_TEXTURE_BUFFER_ARB, type, unibuf[uniform]);
   glBindTexture(GL_TEXTURE_BUFFER_ARB, 0);

   glActiveTextureARB(GL_TEXTURE0 + slot);
   glBindTexture(GL_TEXTURE_BUFFER_ARB, unitex[uniform]);
   glActiveTextureARB(GL_TEXTURE0);

   stbglUseProgram(main_prog);
   stbglUniform1i(uloc, slot);
}