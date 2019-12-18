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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,void const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool decodeQtLanguageCode( uint16_t i_language_code, char *psz_iso,
                                  bool *b_mactables )
{
    static const char * psz_qt_to_iso639_2T_lower =
            "eng"    "fra"    "deu"    "ita"    "nld"
            "swe"    "spa"    "dan"    "por"    "nor" /* 5-9 */
            "heb"    "jpn"    "ara"    "fin"    "gre"
            "isl"    "mlt"    "tur"    "hrv"    "zho" /* 15-19 */
            "urd"    "hin"    "tha"    "kor"    "lit"
            "pol"    "hun"    "est"    "lav"    "sme" /* 25-29 */
            "fao"    "fas"    "rus"    "zho"    "nld" /* nld==flemish */
            "gle"    "sqi"    "ron"    "ces"    "slk" /* 35-39 */
            "slv"    "yid"    "srp"    "mkd"    "bul"
            "ukr"    "bel"    "uzb"    "kaz"    "aze" /* 45-49 */
            "aze"    "hye"    "kat"    "mol"    "kir"
            "tgk"    "tuk"    "mon"    "mon"    "pus" /* 55-59 */
            "kur"    "kas"    "snd"    "bod"    "nep"
            "san"    "mar"    "ben"    "asm"    "guj" /* 65-69 */
            "pan"    "ori"    "mal"    "kan"    "tam"
            "tel"    "sin"    "mya"    "khm"    "lao" /* 75-79 */
            "vie"    "ind"    "tgl"    "msa"    "msa"
            "amh"    "tir"    "orm"    "som"    "swa" /* 85-89 */
            "kin"    "run"    "nya"    "mlg"    "epo" /* 90-94 */
            ;

    static const char * psz_qt_to_iso639_2T_upper =
            "cym"    "eus"    "cat"    "lat"    "que" /* 128-132 */
            "grn"    "aym"    "tat"    "uig"    "dzo"
            "jaw"    "sun"    "glg"    "afr"    "bre" /* 138-142 */
            "iku"    "gla"    "glv"    "gle"    "ton"
            "gre"                                     /* 148 */
            ;

    if ( i_language_code < 0x400 || i_language_code == 0x7FFF )
    {
        const void *p_data;
        *b_mactables = true;
        if ( i_language_code <= 94 )
        {
            p_data = psz_qt_to_iso639_2T_lower + i_language_code * 3;
        }
        else if ( i_language_code >= 128 && i_language_code <= 148 )
        {
            i_language_code -= 128;
            p_data = psz_qt_to_iso639_2T_upper + i_language_code * 3;
        }
        else
            return false;
        memcpy( psz_iso, p_data, 3 );
    }
    else
    {
        *b_mactables = false;
        /*
         * to build code: ( ( 'f' - 0x60 ) << 10 ) | ( ('r' - 0x60) << 5 ) | ('a' - 0x60)
         */
        if( i_language_code == 0x55C4 ) /* "und" */
        {
            memset( psz_iso, 0, 3 );
            return false;
        }

        for( unsigned i = 0; i < 3; i++ )
            psz_iso[i] = ( ( i_language_code >> ( (2-i)*5 ) )&0x1f ) + 0x60;
    }
    return true;
}