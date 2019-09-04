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
typedef  int /*<<< orphan*/  xml_encoding ;
typedef  scalar_t__ UINT ;
struct TYPE_3__ {scalar_t__ cp; int /*<<< orphan*/  enc; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  XmlEncoding_Unknown ; 
 TYPE_1__* xml_encoding_map ; 

xml_encoding get_encoding_from_codepage(UINT codepage)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(xml_encoding_map); i++)
    {
        if (xml_encoding_map[i].cp == codepage) return xml_encoding_map[i].enc;
    }
    return XmlEncoding_Unknown;
}