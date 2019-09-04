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
typedef  int XmlNodeType ;

/* Variables and functions */
#define  XmlNodeType_Attribute 138 
#define  XmlNodeType_CDATA 137 
#define  XmlNodeType_Comment 136 
#define  XmlNodeType_DocumentType 135 
#define  XmlNodeType_Element 134 
#define  XmlNodeType_EndElement 133 
#define  XmlNodeType_None 132 
#define  XmlNodeType_ProcessingInstruction 131 
#define  XmlNodeType_Text 130 
#define  XmlNodeType_Whitespace 129 
#define  XmlNodeType_XmlDeclaration 128 

__attribute__((used)) static const char *type_to_str(XmlNodeType type)
{
    static const char* type_names[] = {
        "XmlNodeType_None",
        "XmlNodeType_Element",
        "XmlNodeType_Attribute",
        "XmlNodeType_Text",
        "XmlNodeType_CDATA",
        "", "",
        "XmlNodeType_ProcessingInstruction",
        "XmlNodeType_Comment",
        "",
        "XmlNodeType_DocumentType",
        "", "",
        "XmlNodeType_Whitespace",
        "",
        "XmlNodeType_EndElement",
        "",
        "XmlNodeType_XmlDeclaration"
    };

    static const char unknown[] = "unknown";

    switch (type)
    {
    case XmlNodeType_None:
    case XmlNodeType_Element:
    case XmlNodeType_Attribute:
    case XmlNodeType_Text:
    case XmlNodeType_CDATA:
    case XmlNodeType_ProcessingInstruction:
    case XmlNodeType_Comment:
    case XmlNodeType_DocumentType:
    case XmlNodeType_Whitespace:
    case XmlNodeType_EndElement:
    case XmlNodeType_XmlDeclaration:
        return type_names[type];
    default:
        return unknown;
    }
}