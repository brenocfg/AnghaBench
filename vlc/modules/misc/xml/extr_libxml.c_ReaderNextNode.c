#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ xml_reader_t ;
struct TYPE_5__ {char* node; int /*<<< orphan*/  xml; } ;
typedef  TYPE_2__ xml_reader_sys_t ;
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int XML_READER_ENDELEM ; 
 int XML_READER_ERROR ; 
 int XML_READER_NONE ; 
 int XML_READER_STARTELEM ; 
 int XML_READER_TEXT ; 
#define  XML_READER_TYPE_CDATA 131 
#define  XML_READER_TYPE_ELEMENT 130 
#define  XML_READER_TYPE_END_ELEMENT 129 
#define  XML_READER_TYPE_TEXT 128 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlTextReaderConstName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlTextReaderConstValue (int /*<<< orphan*/ ) ; 
 int xmlTextReaderNodeType (int /*<<< orphan*/ ) ; 
 int xmlTextReaderRead (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ReaderNextNode( xml_reader_t *p_reader, const char **pval )
{
    xml_reader_sys_t *p_sys = p_reader->p_sys;
    const xmlChar *node;
    int ret;

    free( p_sys->node );
    p_sys->node = NULL;

skip:
    switch( xmlTextReaderRead( p_sys->xml ) )
    {
        case 0: /* EOF */
            return XML_READER_NONE;
        case -1: /* error */
            return XML_READER_ERROR;
    }

    switch( xmlTextReaderNodeType( p_sys->xml ) )
    {
        case XML_READER_TYPE_ELEMENT:
            node = xmlTextReaderConstName( p_sys->xml );
            ret = XML_READER_STARTELEM;
            break;

        case XML_READER_TYPE_END_ELEMENT:
            node = xmlTextReaderConstName( p_sys->xml );
            ret = XML_READER_ENDELEM;
            break;

        case XML_READER_TYPE_CDATA:
        case XML_READER_TYPE_TEXT:
            node = xmlTextReaderConstValue( p_sys->xml );
            ret = XML_READER_TEXT;
            break;

        case -1:
            return XML_READER_ERROR;

        default:
            goto skip;
    }

    if( unlikely(node == NULL) )
        return XML_READER_ERROR;

    p_sys->node = strdup( (const char *)node );
    if( pval != NULL )
        *pval = p_sys->node;
    return likely(p_sys->node != NULL) ? ret : XML_READER_ERROR;
}