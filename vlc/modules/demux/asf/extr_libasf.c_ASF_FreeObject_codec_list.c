#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* codecs; } ;
struct TYPE_6__ {TYPE_2__ codec_list; } ;
typedef  TYPE_1__ asf_object_t ;
typedef  TYPE_2__ asf_object_codec_list_t ;
struct TYPE_8__ {struct TYPE_8__* p_information; struct TYPE_8__* psz_description; struct TYPE_8__* psz_name; struct TYPE_8__* p_next; } ;
typedef  TYPE_3__ asf_codec_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 

__attribute__((used)) static void ASF_FreeObject_codec_list( asf_object_t *p_obj )
{
    asf_object_codec_list_t *p_cl = &p_obj->codec_list;

    for( asf_codec_entry_t *codec = p_cl->codecs, *next;
         codec != NULL;
         codec = next )
    {
        next = codec->p_next;
        free( codec->psz_name );
        free( codec->psz_description );
        free( codec->p_information );
        free( codec );
    }
}