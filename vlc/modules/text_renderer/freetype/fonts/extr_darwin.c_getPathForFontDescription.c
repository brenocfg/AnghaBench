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
typedef  int /*<<< orphan*/  CTFontDescriptorRef ;
typedef  int /*<<< orphan*/  CFURLRef ;
typedef  int /*<<< orphan*/  CFStringRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFURLCopyFileSystemPath (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTFontDescriptorCopyAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* FromCFString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCFStringEncodingUTF8 ; 
 int /*<<< orphan*/  kCFURLPOSIXPathStyle ; 
 int /*<<< orphan*/  kCTFontURLAttribute ; 

char* getPathForFontDescription(CTFontDescriptorRef fontDescriptor)
{
    CFURLRef url = CTFontDescriptorCopyAttribute(fontDescriptor, kCTFontURLAttribute);
    CFStringRef path = CFURLCopyFileSystemPath(url, kCFURLPOSIXPathStyle);
    char *retPath = FromCFString(path, kCFStringEncodingUTF8);
    CFRelease(path);
    CFRelease(url);
    return retPath;
}