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
typedef  TYPE_1__* jpeg_saved_marker_ptr ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_3__ {scalar_t__ marker; int data_length; struct TYPE_3__* next; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ JPEG_APP0 ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static
cmsBool IsITUFax(jpeg_saved_marker_ptr ptr)
{
    while (ptr)
    {
        if (ptr -> marker == (JPEG_APP0 + 1) && ptr -> data_length > 5) {

            const char* data = (const char*) ptr -> data;

            if (strcmp(data, "G3FAX") == 0) return TRUE;
        }

        ptr = ptr -> next;
    }

    return FALSE;
}