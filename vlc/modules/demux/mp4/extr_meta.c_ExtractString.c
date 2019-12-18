#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* p_binary; int /*<<< orphan*/  p_data; } ;
struct TYPE_10__ {scalar_t__ i_type; TYPE_1__ data; } ;
struct TYPE_9__ {int /*<<< orphan*/  i_blob; scalar_t__ p_blob; } ;
typedef  TYPE_3__ MP4_Box_t ;

/* Variables and functions */
 scalar_t__ ATOM_data ; 
 int /*<<< orphan*/  BOXDATA (TYPE_3__*) ; 
 int /*<<< orphan*/  EnsureUTF8 (char*) ; 
 TYPE_3__* MP4_BoxGet (TYPE_3__*,char*) ; 
 char* StringConvert (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (char*) ; 
 char* strndup (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char * ExtractString( MP4_Box_t *p_box )
{
    if ( p_box->i_type == ATOM_data )
        return StringConvert( p_box->data.p_data );

    MP4_Box_t *p_data = MP4_BoxGet( p_box, "data" );
    if ( p_data )
        return StringConvert( BOXDATA(p_data) );
    else if ( p_box->data.p_binary && p_box->data.p_binary->p_blob )
    {
        char *psz_utf = strndup( p_box->data.p_binary->p_blob,
                                 p_box->data.p_binary->i_blob );
        if (likely( psz_utf ))
            EnsureUTF8( psz_utf );
        return psz_utf;
    }
    else
        return NULL;
}