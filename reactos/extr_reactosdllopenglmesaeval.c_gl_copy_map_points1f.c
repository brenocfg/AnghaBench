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
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int components (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 

GLfloat *gl_copy_map_points1f( GLenum target,
                               GLint ustride, GLint uorder,
                               const GLfloat *points )
{
   GLfloat *buffer, *p;
   GLuint i, k, size = components(target);

   if (!points || size==0) {
      return NULL;
   }

   buffer = (GLfloat *) malloc(uorder * size * sizeof(GLfloat));

   if(buffer) 
      for(i=0, p=buffer; i<uorder; i++, points+=ustride)
	for(k=0; k<size; k++)
	  *p++ = points[k];

   return buffer;
}