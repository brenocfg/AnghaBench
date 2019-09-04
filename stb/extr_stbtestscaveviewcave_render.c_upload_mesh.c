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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_3__ {int num_quads; int /*<<< orphan*/  fbuf; int /*<<< orphan*/  fbuf_tex; int /*<<< orphan*/  vbuf; } ;
typedef  TYPE_1__ chunk_mesh ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER_ARB ; 
 int /*<<< orphan*/  GL_RGBA8UI ; 
 int /*<<< orphan*/  GL_STATIC_DRAW_ARB ; 
 int /*<<< orphan*/  GL_TEXTURE_BUFFER_ARB ; 
 int /*<<< orphan*/  glBindBufferARB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferDataARB (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenBuffersARB (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glTexBufferARB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void upload_mesh(chunk_mesh *cm, uint8 *build_buffer, uint8 *face_buffer)
{
   glGenBuffersARB(1, &cm->vbuf);
   glBindBufferARB(GL_ARRAY_BUFFER_ARB, cm->vbuf);
   glBufferDataARB(GL_ARRAY_BUFFER_ARB, cm->num_quads*4*sizeof(uint32), build_buffer, GL_STATIC_DRAW_ARB);
   glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

   glGenBuffersARB(1, &cm->fbuf);
   glBindBufferARB(GL_TEXTURE_BUFFER_ARB, cm->fbuf);
   glBufferDataARB(GL_TEXTURE_BUFFER_ARB, cm->num_quads*sizeof(uint32), face_buffer , GL_STATIC_DRAW_ARB);
   glBindBufferARB(GL_TEXTURE_BUFFER_ARB, 0);

   glGenTextures(1, &cm->fbuf_tex);
   glBindTexture(GL_TEXTURE_BUFFER_ARB, cm->fbuf_tex);
   glTexBufferARB(GL_TEXTURE_BUFFER_ARB, GL_RGBA8UI, cm->fbuf);
   glBindTexture(GL_TEXTURE_BUFFER_ARB, 0);
}