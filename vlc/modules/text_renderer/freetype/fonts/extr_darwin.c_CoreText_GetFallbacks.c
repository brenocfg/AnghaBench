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
typedef  int /*<<< orphan*/  vlc_family_t ;
typedef  int /*<<< orphan*/  uni_char_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  littleEndianCodePoint ;
struct TYPE_8__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_9__ {int /*<<< orphan*/  family_map; int /*<<< orphan*/  p_families; } ;
typedef  TYPE_2__ filter_sys_t ;
typedef  int /*<<< orphan*/  UInt8 ;
typedef  int /*<<< orphan*/ * CTFontRef ;
typedef  int /*<<< orphan*/ * CTFontDescriptorRef ;
typedef  int /*<<< orphan*/ * CFStringRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFRangeMake (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CFStringCreateWithBytes (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CFStringCreateWithCString (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CTFontCopyFamilyName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CTFontCopyPostScriptName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CTFontCreateForString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CTFontCreateWithName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CTFontDescriptorCreateWithNameAndSize (int /*<<< orphan*/ *,int) ; 
 char* FromCFString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewFamily (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  OSSwapHostToLittleInt32 (int /*<<< orphan*/ ) ; 
 char* ToLower (char*) ; 
 int /*<<< orphan*/  addNewFontToFamily (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getPathForFontDescription (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFStringEncodingUTF32LE ; 
 int /*<<< orphan*/  kCFStringEncodingUTF8 ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * vlc_dictionary_value_for_key (int /*<<< orphan*/ *,char*) ; 

vlc_family_t *CoreText_GetFallbacks(filter_t *p_filter, const char *psz_family, uni_char_t codepoint)
{
    filter_sys_t *p_sys = p_filter->p_sys;
    if (unlikely(psz_family == NULL)) {
        return NULL;
    }

    vlc_family_t *p_family = NULL;
    CFStringRef postScriptFallbackFontname = NULL;
    CTFontDescriptorRef fallbackFontDescriptor = NULL;
    char *psz_lc_fallback = NULL;
    char *psz_fontPath = NULL;

    CFStringRef familyName = CFStringCreateWithCString(kCFAllocatorDefault,
                                                       psz_family,
                                                       kCFStringEncodingUTF8);
    CTFontRef font = CTFontCreateWithName(familyName, 0, NULL);
    uint32_t littleEndianCodePoint = OSSwapHostToLittleInt32(codepoint);
    CFStringRef codepointString = CFStringCreateWithBytes(kCFAllocatorDefault,
                                                          (const UInt8 *)&littleEndianCodePoint,
                                                          sizeof(littleEndianCodePoint),
                                                          kCFStringEncodingUTF32LE,
                                                          false);
    CTFontRef fallbackFont = CTFontCreateForString(font, codepointString, CFRangeMake(0,1));
    CFStringRef fallbackFontFamilyName = CTFontCopyFamilyName(fallbackFont);

    /* create a new family object */
    char *psz_fallbackFamilyName = FromCFString(fallbackFontFamilyName, kCFStringEncodingUTF8);
    if (psz_fallbackFamilyName == NULL) {
        msg_Warn(p_filter, "Failed to convert font family name CFString to C string");
        goto done;
    }
#ifndef NDEBUG
    msg_Dbg(p_filter, "Will deploy fallback font '%s'", psz_fallbackFamilyName);
#endif

    psz_lc_fallback = ToLower(psz_fallbackFamilyName);

    p_family = vlc_dictionary_value_for_key(&p_sys->family_map, psz_lc_fallback);
    if (p_family) {
        goto done;
    }

    p_family = NewFamily(p_filter, psz_lc_fallback, &p_sys->p_families, &p_sys->family_map, psz_lc_fallback);
    if (unlikely(!p_family)) {
        goto done;
    }

    postScriptFallbackFontname = CTFontCopyPostScriptName(fallbackFont);
    fallbackFontDescriptor = CTFontDescriptorCreateWithNameAndSize(postScriptFallbackFontname, 0.);
    psz_fontPath = getPathForFontDescription(fallbackFontDescriptor);

    /* check if the path is empty, which can happen in rare circumstances */
    if (psz_fontPath != NULL) {
        if (strcmp("", psz_fontPath) == 0) {
            goto done;
        }
    } else {
        goto done;
    }

    addNewFontToFamily(p_filter, fallbackFontDescriptor, strdup(psz_fontPath), p_family);

done:
    CFRelease(familyName);
    CFRelease(font);
    CFRelease(codepointString);
    CFRelease(fallbackFont);
    CFRelease(fallbackFontFamilyName);
    free(psz_fallbackFamilyName);
    free(psz_lc_fallback);
    free(psz_fontPath);
    if (postScriptFallbackFontname != NULL)
        CFRelease(postScriptFallbackFontname);
    if (fallbackFontDescriptor != NULL)
        CFRelease(fallbackFontDescriptor);
    return p_family;
}