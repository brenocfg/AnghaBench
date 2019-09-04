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
typedef  int LCTYPE ;
typedef  scalar_t__ LCID ;

/* Variables and functions */
 scalar_t__ ConvertDefaultLocale (scalar_t__) ; 
#define  LOCALE_FONTSIGNATURE 223 
#define  LOCALE_ICALENDARTYPE 222 
#define  LOCALE_ICENTURY 221 
#define  LOCALE_ICOUNTRY 220 
#define  LOCALE_ICURRDIGITS 219 
#define  LOCALE_ICURRENCY 218 
#define  LOCALE_IDATE 217 
#define  LOCALE_IDAYLZERO 216 
#define  LOCALE_IDEFAULTANSICODEPAGE 215 
#define  LOCALE_IDEFAULTCODEPAGE 214 
#define  LOCALE_IDEFAULTEBCDICCODEPAGE 213 
#define  LOCALE_IDEFAULTMACCODEPAGE 212 
#define  LOCALE_IDEFAULTUNIXCODEPAGE 211 
#define  LOCALE_IDIGITS 210 
#define  LOCALE_IDIGITSUBSTITUTION 209 
#define  LOCALE_IFIRSTDAYOFWEEK 208 
#define  LOCALE_IFIRSTWEEKOFYEAR 207 
#define  LOCALE_IINTLCURRDIGITS 206 
#define  LOCALE_ILDATE 205 
#define  LOCALE_ILZERO 204 
#define  LOCALE_IMEASURE 203 
#define  LOCALE_IMONLZERO 202 
#define  LOCALE_INEGCURR 201 
#define  LOCALE_INEGNUMBER 200 
#define  LOCALE_INEGSEPBYSPACE 199 
#define  LOCALE_INEGSIGNPOSN 198 
#define  LOCALE_INEGSYMPRECEDES 197 
#define  LOCALE_IOPTIONALCALENDAR 196 
#define  LOCALE_IPAPERSIZE 195 
#define  LOCALE_IPOSSEPBYSPACE 194 
#define  LOCALE_IPOSSIGNPOSN 193 
#define  LOCALE_IPOSSYMPRECEDES 192 
#define  LOCALE_ITIME 191 
#define  LOCALE_ITIMEMARKPOSN 190 
#define  LOCALE_ITLZERO 189 
 scalar_t__ LOCALE_NEUTRAL ; 
