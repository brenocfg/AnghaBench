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
typedef  char* LPSTR ;
typedef  char* LPCSTR ;
typedef  int HRESULT ;

/* Variables and functions */
#define  CLASS_E_NOAGGREGATION 193 
#define  DPERR_ABORTED 192 
#define  DPERR_ACCESSDENIED 191 
#define  DPERR_ACTIVEPLAYERS 190 
#define  DPERR_ALREADYINITIALIZED 189 
#define  DPERR_ALREADYREGISTERED 188 
#define  DPERR_APPNOTSTARTED 187 
#define  DPERR_AUTHENTICATIONFAILED 186 
#define  DPERR_BUFFERTOOLARGE 185 
#define  DPERR_BUFFERTOOSMALL 184 
#define  DPERR_BUSY 183 
#define  DPERR_CANCELFAILED 182 
#define  DPERR_CANCELLED 181 
#define  DPERR_CANNOTCREATESERVER 180 
#define  DPERR_CANTADDPLAYER 179 
#define  DPERR_CANTCREATEGROUP 178 
#define  DPERR_CANTCREATEPLAYER 177 
#define  DPERR_CANTCREATEPROCESS 176 
#define  DPERR_CANTCREATESESSION 175 
#define  DPERR_CANTLOADCAPI 174 
#define  DPERR_CANTLOADSECURITYPACKAGE 173 
#define  DPERR_CANTLOADSSPI 172 
#define  DPERR_CAPSNOTAVAILABLEYET 171 
#define  DPERR_CONNECTING 170 
#define  DPERR_CONNECTIONLOST 169 
#define  DPERR_ENCRYPTIONFAILED 168 
#define  DPERR_ENCRYPTIONNOTSUPPORTED 167 
#define  DPERR_EXCEPTION 166 
#define  DPERR_GENERIC 165 
#define  DPERR_INVALIDFLAGS 164 
#define  DPERR_INVALIDGROUP 163 
#define  DPERR_INVALIDINTERFACE 162 
#define  DPERR_INVALIDOBJECT 161 
#define  DPERR_INVALIDPARAMS 160 
#define  DPERR_INVALIDPASSWORD 159 
#define  DPERR_INVALIDPLAYER 158 
#define  DPERR_INVALIDPRIORITY 157 
#define  DPERR_LOGONDENIED 156 
#define  DPERR_NOCAPS 155 
#define  DPERR_NOCONNECTION 154 
#define  DPERR_NOINTERFACE 153 
#define  DPERR_NOMEMORY 152 
#define  DPERR_NOMESSAGES 151 
#define  DPERR_NONAMESERVERFOUND 150 
#define  DPERR_NONEWPLAYERS 149 
#define  DPERR_NOPLAYERS 148 
#define  DPERR_NOSERVICEPROVIDER 147 
#define  DPERR_NOSESSIONS 146 
#define  DPERR_NOTHANDLED 145 
#define  DPERR_NOTLOBBIED 144 
#define  DPERR_NOTLOGGEDIN 143 
#define  DPERR_NOTREGISTERED 142 
#define  DPERR_PENDING 141 
#define  DPERR_PLAYERLOST 140 
#define  DPERR_SENDTOOBIG 139 
#define  DPERR_SERVICEPROVIDERLOADED 138 
#define  DPERR_SESSIONLOST 137 
#define  DPERR_SIGNFAILED 136 
#define  DPERR_TIMEOUT 135 
#define  DPERR_UNAVAILABLE 134 
#define  DPERR_UNINITIALIZED 133 
#define  DPERR_UNKNOWNAPPLICATION 132 
#define  DPERR_UNKNOWNMESSAGE 131 
#define  DPERR_UNSUPPORTED 130 
#define  DPERR_USERCANCEL 129 
#define  DP_OK 128 
 int HRESULT_CODE (int) ; 
 char* get_temp_buffer () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static LPCSTR dpResult2str(HRESULT hr)
{
    switch (hr)
    {
    case DP_OK:                          return "DP_OK";
    case DPERR_ALREADYINITIALIZED:       return "DPERR_ALREADYINITIALIZED";
    case DPERR_ACCESSDENIED:             return "DPERR_ACCESSDENIED";
    case DPERR_ACTIVEPLAYERS:            return "DPERR_ACTIVEPLAYERS";
    case DPERR_BUFFERTOOSMALL:           return "DPERR_BUFFERTOOSMALL";
    case DPERR_CANTADDPLAYER:            return "DPERR_CANTADDPLAYER";
    case DPERR_CANTCREATEGROUP:          return "DPERR_CANTCREATEGROUP";
    case DPERR_CANTCREATEPLAYER:         return "DPERR_CANTCREATEPLAYER";
    case DPERR_CANTCREATESESSION:        return "DPERR_CANTCREATESESSION";
    case DPERR_CAPSNOTAVAILABLEYET:      return "DPERR_CAPSNOTAVAILABLEYET";
    case DPERR_EXCEPTION:                return "DPERR_EXCEPTION";
    case DPERR_GENERIC:                  return "DPERR_GENERIC";
    case DPERR_INVALIDFLAGS:             return "DPERR_INVALIDFLAGS";
    case DPERR_INVALIDOBJECT:            return "DPERR_INVALIDOBJECT";
    case DPERR_INVALIDPARAMS:            return "DPERR_INVALIDPARAMS";
        /*           symbol with the same value: DPERR_INVALIDPARAM */
    case DPERR_INVALIDPLAYER:            return "DPERR_INVALIDPLAYER";
    case DPERR_INVALIDGROUP:             return "DPERR_INVALIDGROUP";
    case DPERR_NOCAPS:                   return "DPERR_NOCAPS";
    case DPERR_NOCONNECTION:             return "DPERR_NOCONNECTION";
    case DPERR_NOMEMORY:                 return "DPERR_NOMEMORY";
        /*           symbol with the same value: DPERR_OUTOFMEMORY */
    case DPERR_NOMESSAGES:               return "DPERR_NOMESSAGES";
    case DPERR_NONAMESERVERFOUND:        return "DPERR_NONAMESERVERFOUND";
    case DPERR_NOPLAYERS:                return "DPERR_NOPLAYERS";
    case DPERR_NOSESSIONS:               return "DPERR_NOSESSIONS";
    case DPERR_PENDING:                  return "DPERR_PENDING";
    case DPERR_SENDTOOBIG:               return "DPERR_SENDTOOBIG";
    case DPERR_TIMEOUT:                  return "DPERR_TIMEOUT";
    case DPERR_UNAVAILABLE:              return "DPERR_UNAVAILABLE";
    case DPERR_UNSUPPORTED:              return "DPERR_UNSUPPORTED";
    case DPERR_BUSY:                     return "DPERR_BUSY";
    case DPERR_USERCANCEL:               return "DPERR_USERCANCEL";
    case DPERR_NOINTERFACE:              return "DPERR_NOINTERFACE";
    case DPERR_CANNOTCREATESERVER:       return "DPERR_CANNOTCREATESERVER";
    case DPERR_PLAYERLOST:               return "DPERR_PLAYERLOST";
    case DPERR_SESSIONLOST:              return "DPERR_SESSIONLOST";
    case DPERR_UNINITIALIZED:            return "DPERR_UNINITIALIZED";
    case DPERR_NONEWPLAYERS:             return "DPERR_NONEWPLAYERS";
    case DPERR_INVALIDPASSWORD:          return "DPERR_INVALIDPASSWORD";
    case DPERR_CONNECTING:               return "DPERR_CONNECTING";
    case DPERR_CONNECTIONLOST:           return "DPERR_CONNECTIONLOST";
    case DPERR_UNKNOWNMESSAGE:           return "DPERR_UNKNOWNMESSAGE";
    case DPERR_CANCELFAILED:             return "DPERR_CANCELFAILED";
    case DPERR_INVALIDPRIORITY:          return "DPERR_INVALIDPRIORITY";
    case DPERR_NOTHANDLED:               return "DPERR_NOTHANDLED";
    case DPERR_CANCELLED:                return "DPERR_CANCELLED";
    case DPERR_ABORTED:                  return "DPERR_ABORTED";
    case DPERR_BUFFERTOOLARGE:           return "DPERR_BUFFERTOOLARGE";
    case DPERR_CANTCREATEPROCESS:        return "DPERR_CANTCREATEPROCESS";
    case DPERR_APPNOTSTARTED:            return "DPERR_APPNOTSTARTED";
    case DPERR_INVALIDINTERFACE:         return "DPERR_INVALIDINTERFACE";
    case DPERR_NOSERVICEPROVIDER:        return "DPERR_NOSERVICEPROVIDER";
    case DPERR_UNKNOWNAPPLICATION:       return "DPERR_UNKNOWNAPPLICATION";
    case DPERR_NOTLOBBIED:               return "DPERR_NOTLOBBIED";
    case DPERR_SERVICEPROVIDERLOADED:    return "DPERR_SERVICEPROVIDERLOADED";
    case DPERR_ALREADYREGISTERED:        return "DPERR_ALREADYREGISTERED";
    case DPERR_NOTREGISTERED:            return "DPERR_NOTREGISTERED";
    case DPERR_AUTHENTICATIONFAILED:     return "DPERR_AUTHENTICATIONFAILED";
    case DPERR_CANTLOADSSPI:             return "DPERR_CANTLOADSSPI";
    case DPERR_ENCRYPTIONFAILED:         return "DPERR_ENCRYPTIONFAILED";
    case DPERR_SIGNFAILED:               return "DPERR_SIGNFAILED";
    case DPERR_CANTLOADSECURITYPACKAGE:  return "DPERR_CANTLOADSECURITYPACKAGE";
    case DPERR_ENCRYPTIONNOTSUPPORTED:   return "DPERR_ENCRYPTIONNOTSUPPORTED";
    case DPERR_CANTLOADCAPI:             return "DPERR_CANTLOADCAPI";
    case DPERR_NOTLOGGEDIN:              return "DPERR_NOTLOGGEDIN";
    case DPERR_LOGONDENIED:              return "DPERR_LOGONDENIED";
    case CLASS_E_NOAGGREGATION:          return "CLASS_E_NOAGGREGATION";

    default:
    {
        LPSTR buffer = get_temp_buffer();
        sprintf( buffer, "%d", HRESULT_CODE(hr) );
        return buffer;
    }
    }
}