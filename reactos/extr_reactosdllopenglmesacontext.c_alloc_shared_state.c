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
struct gl_shared_state {void* Default2D; void* Default1D; void* TexObjects; void* DisplayList; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteHashTable (void*) ; 
 void* NewHashTable () ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct gl_shared_state*) ; 
 void* gl_alloc_texture_object (struct gl_shared_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gl_free_texture_object (struct gl_shared_state*,void*) ; 

__attribute__((used)) static struct gl_shared_state *alloc_shared_state( void )
{
   struct gl_shared_state *ss;

   ss = (struct gl_shared_state*) calloc( 1, sizeof(struct gl_shared_state) );
   if (!ss)
      return NULL;

   ss->DisplayList = NewHashTable();

   ss->TexObjects = NewHashTable();

   /* Default Texture objects */
   ss->Default1D = gl_alloc_texture_object(ss, 0, 1);
   ss->Default2D = gl_alloc_texture_object(ss, 0, 2);

   if (!ss->DisplayList || !ss->TexObjects
       || !ss->Default1D || !ss->Default2D) {
      /* Ran out of memory at some point.  Free everything and return NULL */
      if (!ss->DisplayList)
         DeleteHashTable(ss->DisplayList);
      if (!ss->TexObjects)
         DeleteHashTable(ss->TexObjects);
      if (!ss->Default1D)
         gl_free_texture_object(ss, ss->Default1D);
      if (!ss->Default2D)
         gl_free_texture_object(ss, ss->Default2D);
      free(ss);
      return NULL;
   }
   else {
      return ss;
   }
}