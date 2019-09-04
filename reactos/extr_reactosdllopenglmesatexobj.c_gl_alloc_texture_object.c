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
struct gl_texture_object {int Name; int Dimensions; float MinMagThresh; int* Palette; int PaletteSize; struct gl_texture_object* Next; void* PaletteFormat; void* PaletteIntFormat; int /*<<< orphan*/  MagFilter; int /*<<< orphan*/  MinFilter; void* WrapT; void* WrapS; } ;
struct gl_shared_state {int /*<<< orphan*/  TexObjects; struct gl_texture_object* TexObjectList; } ;
typedef  int GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_NEAREST_MIPMAP_LINEAR ; 
 void* GL_REPEAT ; 
 void* GL_RGBA ; 
 int /*<<< orphan*/  HashInsert (int /*<<< orphan*/ ,int,struct gl_texture_object*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ calloc (int,int) ; 

struct gl_texture_object *
gl_alloc_texture_object( struct gl_shared_state *shared, GLuint name,
                         GLuint dimensions)
{
   struct gl_texture_object *obj;

   assert(dimensions >= 0 && dimensions <= 2);

   obj = (struct gl_texture_object *)
                     calloc(1,sizeof(struct gl_texture_object));
   if (obj) {
      /* init the non-zero fields */
      obj->Name = name;
      obj->Dimensions = dimensions;
      obj->WrapS = GL_REPEAT;
      obj->WrapT = GL_REPEAT;
      obj->MinFilter = GL_NEAREST_MIPMAP_LINEAR;
      obj->MagFilter = GL_LINEAR;
      obj->MinMagThresh = 0.0F;
      obj->Palette[0] = 255;
      obj->Palette[1] = 255;
      obj->Palette[2] = 255;
      obj->Palette[3] = 255;
      obj->PaletteSize = 1;
      obj->PaletteIntFormat = GL_RGBA;
      obj->PaletteFormat = GL_RGBA;

      /* insert into linked list */
      if (shared) {
         obj->Next = shared->TexObjectList;
         shared->TexObjectList = obj;
      }

      if (name > 0) {
         /* insert into hash table */
         HashInsert(shared->TexObjects, name, obj);
      }
   }
   return obj;
}