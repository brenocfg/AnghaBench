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
typedef  int /*<<< orphan*/ * CFStringRef ;
typedef  int /*<<< orphan*/ * CFMutableArrayRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFArrayAppendValue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFArrayCreateMutable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFStringCreateWithCString (int /*<<< orphan*/ ,char const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFStringEncodingASCII ; 
 int /*<<< orphan*/  kCFTypeArrayCallBacks ; 

__attribute__((used)) static CFMutableArrayRef alpnToCFArray(const char *const *alpn)
{
    CFMutableArrayRef alpnValues =
            CFArrayCreateMutable(kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks);

    for (size_t i = 0; alpn[i] != NULL; i++) {
        CFStringRef alpnVal =
                CFStringCreateWithCString(kCFAllocatorDefault, alpn[i], kCFStringEncodingASCII);
        if (alpnVal == NULL) {
            // Failed to convert the ALPN value to CFString, error out.
            CFRelease(alpnValues);
            return NULL;
        }
        CFArrayAppendValue(alpnValues, alpnVal);
        CFRelease(alpnVal);
    }
    return alpnValues;
}