#define  LOCALE_S1159 188 
#define  LOCALE_S2359 187 
#define  LOCALE_SABBREVDAYNAME1 186 
#define  LOCALE_SABBREVDAYNAME2 185 
#define  LOCALE_SABBREVDAYNAME3 184 
#define  LOCALE_SABBREVDAYNAME4 183 
#define  LOCALE_SABBREVDAYNAME5 182 
#define  LOCALE_SABBREVDAYNAME6 181 
#define  LOCALE_SABBREVDAYNAME7 180 
#define  LOCALE_SABBREVMONTHNAME1 179 
#define  LOCALE_SABBREVMONTHNAME10 178 
#define  LOCALE_SABBREVMONTHNAME11 177 
#define  LOCALE_SABBREVMONTHNAME12 176 
#define  LOCALE_SABBREVMONTHNAME13 175 
#define  LOCALE_SABBREVMONTHNAME2 174 
#define  LOCALE_SABBREVMONTHNAME3 173 
#define  LOCALE_SABBREVMONTHNAME4 172 
#define  LOCALE_SABBREVMONTHNAME5 171 
#define  LOCALE_SABBREVMONTHNAME6 170 
#define  LOCALE_SABBREVMONTHNAME7 169 
#define  LOCALE_SABBREVMONTHNAME8 168 
#define  LOCALE_SABBREVMONTHNAME9 167 
#define  LOCALE_SCURRENCY 166 
#define  LOCALE_SDATE 165 
#define  LOCALE_SDAYNAME1 164 
#define  LOCALE_SDAYNAME2 163 
#define  LOCALE_SDAYNAME3 162 
#define  LOCALE_SDAYNAME4 161 
#define  LOCALE_SDAYNAME5 160 
#define  LOCALE_SDAYNAME6 159 
#define  LOCALE_SDAYNAME7 158 
#define  LOCALE_SDECIMAL 157 
#define  LOCALE_SGROUPING 156 
#define  LOCALE_SINTLSYMBOL 155 
#define  LOCALE_SLONGDATE 154 
#define  LOCALE_SMONDECIMALSEP 153 
#define  LOCALE_SMONGROUPING 152 
#define  LOCALE_SMONTHNAME1 151 
#define  LOCALE_SMONTHNAME10 150 
#define  LOCALE_SMONTHNAME11 149 
#define  LOCALE_SMONTHNAME12 148 
#define  LOCALE_SMONTHNAME13 147 
#define  LOCALE_SMONTHNAME2 146 
#define  LOCALE_SMONTHNAME3 145 
#define  LOCALE_SMONTHNAME4 144 
#define  LOCALE_SMONTHNAME5 143 
#define  LOCALE_SMONTHNAME6 142 
#define  LOCALE_SMONTHNAME7 141 
#define  LOCALE_SMONTHNAME8 140 
#define  LOCALE_SMONTHNAME9 139 
#define  LOCALE_SMONTHOUSANDSEP 138 
#define  LOCALE_SNATIVECURRNAME 137 
#define  LOCALE_SNATIVEDIGITS 136 
#define  LOCALE_SNEGATIVESIGN 135 
#define  LOCALE_SPOSITIVESIGN 134 
#define  LOCALE_SSHORTDATE 133 
#define  LOCALE_SSORTNAME 132 
#define  LOCALE_STHOUSAND 131 
#define  LOCALE_STIME 130 
#define  LOCALE_STIMEFORMAT 129 
#define  LOCALE_SYEARMONTH 128 
 scalar_t__ LOCALE_SYSTEM_DEFAULT ; 
 scalar_t__ LOCALE_USER_DEFAULT ; 
 scalar_t__ lcid_LC_COLLATE ; 
 scalar_t__ lcid_LC_CTYPE ; 
 scalar_t__ lcid_LC_MEASUREMENT ; 
 scalar_t__ lcid_LC_MONETARY ; 
 scalar_t__ lcid_LC_NUMERIC ; 
 scalar_t__ lcid_LC_PAPER ; 
 scalar_t__ lcid_LC_TELEPHONE ; 
 scalar_t__ lcid_LC_TIME ; 

