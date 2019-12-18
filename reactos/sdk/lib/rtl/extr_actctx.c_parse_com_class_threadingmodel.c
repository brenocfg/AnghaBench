#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ len; } ;
typedef  TYPE_1__ xmlstr_t ;
typedef  enum comclass_threadingmodel { ____Placeholder_comclass_threadingmodel } comclass_threadingmodel ;
typedef  char WCHAR ;

/* Variables and functions */
 int ThreadingModel_Apartment ; 
 int ThreadingModel_Both ; 
 int ThreadingModel_Free ; 
 int ThreadingModel_Neutral ; 
 int ThreadingModel_No ; 
 scalar_t__ xmlstr_cmp (TYPE_1__*,char const*) ; 

__attribute__((used)) static enum comclass_threadingmodel parse_com_class_threadingmodel(xmlstr_t *value)
{
    static const WCHAR apartW[] = {'A','p','a','r','t','m','e','n','t',0};
    static const WCHAR neutralW[] = {'N','e','u','t','r','a','l',0};
    static const WCHAR freeW[] = {'F','r','e','e',0};
    static const WCHAR bothW[] = {'B','o','t','h',0};

    if (value->len == 0) return ThreadingModel_No;
    if (xmlstr_cmp(value, apartW))
        return ThreadingModel_Apartment;
    else if (xmlstr_cmp(value, freeW))
        return ThreadingModel_Free;
    else if (xmlstr_cmp(value, bothW))
        return ThreadingModel_Both;
    else if (xmlstr_cmp(value, neutralW))
        return ThreadingModel_Neutral;
    else
        return ThreadingModel_No;
}