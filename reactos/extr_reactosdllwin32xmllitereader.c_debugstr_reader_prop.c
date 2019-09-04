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
typedef  size_t XmlReaderProperty ;

/* Variables and functions */
 size_t _XmlReaderProperty_Last ; 
 char const* wine_dbg_sprintf (char*,size_t) ; 

__attribute__((used)) static const char *debugstr_reader_prop(XmlReaderProperty prop)
{
    static const char * const prop_names[] =
    {
        "MultiLanguage",
        "ConformanceLevel",
        "RandomAccess",
        "XmlResolver",
        "DtdProcessing",
        "ReadState",
        "MaxElementDepth",
        "MaxEntityExpansion"
    };

    if (prop > _XmlReaderProperty_Last)
        return wine_dbg_sprintf("unknown property=%d", prop);

    return prop_names[prop];
}