__attribute__((used)) static LCID convert_default_lcid( LCID lcid, LCTYPE lctype )
{
    if (lcid == LOCALE_SYSTEM_DEFAULT ||
        lcid == LOCALE_USER_DEFAULT ||
        lcid == LOCALE_NEUTRAL)
    {
        LCID default_id = 0;

        switch(lctype & 0xffff)
        {
        case LOCALE_SSORTNAME:
            default_id = lcid_LC_COLLATE;
            break;

        case LOCALE_FONTSIGNATURE:
        case LOCALE_IDEFAULTANSICODEPAGE:
        case LOCALE_IDEFAULTCODEPAGE:
        case LOCALE_IDEFAULTEBCDICCODEPAGE:
        case LOCALE_IDEFAULTMACCODEPAGE:
        case LOCALE_IDEFAULTUNIXCODEPAGE:
            default_id = lcid_LC_CTYPE;
            break;

        case LOCALE_ICURRDIGITS:
        case LOCALE_ICURRENCY:
        case LOCALE_IINTLCURRDIGITS:
        case LOCALE_INEGCURR:
        case LOCALE_INEGSEPBYSPACE:
        case LOCALE_INEGSIGNPOSN:
        case LOCALE_INEGSYMPRECEDES:
        case LOCALE_IPOSSEPBYSPACE:
        case LOCALE_IPOSSIGNPOSN:
        case LOCALE_IPOSSYMPRECEDES:
        case LOCALE_SCURRENCY:
        case LOCALE_SINTLSYMBOL:
        case LOCALE_SMONDECIMALSEP:
        case LOCALE_SMONGROUPING:
        case LOCALE_SMONTHOUSANDSEP:
        case LOCALE_SNATIVECURRNAME:
            default_id = lcid_LC_MONETARY;
            break;

        case LOCALE_IDIGITS:
        case LOCALE_IDIGITSUBSTITUTION:
        case LOCALE_ILZERO:
        case LOCALE_INEGNUMBER:
        case LOCALE_SDECIMAL:
        case LOCALE_SGROUPING:
        //case LOCALE_SNAN:
        case LOCALE_SNATIVEDIGITS:
        case LOCALE_SNEGATIVESIGN:
        //case LOCALE_SNEGINFINITY:
        //case LOCALE_SPOSINFINITY:
        case LOCALE_SPOSITIVESIGN:
        case LOCALE_STHOUSAND:
            default_id = lcid_LC_NUMERIC;
            break;

        case LOCALE_ICALENDARTYPE:
        case LOCALE_ICENTURY:
        case LOCALE_IDATE:
        case LOCALE_IDAYLZERO:
        case LOCALE_IFIRSTDAYOFWEEK:
        case LOCALE_IFIRSTWEEKOFYEAR:
        case LOCALE_ILDATE:
        case LOCALE_IMONLZERO:
        case LOCALE_IOPTIONALCALENDAR:
        case LOCALE_ITIME:
        case LOCALE_ITIMEMARKPOSN:
        case LOCALE_ITLZERO:
        case LOCALE_S1159:
        case LOCALE_S2359:
        case LOCALE_SABBREVDAYNAME1:
        case LOCALE_SABBREVDAYNAME2:
        case LOCALE_SABBREVDAYNAME3:
        case LOCALE_SABBREVDAYNAME4:
        case LOCALE_SABBREVDAYNAME5:
        case LOCALE_SABBREVDAYNAME6:
        case LOCALE_SABBREVDAYNAME7:
        case LOCALE_SABBREVMONTHNAME1:
        case LOCALE_SABBREVMONTHNAME2:
        case LOCALE_SABBREVMONTHNAME3:
        case LOCALE_SABBREVMONTHNAME4:
        case LOCALE_SABBREVMONTHNAME5:
        case LOCALE_SABBREVMONTHNAME6:
        case LOCALE_SABBREVMONTHNAME7:
        case LOCALE_SABBREVMONTHNAME8:
        case LOCALE_SABBREVMONTHNAME9:
        case LOCALE_SABBREVMONTHNAME10:
        case LOCALE_SABBREVMONTHNAME11:
        case LOCALE_SABBREVMONTHNAME12:
        case LOCALE_SABBREVMONTHNAME13:
        case LOCALE_SDATE:
        case LOCALE_SDAYNAME1:
        case LOCALE_SDAYNAME2:
        case LOCALE_SDAYNAME3:
        case LOCALE_SDAYNAME4:
        case LOCALE_SDAYNAME5:
        case LOCALE_SDAYNAME6:
        case LOCALE_SDAYNAME7:
        //case LOCALE_SDURATION:
        case LOCALE_SLONGDATE:
        case LOCALE_SMONTHNAME1:
        case LOCALE_SMONTHNAME2:
        case LOCALE_SMONTHNAME3:
        case LOCALE_SMONTHNAME4:
        case LOCALE_SMONTHNAME5:
        case LOCALE_SMONTHNAME6:
        case LOCALE_SMONTHNAME7:
        case LOCALE_SMONTHNAME8:
        case LOCALE_SMONTHNAME9:
        case LOCALE_SMONTHNAME10:
        case LOCALE_SMONTHNAME11:
        case LOCALE_SMONTHNAME12:
        case LOCALE_SMONTHNAME13:
        case LOCALE_SSHORTDATE:
        //case LOCALE_SSHORTESTDAYNAME1:
        //case LOCALE_SSHORTESTDAYNAME2:
        //case LOCALE_SSHORTESTDAYNAME3:
        //case LOCALE_SSHORTESTDAYNAME4:
        //case LOCALE_SSHORTESTDAYNAME5:
        //case LOCALE_SSHORTESTDAYNAME6:
        //case LOCALE_SSHORTESTDAYNAME7:
        case LOCALE_STIME:
        case LOCALE_STIMEFORMAT:
        case LOCALE_SYEARMONTH:
            default_id = lcid_LC_TIME;
            break;

        case LOCALE_IPAPERSIZE:
            default_id = lcid_LC_PAPER;
            break;

        case LOCALE_IMEASURE:
            default_id = lcid_LC_MEASUREMENT;
            break;

        case LOCALE_ICOUNTRY:
            default_id = lcid_LC_TELEPHONE;
            break;
        }
        if (default_id) lcid = default_id;
    }
    return ConvertDefaultLocale( lcid );
}