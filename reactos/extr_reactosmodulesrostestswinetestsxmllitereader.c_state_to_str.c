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
typedef  int XmlReadState ;

/* Variables and functions */
#define  XmlReadState_Closed 132 
#define  XmlReadState_EndOfFile 131 
#define  XmlReadState_Error 130 
#define  XmlReadState_Initial 129 
#define  XmlReadState_Interactive 128 

__attribute__((used)) static const char *state_to_str(XmlReadState state)
{
    static const char* state_names[] = {
        "XmlReadState_Initial",
        "XmlReadState_Interactive",
        "XmlReadState_Error",
        "XmlReadState_EndOfFile",
        "XmlReadState_Closed"
    };

    static const char unknown[] = "unknown";

    switch (state)
    {
    case XmlReadState_Initial:
    case XmlReadState_Interactive:
    case XmlReadState_Error:
    case XmlReadState_EndOfFile:
    case XmlReadState_Closed:
        return state_names[state];
    default:
        return unknown;
    }
}