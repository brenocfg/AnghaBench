#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  char WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  daylightBias; int /*<<< orphan*/  daylightDate; int /*<<< orphan*/  standardBias; int /*<<< orphan*/  standardDate; int /*<<< orphan*/  bias; } ;
struct TYPE_5__ {int /*<<< orphan*/  DaylightBias; int /*<<< orphan*/  DaylightDate; int /*<<< orphan*/  StandardBias; int /*<<< orphan*/  StandardDate; int /*<<< orphan*/  Bias; } ;
typedef  TYPE_1__ TIME_ZONE_INFORMATION ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ DateInstance ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FALSE ; 
 int GetLocaleInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/  const,char*,int) ; 
 int /*<<< orphan*/  GetTimeZoneInformation (TYPE_1__*) ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
#define  LOCALE_SDAYNAME1 146 
#define  LOCALE_SDAYNAME2 145 
#define  LOCALE_SDAYNAME3 144 
#define  LOCALE_SDAYNAME4 143 
#define  LOCALE_SDAYNAME5 142 
#define  LOCALE_SDAYNAME6 141 
#define  LOCALE_SDAYNAME7 140 
#define  LOCALE_SMONTHNAME1 139 
#define  LOCALE_SMONTHNAME10 138 
#define  LOCALE_SMONTHNAME11 137 
#define  LOCALE_SMONTHNAME12 136 
#define  LOCALE_SMONTHNAME2 135 
#define  LOCALE_SMONTHNAME3 134 
#define  LOCALE_SMONTHNAME4 133 
#define  LOCALE_SMONTHNAME5 132 
#define  LOCALE_SMONTHNAME6 131 
#define  LOCALE_SMONTHNAME7 130 
#define  LOCALE_SMONTHNAME8 129 
#define  LOCALE_SMONTHNAME9 128 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELCID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MS_PER_MINUTE ; 
 double NAN ; 
 int /*<<< orphan*/  SORT_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_ENGLISH_US ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ TRUE ; 
 int atoiW (char*) ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 scalar_t__ isspaceW (char) ; 
 char* jsstr_flatten (int /*<<< orphan*/ *) ; 
 int jsstr_length (int /*<<< orphan*/ *) ; 
 scalar_t__ make_date (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_day (int,int,int) ; 
 int /*<<< orphan*/  make_time (int,int,int,int) ; 
 int /*<<< orphan*/  strncmpiW (char*,char*,int) ; 
 double time_clip (scalar_t__) ; 
 char toupperW (char const) ; 
 double utc (double,TYPE_2__*) ; 

__attribute__((used)) static inline HRESULT date_parse(jsstr_t *input_str, double *ret) {
    static const DWORD string_ids[] = { LOCALE_SMONTHNAME12, LOCALE_SMONTHNAME11,
        LOCALE_SMONTHNAME10, LOCALE_SMONTHNAME9, LOCALE_SMONTHNAME8,
        LOCALE_SMONTHNAME7, LOCALE_SMONTHNAME6, LOCALE_SMONTHNAME5,
        LOCALE_SMONTHNAME4, LOCALE_SMONTHNAME3, LOCALE_SMONTHNAME2,
        LOCALE_SMONTHNAME1, LOCALE_SDAYNAME7, LOCALE_SDAYNAME1,
        LOCALE_SDAYNAME2, LOCALE_SDAYNAME3, LOCALE_SDAYNAME4,
        LOCALE_SDAYNAME5, LOCALE_SDAYNAME6 };
    WCHAR *strings[ARRAY_SIZE(string_ids)];
    WCHAR *parse;
    int input_len, parse_len = 0, nest_level = 0, i, size;
    int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0;
    int ms = 0, offset = 0, hour_adjust = 0;
    BOOL set_year = FALSE, set_month = FALSE, set_day = FALSE, set_hour = FALSE;
    BOOL set_offset = FALSE, set_era = FALSE, ad = TRUE, set_am = FALSE, am = TRUE;
    BOOL set_hour_adjust = TRUE;
    TIME_ZONE_INFORMATION tzi;
    const WCHAR *input;
    DateInstance di;
    DWORD lcid_en;

    input_len = jsstr_length(input_str);
    input = jsstr_flatten(input_str);
    if(!input)
        return E_OUTOFMEMORY;

    for(i=0; i<input_len; i++) {
        if(input[i] == '(') nest_level++;
        else if(input[i] == ')') {
            nest_level--;
            if(nest_level<0) {
                *ret = NAN;
                return S_OK;
            }
        }
        else if(!nest_level) parse_len++;
    }

    parse = heap_alloc((parse_len+1)*sizeof(WCHAR));
    if(!parse)
        return E_OUTOFMEMORY;
    nest_level = 0;
    parse_len = 0;
    for(i=0; i<input_len; i++) {
        if(input[i] == '(') nest_level++;
        else if(input[i] == ')') nest_level--;
        else if(!nest_level) parse[parse_len++] = toupperW(input[i]);
    }
    parse[parse_len] = 0;

    GetTimeZoneInformation(&tzi);
    di.bias = tzi.Bias;
    di.standardDate = tzi.StandardDate;
    di.standardBias = tzi.StandardBias;
    di.daylightDate = tzi.DaylightDate;
    di.daylightBias = tzi.DaylightBias;

    /* FIXME: Cache strings */
    lcid_en = MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT);
    for(i=0; i<ARRAY_SIZE(string_ids); i++) {
        size = GetLocaleInfoW(lcid_en, string_ids[i], NULL, 0);
        strings[i] = heap_alloc((size+1)*sizeof(WCHAR));
        if(!strings[i]) {
            i--;
            while(i-- >= 0)
                heap_free(strings[i]);
            heap_free(parse);
            return E_OUTOFMEMORY;
        }
        GetLocaleInfoW(lcid_en, string_ids[i], strings[i], size);
    }

    for(i=0; i<parse_len;) {
        while(isspaceW(parse[i])) i++;
        if(parse[i] == ',') {
            while(parse[i] == ',') i++;
            continue;
        }

        if(parse[i]>='0' && parse[i]<='9') {
            int tmp = atoiW(&parse[i]);
            while(parse[i]>='0' && parse[i]<='9') i++;
            while(isspaceW(parse[i])) i++;

            if(parse[i] == ':') {
                /* Time */
                if(set_hour) break;
                set_hour = TRUE;

                hour = tmp;

                while(parse[i] == ':') i++;
                while(isspaceW(parse[i])) i++;
                if(parse[i]>='0' && parse[i]<='9') {
                    min = atoiW(&parse[i]);
                    while(parse[i]>='0' && parse[i]<='9') i++;
                }

                while(isspaceW(parse[i])) i++;
                while(parse[i] == ':') i++;
                while(isspaceW(parse[i])) i++;
                if(parse[i]>='0' && parse[i]<='9') {
                    sec = atoiW(&parse[i]);
                    while(parse[i]>='0' && parse[i]<='9') i++;
                }
            }
            else if(parse[i]=='-' || parse[i]=='/') {
                /* Short or long date */
                if(set_day || set_month || set_year) break;
                set_day = TRUE;
                set_month = TRUE;
                set_year = TRUE;

                month = tmp-1;

                while(isspaceW(parse[i])) i++;
                while(parse[i]=='-' || parse[i]=='/') i++;
                while(isspaceW(parse[i])) i++;
                if(parse[i]<'0' || parse[i]>'9') break;
                day = atoiW(&parse[i]);
                while(parse[i]>='0' && parse[i]<='9') i++;

                while(parse[i]=='-' || parse[i]=='/') i++;
                while(isspaceW(parse[i])) i++;
                if(parse[i]<'0' || parse[i]>'9') break;
                year = atoiW(&parse[i]);
                while(parse[i]>='0' && parse[i]<='9') i++;

                if(tmp >= 70){
                        /* long date */
                        month = day - 1;
                        day = year;
                        year = tmp;
		}
            }
            else if(tmp<0) break;
            else if(tmp<70) {
                /* Day */
                if(set_day) break;
                set_day = TRUE;
                day = tmp;
            }
            else {
                /* Year */
                if(set_year) break;
                set_year = TRUE;
                year = tmp;
            }
        }
        else if(parse[i]=='+' || parse[i]=='-') {
            /* Timezone offset */
            BOOL positive = TRUE;

            if(set_offset && set_hour_adjust) break;
            set_offset = TRUE;
            set_hour_adjust = FALSE;

            if(parse[i] == '-')  positive = FALSE;

            i++;
            while(isspaceW(parse[i])) i++;
            if(parse[i]<'0' || parse[i]>'9') break;
            offset = atoiW(&parse[i]);
            while(parse[i]>='0' && parse[i]<='9') i++;

            if(offset<24) offset *= 60;
            else offset = (offset/100)*60 + offset%100;

            if(positive) offset = -offset;

        }
        else {
            if(parse[i]<'A' || parse[i]>'Z') break;
            else if(parse[i]=='B' && (parse[i+1]=='C' ||
                        (parse[i+1]=='.' && parse[i+2]=='C'))) {
                /* AD/BC */
                if(set_era) break;
                set_era = TRUE;
                ad = FALSE;

                i++;
                if(parse[i] == '.') i++;
                i++;
                if(parse[i] == '.') i++;
            }
            else if(parse[i]=='A' && (parse[i+1]=='D' ||
                        (parse[i+1]=='.' && parse[i+2]=='D'))) {
                /* AD/BC */
                if(set_era) break;
                set_era = TRUE;

                i++;
                if(parse[i] == '.') i++;
                i++;
                if(parse[i] == '.') i++;
            }
            else if(parse[i+1]<'A' || parse[i+1]>'Z') {
                /* Timezone */
                if(set_offset) break;
                set_offset = TRUE;

                if(parse[i] <= 'I') hour_adjust = parse[i]-'A'+2;
                else if(parse[i] == 'J') break;
                else if(parse[i] <= 'M') hour_adjust = parse[i]-'K'+11;
                else if(parse[i] <= 'Y') hour_adjust = parse[i]-'N';
                else hour_adjust = 1;

                i++;
                if(parse[i] == '.') i++;
            }
            else if(parse[i]=='A' && parse[i+1]=='M') {
                /* AM/PM */
                if(set_am) break;
                set_am = TRUE;
                am = TRUE;
                i += 2;
            }
            else if(parse[i]=='P' && parse[i+1]=='M') {
                /* AM/PM */
                if(set_am) break;
                set_am = TRUE;
                am = FALSE;
                i += 2;
            }
            else if((parse[i]=='U' && parse[i+1]=='T' && parse[i+2]=='C')
                    || (parse[i]=='G' && parse[i+1]=='M' && parse[i+2]=='T')) {
                /* Timezone */
                if(set_offset) break;
                set_offset = TRUE;
                set_hour_adjust = FALSE;

                i += 3;
            }
            else {
                /* Month or garbage */
                unsigned int j;

                for(size=i; parse[size]>='A' && parse[size]<='Z'; size++);
                size -= i;

                for(j=0; j<ARRAY_SIZE(string_ids); j++)
                    if(!strncmpiW(&parse[i], strings[j], size)) break;

                if(j < 12) {
                    if(set_month) break;
                    set_month = TRUE;
                    month = 11-j;
                }
                else if(j == ARRAY_SIZE(string_ids)) break;

                i += size;
            }
        }
    }

    if(i == parse_len && set_year && set_month && set_day && (!set_am || hour<13)) {
        if(set_am) {
            if(hour == 12) hour = 0;
            if(!am) hour += 12;
        }

        if(!ad) year = -year+1;
        else if(year<100) year += 1900;

        *ret = time_clip(make_date(make_day(year, month, day),
                    make_time(hour+hour_adjust, min, sec, ms)) + offset*MS_PER_MINUTE);

        if(set_hour_adjust)
            *ret = utc(*ret, &di);
    }else {
        *ret = NAN;
    }

    for(i=0; i<ARRAY_SIZE(string_ids); i++)
        heap_free(strings[i]);
    heap_free(parse);

    return S_OK;
}