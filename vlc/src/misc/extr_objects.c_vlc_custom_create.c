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
typedef  void vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 void* calloc (size_t,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlc_object_init (void*,void*,char const*) ; 

void *(vlc_custom_create)(vlc_object_t *parent, size_t length,
                          const char *typename)
{
    assert(length >= sizeof (vlc_object_t));

    vlc_object_t *obj = calloc(length, 1);
    if (unlikely(obj == NULL || vlc_object_init(obj, parent, typename))) {
        free(obj);
        obj = NULL;
    }
    return obj;
}