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
typedef  void hb_face_t ;
typedef  int /*<<< orphan*/  hb_blob_t ;

/* Variables and functions */
 scalar_t__ create_blob () ; 
 int /*<<< orphan*/  hb_blob_destroy (int /*<<< orphan*/ *) ; 
 void* hb_face_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
create_face (void)
{
  hb_blob_t *blob = (hb_blob_t *) create_blob ();
  hb_face_t *face = hb_face_create (blob, 0);
  hb_blob_destroy (blob);
  return face;
}