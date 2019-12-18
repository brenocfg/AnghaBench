#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  p_module; } ;
typedef  TYPE_1__ xml_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  module_need (TYPE_1__*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_1__*) ; 

xml_t *xml_Create( vlc_object_t *p_this )
{
    xml_t *p_xml;

    p_xml = vlc_custom_create( p_this, sizeof( *p_xml ), "xml" );

    p_xml->p_module = module_need( p_xml, "xml", NULL, false );
    if( !p_xml->p_module )
    {
        vlc_object_delete(p_xml);
        msg_Err( p_this, "XML provider not found" );
        return NULL;
    }

    return p_xml;
}