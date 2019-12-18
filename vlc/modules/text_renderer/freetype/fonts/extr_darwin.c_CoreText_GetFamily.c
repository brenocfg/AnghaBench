#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const vlc_family_t ;
struct TYPE_8__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_9__ {int /*<<< orphan*/  family_map; int /*<<< orphan*/  p_families; } ;
typedef  TYPE_2__ filter_sys_t ;
typedef  int /*<<< orphan*/ * CTFontDescriptorRef ;
typedef  int /*<<< orphan*/ * CTFontCollectionRef ;
typedef  int /*<<< orphan*/ * CFStringRef ;
typedef  int /*<<< orphan*/ * CFMutableDictionaryRef ;
typedef  scalar_t__ CFIndex ;
typedef  int /*<<< orphan*/ * CFArrayRef ;

/* Variables and functions */
 int /*<<< orphan*/ * CFArrayCreate (int /*<<< orphan*/ ,void const**,size_t const,int /*<<< orphan*/ *) ; 
 scalar_t__ CFArrayGetCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFArrayGetValueAtIndex (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CFDictionaryAddValue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFDictionaryCreateMutable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFStringCreateWithCString (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CTFontCollectionCreateMatchingFontDescriptors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CTFontCollectionCreateWithFontDescriptors (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CTFontDescriptorCreateWithAttributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FREENULL (char*) ; 
 int /*<<< orphan*/  const* NewFamily (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 char* ToLower (char const*) ; 
 int /*<<< orphan*/  addNewFontToFamily (TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getPathForFontDescription (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFStringEncodingUTF8 ; 
 int /*<<< orphan*/ * kCTFontDisplayNameAttribute ; 
 int /*<<< orphan*/ * kCTFontFamilyNameAttribute ; 
 int /*<<< orphan*/ * kCTFontNameAttribute ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  const* vlc_dictionary_value_for_key (int /*<<< orphan*/ *,char*) ; 

const vlc_family_t *CoreText_GetFamily(filter_t *p_filter, const char *psz_family)
{
    filter_sys_t *p_sys = p_filter->p_sys;

    if (unlikely(psz_family == NULL)) {
        return NULL;
    }

    char *psz_lc = ToLower(psz_family);
    if (unlikely(!psz_lc)) {
        return NULL;
    }

    /* let's double check if we have parsed this family already */
    vlc_family_t *p_family = vlc_dictionary_value_for_key(&p_sys->family_map, psz_lc);
    if (p_family) {
        free(psz_lc);
        return p_family;
    }

    CTFontCollectionRef coreTextFontCollection = NULL;
    CFArrayRef matchedFontDescriptions = NULL;

    /* we search for family name, display name and name to find them all */
    const size_t numberOfAttributes = 3;
    CTFontDescriptorRef coreTextFontDescriptors[numberOfAttributes];
    CFMutableDictionaryRef coreTextAttributes[numberOfAttributes];
    CFStringRef attributeNames[numberOfAttributes] = {
        kCTFontFamilyNameAttribute,
        kCTFontDisplayNameAttribute,
        kCTFontNameAttribute,
    };

#ifndef NDEBUG
    msg_Dbg(p_filter, "Creating new family for '%s'", psz_family);
#endif

    CFStringRef familyName = CFStringCreateWithCString(kCFAllocatorDefault,
                                                       psz_family,
                                                       kCFStringEncodingUTF8);
    for (size_t x = 0; x < numberOfAttributes; x++) {
        coreTextAttributes[x] = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, NULL, NULL);
        CFDictionaryAddValue(coreTextAttributes[x], attributeNames[x], familyName);
        coreTextFontDescriptors[x] = CTFontDescriptorCreateWithAttributes(coreTextAttributes[x]);
    }

    CFArrayRef coreTextFontDescriptorsArray = CFArrayCreate(kCFAllocatorDefault,
                                                            (const void **)&coreTextFontDescriptors,
                                                            numberOfAttributes, NULL);

    coreTextFontCollection = CTFontCollectionCreateWithFontDescriptors(coreTextFontDescriptorsArray, 0);
    if (coreTextFontCollection == NULL) {
        msg_Warn(p_filter,"CTFontCollectionCreateWithFontDescriptors (1) failed!");
        goto end;
    }

    matchedFontDescriptions = CTFontCollectionCreateMatchingFontDescriptors(coreTextFontCollection);
    if (matchedFontDescriptions == NULL) {
        msg_Warn(p_filter, "CTFontCollectionCreateMatchingFontDescriptors (2) failed!");
        goto end;
    }

    CFIndex numberOfFoundFontDescriptions = CFArrayGetCount(matchedFontDescriptions);

    char *path = NULL;

    /* create a new family object */
    p_family = NewFamily(p_filter, psz_lc, &p_sys->p_families, &p_sys->family_map, psz_lc);
    if (unlikely(!p_family)) {
        goto end;
    }

    for (CFIndex i = 0; i < numberOfFoundFontDescriptions; i++) {
        CTFontDescriptorRef iter = CFArrayGetValueAtIndex(matchedFontDescriptions, i);
        path = getPathForFontDescription(iter);

        /* check if the path is empty, which can happen in rare circumstances */
        if (path == NULL || *path == '\0') {
            FREENULL(path);
            continue;
        }

        addNewFontToFamily(p_filter, iter, path, p_family);
    }

end:
    if (matchedFontDescriptions != NULL) {
        CFRelease(matchedFontDescriptions);
    }
    if (coreTextFontCollection != NULL) {
        CFRelease(coreTextFontCollection);
    }

    for (size_t x = 0; x < numberOfAttributes; x++) {
        CFRelease(coreTextAttributes[x]);
        CFRelease(coreTextFontDescriptors[x]);
    }

    CFRelease(coreTextFontDescriptorsArray);
    CFRelease(familyName);
    free(psz_lc);

    return p_family;
}