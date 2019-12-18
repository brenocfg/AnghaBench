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
struct TYPE_5__ {int /*<<< orphan*/  xml; } ;
typedef  TYPE_2__ xml_reader_sys_t ;
typedef  int /*<<< orphan*/  xmlTextReaderPtr ;
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int /*<<< orphan*/ * xmlTextReaderConstName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlTextReaderConstValue (int /*<<< orphan*/ ) ; 
 int xmlTextReaderMoveToNextAttribute (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *ReaderNextAttr( xml_reader_t *p_reader, const char **pval )
{
    xml_reader_sys_t *p_sys = p_reader->p_sys;
    xmlTextReaderPtr xml = p_sys->xml;
    const xmlChar *name, *value;

    if( xmlTextReaderMoveToNextAttribute( xml ) != 1
     || (name = xmlTextReaderConstName( xml )) == NULL
     || (value = xmlTextReaderConstValue( xml )) == NULL )
        return NULL;

    *pval = (const char *)value;
    return (const char *)name;
}