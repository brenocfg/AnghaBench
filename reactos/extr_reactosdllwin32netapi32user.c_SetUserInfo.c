#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_54__   TYPE_9__ ;
typedef  struct TYPE_53__   TYPE_8__ ;
typedef  struct TYPE_52__   TYPE_7__ ;
typedef  struct TYPE_51__   TYPE_6__ ;
typedef  struct TYPE_50__   TYPE_5__ ;
typedef  struct TYPE_49__   TYPE_4__ ;
typedef  struct TYPE_48__   TYPE_3__ ;
typedef  struct TYPE_47__   TYPE_2__ ;
typedef  struct TYPE_46__   TYPE_28__ ;
typedef  struct TYPE_45__   TYPE_25__ ;
typedef  struct TYPE_44__   TYPE_24__ ;
typedef  struct TYPE_43__   TYPE_23__ ;
typedef  struct TYPE_42__   TYPE_22__ ;
typedef  struct TYPE_41__   TYPE_21__ ;
typedef  struct TYPE_40__   TYPE_20__ ;
typedef  struct TYPE_39__   TYPE_1__ ;
typedef  struct TYPE_38__   TYPE_19__ ;
typedef  struct TYPE_37__   TYPE_18__ ;
typedef  struct TYPE_36__   TYPE_17__ ;
typedef  struct TYPE_35__   TYPE_16__ ;
typedef  struct TYPE_34__   TYPE_15__ ;
typedef  struct TYPE_33__   TYPE_14__ ;
typedef  struct TYPE_32__   TYPE_13__ ;
typedef  struct TYPE_31__   TYPE_12__ ;
typedef  struct TYPE_30__   TYPE_11__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
struct TYPE_39__ {int /*<<< orphan*/  LogonHours; int /*<<< orphan*/  UnitsPerWeek; } ;
struct TYPE_46__ {void* QuadPart; } ;
struct TYPE_47__ {int PasswordExpired; int /*<<< orphan*/  WhichFields; int /*<<< orphan*/  HomeDirectoryDrive; int /*<<< orphan*/  ProfilePath; int /*<<< orphan*/  PrimaryGroupId; int /*<<< orphan*/  CodePage; int /*<<< orphan*/  CountryCode; TYPE_1__ LogonHours; TYPE_28__ AccountExpires; int /*<<< orphan*/  WorkStations; int /*<<< orphan*/  Parameters; int /*<<< orphan*/  UserComment; int /*<<< orphan*/  FullName; int /*<<< orphan*/  ScriptPath; void* UserAccountControl; int /*<<< orphan*/  AdminComment; int /*<<< orphan*/  HomeDirectory; void* NtPasswordPresent; int /*<<< orphan*/  NtPassword; int /*<<< orphan*/  UserName; } ;
typedef  TYPE_2__ USER_ALL_INFORMATION ;
struct TYPE_54__ {int /*<<< orphan*/  usri1051_primary_group_id; } ;
struct TYPE_53__ {int /*<<< orphan*/ * usri1052_profile; } ;
struct TYPE_52__ {int /*<<< orphan*/ * usri1053_home_dir_drive; } ;
struct TYPE_51__ {int /*<<< orphan*/  usri2_code_page; int /*<<< orphan*/  usri2_country_code; int /*<<< orphan*/  usri2_logon_hours; int /*<<< orphan*/  usri2_units_per_week; int /*<<< orphan*/  usri2_max_storage; int /*<<< orphan*/  usri2_acct_expires; int /*<<< orphan*/ * usri2_workstations; int /*<<< orphan*/ * usri2_parms; int /*<<< orphan*/ * usri2_usr_comment; int /*<<< orphan*/ * usri2_full_name; int /*<<< orphan*/ * usri2_script_path; int /*<<< orphan*/  usri2_flags; int /*<<< orphan*/ * usri2_comment; int /*<<< orphan*/ * usri2_home_dir; int /*<<< orphan*/ * usri2_password; } ;
struct TYPE_50__ {int /*<<< orphan*/  usri22_code_page; int /*<<< orphan*/  usri22_country_code; int /*<<< orphan*/  usri22_logon_hours; int /*<<< orphan*/  usri22_units_per_week; int /*<<< orphan*/  usri22_max_storage; int /*<<< orphan*/  usri22_acct_expires; int /*<<< orphan*/ * usri22_workstations; int /*<<< orphan*/ * usri22_parms; int /*<<< orphan*/ * usri22_usr_comment; int /*<<< orphan*/ * usri22_full_name; int /*<<< orphan*/ * usri22_script_path; int /*<<< orphan*/  usri22_flags; int /*<<< orphan*/ * usri22_comment; int /*<<< orphan*/ * usri22_home_dir; } ;
struct TYPE_49__ {int /*<<< orphan*/  usri3_password_expired; int /*<<< orphan*/ * usri3_home_dir_drive; int /*<<< orphan*/ * usri3_profile; int /*<<< orphan*/  usri3_primary_group_id; int /*<<< orphan*/  usri3_code_page; int /*<<< orphan*/  usri3_country_code; int /*<<< orphan*/  usri3_logon_hours; int /*<<< orphan*/  usri3_units_per_week; int /*<<< orphan*/  usri3_max_storage; int /*<<< orphan*/  usri3_acct_expires; int /*<<< orphan*/ * usri3_workstations; int /*<<< orphan*/ * usri3_parms; int /*<<< orphan*/ * usri3_usr_comment; int /*<<< orphan*/ * usri3_full_name; int /*<<< orphan*/ * usri3_script_path; int /*<<< orphan*/  usri3_flags; int /*<<< orphan*/ * usri3_comment; int /*<<< orphan*/ * usri3_home_dir; int /*<<< orphan*/ * usri3_password; } ;
struct TYPE_48__ {int /*<<< orphan*/  usri4_password_expired; int /*<<< orphan*/ * usri4_home_dir_drive; int /*<<< orphan*/ * usri4_profile; int /*<<< orphan*/  usri4_primary_group_id; int /*<<< orphan*/  usri4_code_page; int /*<<< orphan*/  usri4_country_code; int /*<<< orphan*/  usri4_logon_hours; int /*<<< orphan*/  usri4_units_per_week; int /*<<< orphan*/  usri4_max_storage; int /*<<< orphan*/  usri4_acct_expires; int /*<<< orphan*/ * usri4_workstations; int /*<<< orphan*/ * usri4_parms; int /*<<< orphan*/ * usri4_usr_comment; int /*<<< orphan*/ * usri4_full_name; int /*<<< orphan*/ * usri4_script_path; int /*<<< orphan*/  usri4_flags; int /*<<< orphan*/ * usri4_comment; int /*<<< orphan*/ * usri4_home_dir; int /*<<< orphan*/ * usri4_password; } ;
struct TYPE_45__ {int /*<<< orphan*/ * usri0_name; } ;
struct TYPE_44__ {int /*<<< orphan*/ * usri1_script_path; int /*<<< orphan*/  usri1_flags; int /*<<< orphan*/ * usri1_comment; int /*<<< orphan*/ * usri1_home_dir; int /*<<< orphan*/ * usri1_password; } ;
struct TYPE_43__ {int /*<<< orphan*/ * usri1003_password; } ;
struct TYPE_42__ {int /*<<< orphan*/ * usri1006_home_dir; } ;
struct TYPE_41__ {int /*<<< orphan*/ * usri1007_comment; } ;
struct TYPE_40__ {int /*<<< orphan*/  usri1008_flags; } ;
struct TYPE_38__ {int /*<<< orphan*/ * usri1009_script_path; } ;
struct TYPE_37__ {int /*<<< orphan*/ * usri1011_full_name; } ;
struct TYPE_36__ {int /*<<< orphan*/ * usri1012_usr_comment; } ;
struct TYPE_35__ {int /*<<< orphan*/ * usri1013_parms; } ;
struct TYPE_34__ {int /*<<< orphan*/ * usri1014_workstations; } ;
struct TYPE_33__ {int /*<<< orphan*/  usri1017_acct_expires; } ;
struct TYPE_32__ {int /*<<< orphan*/  usri1018_max_storage; } ;
struct TYPE_31__ {int /*<<< orphan*/  usri1020_logon_hours; int /*<<< orphan*/  usri1020_units_per_week; } ;
struct TYPE_30__ {int /*<<< orphan*/  usri1024_country_code; } ;
struct TYPE_29__ {int /*<<< orphan*/  usri1025_code_page; } ;
typedef  int /*<<< orphan*/  SAM_HANDLE ;
typedef  TYPE_3__* PUSER_INFO_4 ;
typedef  TYPE_4__* PUSER_INFO_3 ;
typedef  TYPE_5__* PUSER_INFO_22 ;
typedef  TYPE_6__* PUSER_INFO_2 ;
typedef  TYPE_7__* PUSER_INFO_1053 ;
typedef  TYPE_8__* PUSER_INFO_1052 ;
typedef  TYPE_9__* PUSER_INFO_1051 ;
typedef  TYPE_10__* PUSER_INFO_1025 ;
typedef  TYPE_11__* PUSER_INFO_1024 ;
typedef  TYPE_12__* PUSER_INFO_1020 ;
typedef  TYPE_13__* PUSER_INFO_1018 ;
typedef  TYPE_14__* PUSER_INFO_1017 ;
typedef  TYPE_15__* PUSER_INFO_1014 ;
typedef  TYPE_16__* PUSER_INFO_1013 ;
typedef  TYPE_17__* PUSER_INFO_1012 ;
typedef  TYPE_18__* PUSER_INFO_1011 ;
typedef  TYPE_19__* PUSER_INFO_1009 ;
typedef  TYPE_20__* PUSER_INFO_1008 ;
typedef  TYPE_21__* PUSER_INFO_1007 ;
typedef  TYPE_22__* PUSER_INFO_1006 ;
typedef  TYPE_23__* PUSER_INFO_1003 ;
typedef  TYPE_24__* PUSER_INFO_1 ;
typedef  TYPE_25__* PUSER_INFO_0 ;
typedef  int /*<<< orphan*/ * PDWORD ;
typedef  int /*<<< orphan*/ * PACL ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ NET_API_STATUS ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ChangeUserDacl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 void* GetAccountControl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ GetUserDacl (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* MAXLONGLONG ; 
 scalar_t__ NERR_Success ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ NetpNtStatusToApiStatus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlSecondsSince1970ToTime (int /*<<< orphan*/ ,TYPE_28__*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SamSetInformationUser (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  TIMEQ_FOREVER ; 
 void* TRUE ; 
 int /*<<< orphan*/  USER_ALL_ACCOUNTEXPIRES ; 
 int /*<<< orphan*/  USER_ALL_ADMINCOMMENT ; 
 int /*<<< orphan*/  USER_ALL_CODEPAGE ; 
 int /*<<< orphan*/  USER_ALL_COUNTRYCODE ; 
 int /*<<< orphan*/  USER_ALL_FULLNAME ; 
 int /*<<< orphan*/  USER_ALL_HOMEDIRECTORY ; 
 int /*<<< orphan*/  USER_ALL_HOMEDIRECTORYDRIVE ; 
 int /*<<< orphan*/  USER_ALL_LOGONHOURS ; 
 int /*<<< orphan*/  USER_ALL_NTPASSWORDPRESENT ; 
 int /*<<< orphan*/  USER_ALL_PARAMETERS ; 
 int /*<<< orphan*/  USER_ALL_PASSWORDEXPIRED ; 
 int /*<<< orphan*/  USER_ALL_PRIMARYGROUPID ; 
 int /*<<< orphan*/  USER_ALL_PROFILEPATH ; 
 int /*<<< orphan*/  USER_ALL_SCRIPTPATH ; 
 int /*<<< orphan*/  USER_ALL_USERACCOUNTCONTROL ; 
 int /*<<< orphan*/  USER_ALL_USERCOMMENT ; 
 int /*<<< orphan*/  USER_ALL_USERNAME ; 
 int /*<<< orphan*/  USER_ALL_WORKSTATIONS ; 
 int /*<<< orphan*/  USER_MAXSTORAGE_UNLIMITED ; 
 int /*<<< orphan*/  USER_MAX_STORAGE_PARMNUM ; 
 int /*<<< orphan*/  USER_UNITS_PER_WEEK_PARMNUM ; 
 int /*<<< orphan*/  USHRT_MAX ; 
 int /*<<< orphan*/  UserAllInformation ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 

__attribute__((used)) static
NET_API_STATUS
SetUserInfo(SAM_HANDLE UserHandle,
            LPBYTE UserInfo,
            DWORD Level,
            PDWORD parm_err)
{
    USER_ALL_INFORMATION UserAllInfo;
    PUSER_INFO_0 UserInfo0;
    PUSER_INFO_1 UserInfo1;
    PUSER_INFO_2 UserInfo2;
    PUSER_INFO_3 UserInfo3;
    PUSER_INFO_4 UserInfo4;
    PUSER_INFO_22 UserInfo22;
    PUSER_INFO_1003 UserInfo1003;
    PUSER_INFO_1006 UserInfo1006;
    PUSER_INFO_1007 UserInfo1007;
    PUSER_INFO_1008 UserInfo1008;
    PUSER_INFO_1009 UserInfo1009;
    PUSER_INFO_1011 UserInfo1011;
    PUSER_INFO_1012 UserInfo1012;
    PUSER_INFO_1013 UserInfo1013;
    PUSER_INFO_1014 UserInfo1014;
    PUSER_INFO_1017 UserInfo1017;
    PUSER_INFO_1018 UserInfo1018;
    PUSER_INFO_1020 UserInfo1020;
    PUSER_INFO_1024 UserInfo1024;
    PUSER_INFO_1025 UserInfo1025;
    PUSER_INFO_1051 UserInfo1051;
    PUSER_INFO_1052 UserInfo1052;
    PUSER_INFO_1053 UserInfo1053;
    PACL Dacl = NULL;
    NET_API_STATUS ApiStatus = NERR_Success;
    NTSTATUS Status = STATUS_SUCCESS;

    ZeroMemory(&UserAllInfo, sizeof(USER_ALL_INFORMATION));

    if ((Level == 1) || (Level == 2) || (Level == 3) ||
        (Level == 4) || (Level == 22) || (Level == 1008))
    {
        ApiStatus = GetUserDacl(UserHandle, &Dacl);
        if (ApiStatus != NERR_Success)
            goto done;
    }

    switch (Level)
    {
        case 0:
            UserInfo0 = (PUSER_INFO_0)UserInfo;

            RtlInitUnicodeString(&UserAllInfo.UserName,
                                 UserInfo0->usri0_name);

            UserAllInfo.WhichFields |= USER_ALL_USERNAME;
            break;

        case 1:
            UserInfo1 = (PUSER_INFO_1)UserInfo;

            // usri1_name ignored

            if (UserInfo1->usri1_password != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.NtPassword,
                                     UserInfo1->usri1_password);
                UserAllInfo.NtPasswordPresent = TRUE;
                UserAllInfo.WhichFields |= USER_ALL_NTPASSWORDPRESENT;
            }

            // usri1_password_age ignored

//          UserInfo1->usri1_priv

            if (UserInfo1->usri1_home_dir != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.HomeDirectory,
                                     UserInfo1->usri1_home_dir);
                UserAllInfo.WhichFields |= USER_ALL_HOMEDIRECTORY;
            }

            if (UserInfo1->usri1_comment != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.AdminComment,
                                     UserInfo1->usri1_comment);
                UserAllInfo.WhichFields |= USER_ALL_ADMINCOMMENT;
            }

            ChangeUserDacl(Dacl, UserInfo1->usri1_flags);
            UserAllInfo.UserAccountControl = GetAccountControl(UserInfo1->usri1_flags);
            UserAllInfo.WhichFields |= USER_ALL_USERACCOUNTCONTROL;

            if (UserInfo1->usri1_script_path != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.ScriptPath,
                                     UserInfo1->usri1_script_path);
                UserAllInfo.WhichFields |= USER_ALL_SCRIPTPATH;
            }
            break;

        case 2:
            UserInfo2 = (PUSER_INFO_2)UserInfo;

            // usri2_name ignored

            if (UserInfo2->usri2_password != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.NtPassword,
                                     UserInfo2->usri2_password);
                UserAllInfo.NtPasswordPresent = TRUE;
                UserAllInfo.WhichFields |= USER_ALL_NTPASSWORDPRESENT;
            }

            // usri2_password_age ignored

//          UserInfo2->usri2_priv;

            if (UserInfo2->usri2_home_dir != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.HomeDirectory,
                                     UserInfo2->usri2_home_dir);
                UserAllInfo.WhichFields |= USER_ALL_HOMEDIRECTORY;
            }

            if (UserInfo2->usri2_comment != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.AdminComment,
                                     UserInfo2->usri2_comment);
                UserAllInfo.WhichFields |= USER_ALL_ADMINCOMMENT;
            }

            ChangeUserDacl(Dacl, UserInfo2->usri2_flags);
            UserAllInfo.UserAccountControl = GetAccountControl(UserInfo2->usri2_flags);
            UserAllInfo.WhichFields |= USER_ALL_USERACCOUNTCONTROL;

            if (UserInfo2->usri2_script_path != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.ScriptPath,
                                     UserInfo2->usri2_script_path);
                UserAllInfo.WhichFields |= USER_ALL_SCRIPTPATH;
            }

//          UserInfo2->usri2_auth_flags;

            if (UserInfo2->usri2_full_name != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.FullName,
                                     UserInfo2->usri2_full_name);
                UserAllInfo.WhichFields |= USER_ALL_FULLNAME;
            }

            if (UserInfo2->usri2_usr_comment != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.UserComment,
                                     UserInfo2->usri2_usr_comment);
                UserAllInfo.WhichFields |= USER_ALL_USERCOMMENT;
            }

            if (UserInfo2->usri2_parms != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.Parameters,
                                     UserInfo2->usri2_parms);
                UserAllInfo.WhichFields |= USER_ALL_PARAMETERS;
            }

            if (UserInfo2->usri2_workstations != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.WorkStations,
                                     UserInfo2->usri2_workstations);
                UserAllInfo.WhichFields |= USER_ALL_WORKSTATIONS;
            }

            // usri2_last_logon ignored
            // usri2_last_logoff ignored

            if (UserInfo2->usri2_acct_expires == TIMEQ_FOREVER)
            {
                UserAllInfo.AccountExpires.QuadPart = MAXLONGLONG;
            }
            else
            {
                RtlSecondsSince1970ToTime(UserInfo2->usri2_acct_expires,
                                          &UserAllInfo.AccountExpires);
            }
            UserAllInfo.WhichFields |= USER_ALL_ACCOUNTEXPIRES;

            if (UserInfo2->usri2_max_storage != USER_MAXSTORAGE_UNLIMITED)
            {
                if (parm_err != NULL)
                    *parm_err = USER_MAX_STORAGE_PARMNUM;
                ApiStatus = ERROR_INVALID_PARAMETER;
                break;
            }

            if (UserInfo2->usri2_units_per_week > USHRT_MAX)
            {
                if (parm_err != NULL)
                    *parm_err = USER_UNITS_PER_WEEK_PARMNUM;
                ApiStatus = ERROR_INVALID_PARAMETER;
                break;
            }

            UserAllInfo.LogonHours.UnitsPerWeek = UserInfo2->usri2_units_per_week;
            UserAllInfo.LogonHours.LogonHours = UserInfo2->usri2_logon_hours;
            UserAllInfo.WhichFields |= USER_ALL_LOGONHOURS;

            // usri2_bad_pw_count ignored
            // usri2_num_logons ignored
            // usri2_logon_server ignored

            UserAllInfo.CountryCode = UserInfo2->usri2_country_code;
            UserAllInfo.WhichFields |= USER_ALL_COUNTRYCODE;

            UserAllInfo.CodePage = UserInfo2->usri2_code_page;
            UserAllInfo.WhichFields |= USER_ALL_CODEPAGE;
            break;

        case 3:
            UserInfo3 = (PUSER_INFO_3)UserInfo;

            // usri3_name ignored

            if (UserInfo3->usri3_password != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.NtPassword,
                                     UserInfo3->usri3_password);
                UserAllInfo.NtPasswordPresent = TRUE;
                UserAllInfo.WhichFields |= USER_ALL_NTPASSWORDPRESENT;
            }

            // usri3_password_age ignored

//          UserInfo3->usri3_priv;

            if (UserInfo3->usri3_home_dir != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.HomeDirectory,
                                     UserInfo3->usri3_home_dir);
                UserAllInfo.WhichFields |= USER_ALL_HOMEDIRECTORY;
            }

            if (UserInfo3->usri3_comment != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.AdminComment,
                                     UserInfo3->usri3_comment);
                UserAllInfo.WhichFields |= USER_ALL_ADMINCOMMENT;
            }

            ChangeUserDacl(Dacl, UserInfo3->usri3_flags);
            UserAllInfo.UserAccountControl = GetAccountControl(UserInfo3->usri3_flags);
            UserAllInfo.WhichFields |= USER_ALL_USERACCOUNTCONTROL;

            if (UserInfo3->usri3_script_path != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.ScriptPath,
                                     UserInfo3->usri3_script_path);
                UserAllInfo.WhichFields |= USER_ALL_SCRIPTPATH;
            }

//          UserInfo3->usri3_auth_flags;

            if (UserInfo3->usri3_full_name != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.FullName,
                                     UserInfo3->usri3_full_name);
                UserAllInfo.WhichFields |= USER_ALL_FULLNAME;
            }

            if (UserInfo3->usri3_usr_comment != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.UserComment,
                                     UserInfo3->usri3_usr_comment);
                UserAllInfo.WhichFields |= USER_ALL_USERCOMMENT;
            }

            if (UserInfo3->usri3_parms != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.Parameters,
                                     UserInfo3->usri3_parms);
                UserAllInfo.WhichFields |= USER_ALL_PARAMETERS;
            }

            if (UserInfo3->usri3_workstations != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.WorkStations,
                                     UserInfo3->usri3_workstations);
                UserAllInfo.WhichFields |= USER_ALL_WORKSTATIONS;
            }

            // usri3_last_logon ignored
            // usri3_last_logoff ignored

            if (UserInfo3->usri3_acct_expires == TIMEQ_FOREVER)
            {
                UserAllInfo.AccountExpires.QuadPart = MAXLONGLONG;
            }
            else
            {
                RtlSecondsSince1970ToTime(UserInfo3->usri3_acct_expires,
                                          &UserAllInfo.AccountExpires);
            }
            UserAllInfo.WhichFields |= USER_ALL_ACCOUNTEXPIRES;

            if (UserInfo3->usri3_max_storage != USER_MAXSTORAGE_UNLIMITED)
            {
                if (parm_err != NULL)
                    *parm_err = USER_MAX_STORAGE_PARMNUM;
                ApiStatus = ERROR_INVALID_PARAMETER;
                break;
            }

            if (UserInfo3->usri3_units_per_week > USHRT_MAX)
            {
                if (parm_err != NULL)
                    *parm_err = USER_UNITS_PER_WEEK_PARMNUM;
                ApiStatus = ERROR_INVALID_PARAMETER;
                break;
            }

            UserAllInfo.LogonHours.UnitsPerWeek = UserInfo3->usri3_units_per_week;
            UserAllInfo.LogonHours.LogonHours = UserInfo3->usri3_logon_hours;
            UserAllInfo.WhichFields |= USER_ALL_LOGONHOURS;

            // usri3_bad_pw_count ignored
            // usri3_num_logons ignored
            // usri3_logon_server ignored

            UserAllInfo.CountryCode = UserInfo3->usri3_country_code;
            UserAllInfo.WhichFields |= USER_ALL_COUNTRYCODE;

            UserAllInfo.CodePage = UserInfo3->usri3_code_page;
            UserAllInfo.WhichFields |= USER_ALL_CODEPAGE;

            // usri3_user_id ignored

            UserAllInfo.PrimaryGroupId = UserInfo3->usri3_primary_group_id;
            UserAllInfo.WhichFields |= USER_ALL_PRIMARYGROUPID;

            if (UserInfo3->usri3_profile != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.ProfilePath,
                                     UserInfo3->usri3_profile);
                UserAllInfo.WhichFields |= USER_ALL_PROFILEPATH;
            }

            if (UserInfo3->usri3_home_dir_drive != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.HomeDirectoryDrive,
                                     UserInfo3->usri3_home_dir_drive);
                UserAllInfo.WhichFields |= USER_ALL_HOMEDIRECTORYDRIVE;
            }

            UserAllInfo.PasswordExpired = (UserInfo3->usri3_password_expired != 0);
            UserAllInfo.WhichFields |= USER_ALL_PASSWORDEXPIRED;
            break;

        case 4:
            UserInfo4 = (PUSER_INFO_4)UserInfo;

            // usri4_name ignored

            if (UserInfo4->usri4_password != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.NtPassword,
                                     UserInfo4->usri4_password);
                UserAllInfo.NtPasswordPresent = TRUE;
                UserAllInfo.WhichFields |= USER_ALL_NTPASSWORDPRESENT;
            }

            // usri4_password_age ignored

//          UserInfo3->usri4_priv;

            if (UserInfo4->usri4_home_dir != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.HomeDirectory,
                                     UserInfo4->usri4_home_dir);
                UserAllInfo.WhichFields |= USER_ALL_HOMEDIRECTORY;
            }

            if (UserInfo4->usri4_comment != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.AdminComment,
                                     UserInfo4->usri4_comment);
                UserAllInfo.WhichFields |= USER_ALL_ADMINCOMMENT;
            }

            ChangeUserDacl(Dacl, UserInfo4->usri4_flags);
            UserAllInfo.UserAccountControl = GetAccountControl(UserInfo4->usri4_flags);
            UserAllInfo.WhichFields |= USER_ALL_USERACCOUNTCONTROL;

            if (UserInfo4->usri4_script_path != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.ScriptPath,
                                     UserInfo4->usri4_script_path);
                UserAllInfo.WhichFields |= USER_ALL_SCRIPTPATH;
            }

//          UserInfo4->usri4_auth_flags;

            if (UserInfo4->usri4_full_name != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.FullName,
                                     UserInfo4->usri4_full_name);
                UserAllInfo.WhichFields |= USER_ALL_FULLNAME;
            }

            if (UserInfo4->usri4_usr_comment != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.UserComment,
                                     UserInfo4->usri4_usr_comment);
                UserAllInfo.WhichFields |= USER_ALL_USERCOMMENT;
            }

            if (UserInfo4->usri4_parms != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.Parameters,
                                     UserInfo4->usri4_parms);
                UserAllInfo.WhichFields |= USER_ALL_PARAMETERS;
            }

            if (UserInfo4->usri4_workstations != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.WorkStations,
                                     UserInfo4->usri4_workstations);
                UserAllInfo.WhichFields |= USER_ALL_WORKSTATIONS;
            }

            // usri4_last_logon ignored
            // usri4_last_logoff ignored

            if (UserInfo4->usri4_acct_expires == TIMEQ_FOREVER)
            {
                UserAllInfo.AccountExpires.QuadPart = MAXLONGLONG;
            }
            else
            {
                RtlSecondsSince1970ToTime(UserInfo4->usri4_acct_expires,
                                          &UserAllInfo.AccountExpires);
            }
            UserAllInfo.WhichFields |= USER_ALL_ACCOUNTEXPIRES;

            if (UserInfo4->usri4_max_storage != USER_MAXSTORAGE_UNLIMITED)
            {
                if (parm_err != NULL)
                    *parm_err = USER_MAX_STORAGE_PARMNUM;
                ApiStatus = ERROR_INVALID_PARAMETER;
                break;
            }

            if (UserInfo4->usri4_units_per_week > USHRT_MAX)
            {
                if (parm_err != NULL)
                    *parm_err = USER_UNITS_PER_WEEK_PARMNUM;
                ApiStatus = ERROR_INVALID_PARAMETER;
                break;
            }

            UserAllInfo.LogonHours.UnitsPerWeek = UserInfo4->usri4_units_per_week;
            UserAllInfo.LogonHours.LogonHours = UserInfo4->usri4_logon_hours;
            UserAllInfo.WhichFields |= USER_ALL_LOGONHOURS;

            // usri4_bad_pw_count ignored
            // usri4_num_logons ignored
            // usri4_logon_server ignored

            UserAllInfo.CountryCode = UserInfo4->usri4_country_code;
            UserAllInfo.WhichFields |= USER_ALL_COUNTRYCODE;

            UserAllInfo.CodePage = UserInfo4->usri4_code_page;
            UserAllInfo.WhichFields |= USER_ALL_CODEPAGE;

            // usri4_user_sid ignored

            UserAllInfo.PrimaryGroupId = UserInfo4->usri4_primary_group_id;
            UserAllInfo.WhichFields |= USER_ALL_PRIMARYGROUPID;

            if (UserInfo4->usri4_profile != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.ProfilePath,
                                     UserInfo4->usri4_profile);
                UserAllInfo.WhichFields |= USER_ALL_PROFILEPATH;
            }

            if (UserInfo4->usri4_home_dir_drive != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.HomeDirectoryDrive,
                                     UserInfo4->usri4_home_dir_drive);
                UserAllInfo.WhichFields |= USER_ALL_HOMEDIRECTORYDRIVE;
            }

            UserAllInfo.PasswordExpired = (UserInfo4->usri4_password_expired != 0);
            UserAllInfo.WhichFields |= USER_ALL_PASSWORDEXPIRED;
            break;

//        case 21:
//            break;

        case 22:
            UserInfo22 = (PUSER_INFO_22)UserInfo;

            // usri22_name ignored

//          UserInfo22->usri22_password[ENCRYPTED_PWLEN];

            // usri22_password_age ignored

//          UserInfo3->usri3_priv;

            if (UserInfo22->usri22_home_dir != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.HomeDirectory,
                                     UserInfo22->usri22_home_dir);
                UserAllInfo.WhichFields |= USER_ALL_HOMEDIRECTORY;
            }

            if (UserInfo22->usri22_comment != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.AdminComment,
                                     UserInfo22->usri22_comment);
                UserAllInfo.WhichFields |= USER_ALL_ADMINCOMMENT;
            }

            ChangeUserDacl(Dacl, UserInfo22->usri22_flags);
            UserAllInfo.UserAccountControl = GetAccountControl(UserInfo22->usri22_flags);
            UserAllInfo.WhichFields |= USER_ALL_USERACCOUNTCONTROL;

            if (UserInfo22->usri22_script_path != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.ScriptPath,
                                     UserInfo22->usri22_script_path);
                UserAllInfo.WhichFields |= USER_ALL_SCRIPTPATH;
            }

//          UserInfo22->usri22_auth_flags;

            if (UserInfo22->usri22_full_name != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.FullName,
                                     UserInfo22->usri22_full_name);
                UserAllInfo.WhichFields |= USER_ALL_FULLNAME;
            }

            if (UserInfo22->usri22_usr_comment != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.UserComment,
                                     UserInfo22->usri22_usr_comment);
                UserAllInfo.WhichFields |= USER_ALL_USERCOMMENT;
            }

            if (UserInfo22->usri22_parms != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.Parameters,
                                     UserInfo22->usri22_parms);
                UserAllInfo.WhichFields |= USER_ALL_PARAMETERS;
            }

            if (UserInfo22->usri22_workstations != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.WorkStations,
                                     UserInfo22->usri22_workstations);
                UserAllInfo.WhichFields |= USER_ALL_WORKSTATIONS;
            }

            // usri22_last_logon ignored
            // usri22_last_logoff ignored

            if (UserInfo22->usri22_acct_expires == TIMEQ_FOREVER)
            {
                UserAllInfo.AccountExpires.QuadPart = MAXLONGLONG;
            }
            else
            {
                RtlSecondsSince1970ToTime(UserInfo22->usri22_acct_expires,
                                          &UserAllInfo.AccountExpires);
            }
            UserAllInfo.WhichFields |= USER_ALL_ACCOUNTEXPIRES;

            if (UserInfo22->usri22_max_storage != USER_MAXSTORAGE_UNLIMITED)
            {
                if (parm_err != NULL)
                    *parm_err = USER_MAX_STORAGE_PARMNUM;
                ApiStatus = ERROR_INVALID_PARAMETER;
                break;
            }

            if (UserInfo22->usri22_units_per_week > USHRT_MAX)
            {
                if (parm_err != NULL)
                    *parm_err = USER_UNITS_PER_WEEK_PARMNUM;
                ApiStatus = ERROR_INVALID_PARAMETER;
                break;
            }

            UserAllInfo.LogonHours.UnitsPerWeek = UserInfo22->usri22_units_per_week;
            UserAllInfo.LogonHours.LogonHours = UserInfo22->usri22_logon_hours;
            UserAllInfo.WhichFields |= USER_ALL_LOGONHOURS;

            // usri22_bad_pw_count ignored
            // usri22_num_logons ignored
            // usri22_logon_server ignored

            UserAllInfo.CountryCode = UserInfo22->usri22_country_code;
            UserAllInfo.WhichFields |= USER_ALL_COUNTRYCODE;

            UserAllInfo.CodePage = UserInfo22->usri22_code_page;
            UserAllInfo.WhichFields |= USER_ALL_CODEPAGE;
            break;

        case 1003:
            UserInfo1003 = (PUSER_INFO_1003)UserInfo;

            if (UserInfo1003->usri1003_password != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.NtPassword,
                                     UserInfo1003->usri1003_password);
                UserAllInfo.NtPasswordPresent = TRUE;
                UserAllInfo.WhichFields |= USER_ALL_NTPASSWORDPRESENT;
            }
            break;

//        case 1005:
//            break;

        case 1006:
            UserInfo1006 = (PUSER_INFO_1006)UserInfo;

            if (UserInfo1006->usri1006_home_dir != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.HomeDirectory,
                                     UserInfo1006->usri1006_home_dir);
                UserAllInfo.WhichFields |= USER_ALL_HOMEDIRECTORY;
            }
            break;

        case 1007:
            UserInfo1007 = (PUSER_INFO_1007)UserInfo;

            if (UserInfo1007->usri1007_comment != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.AdminComment,
                                     UserInfo1007->usri1007_comment);
                UserAllInfo.WhichFields |= USER_ALL_ADMINCOMMENT;
            }
            break;

        case 1008:
            UserInfo1008 = (PUSER_INFO_1008)UserInfo;
            ChangeUserDacl(Dacl, UserInfo1008->usri1008_flags);
            UserAllInfo.UserAccountControl = GetAccountControl(UserInfo1008->usri1008_flags);
            UserAllInfo.WhichFields |= USER_ALL_USERACCOUNTCONTROL;
            break;

        case 1009:
            UserInfo1009 = (PUSER_INFO_1009)UserInfo;

            if (UserInfo1009->usri1009_script_path != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.ScriptPath,
                                     UserInfo1009->usri1009_script_path);
                UserAllInfo.WhichFields |= USER_ALL_SCRIPTPATH;
            }
            break;

//        case 1010:
//            break;

        case 1011:
            UserInfo1011 = (PUSER_INFO_1011)UserInfo;

            if (UserInfo1011->usri1011_full_name != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.FullName,
                                     UserInfo1011->usri1011_full_name);
                UserAllInfo.WhichFields |= USER_ALL_FULLNAME;
            }
            break;

        case 1012:
            UserInfo1012 = (PUSER_INFO_1012)UserInfo;

            if (UserInfo1012->usri1012_usr_comment != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.UserComment,
                                     UserInfo1012->usri1012_usr_comment);
                UserAllInfo.WhichFields |= USER_ALL_USERCOMMENT;
            }
            break;

        case 1013:
            UserInfo1013 = (PUSER_INFO_1013)UserInfo;

            if (UserInfo1013->usri1013_parms != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.Parameters,
                                     UserInfo1013->usri1013_parms);
                UserAllInfo.WhichFields |= USER_ALL_PARAMETERS;
            }
            break;

        case 1014:
            UserInfo1014 = (PUSER_INFO_1014)UserInfo;

            if (UserInfo1014->usri1014_workstations != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.WorkStations,
                                     UserInfo1014->usri1014_workstations);
                UserAllInfo.WhichFields |= USER_ALL_WORKSTATIONS;
            }
            break;

        case 1017:
            UserInfo1017 = (PUSER_INFO_1017)UserInfo;

            if (UserInfo1017->usri1017_acct_expires == TIMEQ_FOREVER)
            {
                UserAllInfo.AccountExpires.QuadPart = MAXLONGLONG;
            }
            else
            {
                RtlSecondsSince1970ToTime(UserInfo1017->usri1017_acct_expires,
                                          &UserAllInfo.AccountExpires);
            }
            UserAllInfo.WhichFields |= USER_ALL_ACCOUNTEXPIRES;
            break;

        case 1018:
            UserInfo1018 = (PUSER_INFO_1018)UserInfo;

            if (UserInfo1018->usri1018_max_storage != USER_MAXSTORAGE_UNLIMITED)
            {
                if (parm_err != NULL)
                    *parm_err = USER_MAX_STORAGE_PARMNUM;
                ApiStatus = ERROR_INVALID_PARAMETER;
            }
            break;

        case 1020:
            UserInfo1020 = (PUSER_INFO_1020)UserInfo;

            if (UserInfo1020->usri1020_units_per_week > USHRT_MAX)
            {
                if (parm_err != NULL)
                    *parm_err = USER_UNITS_PER_WEEK_PARMNUM;
                ApiStatus = ERROR_INVALID_PARAMETER;
                break;
            }

            UserAllInfo.LogonHours.UnitsPerWeek = UserInfo1020->usri1020_units_per_week;
            UserAllInfo.LogonHours.LogonHours = UserInfo1020->usri1020_logon_hours;
            UserAllInfo.WhichFields |= USER_ALL_LOGONHOURS;
            break;

        case 1024:
            UserInfo1024 = (PUSER_INFO_1024)UserInfo;

            UserAllInfo.CountryCode = UserInfo1024->usri1024_country_code;
            UserAllInfo.WhichFields |= USER_ALL_COUNTRYCODE;
            break;

        case 1025:
            UserInfo1025 = (PUSER_INFO_1025)UserInfo;

            UserAllInfo.CodePage = UserInfo1025->usri1025_code_page;
            UserAllInfo.WhichFields |= USER_ALL_CODEPAGE;
            break;

        case 1051:
            UserInfo1051 = (PUSER_INFO_1051)UserInfo;

            UserAllInfo.PrimaryGroupId = UserInfo1051->usri1051_primary_group_id;
            UserAllInfo.WhichFields |= USER_ALL_PRIMARYGROUPID;
            break;

        case 1052:
            UserInfo1052 = (PUSER_INFO_1052)UserInfo;

            if (UserInfo1052->usri1052_profile != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.ProfilePath,
                                     UserInfo1052->usri1052_profile);
                UserAllInfo.WhichFields |= USER_ALL_PROFILEPATH;
            }
            break;

        case 1053:
            UserInfo1053 = (PUSER_INFO_1053)UserInfo;

            if (UserInfo1053->usri1053_home_dir_drive != NULL)
            {
                RtlInitUnicodeString(&UserAllInfo.HomeDirectoryDrive,
                                     UserInfo1053->usri1053_home_dir_drive);
                UserAllInfo.WhichFields |= USER_ALL_HOMEDIRECTORYDRIVE;
            }
            break;
    }

    if (ApiStatus != NERR_Success)
        goto done;

    Status = SamSetInformationUser(UserHandle,
                                   UserAllInformation,
                                   &UserAllInfo);
    if (!NT_SUCCESS(Status))
    {
        ERR("SamSetInformationUser failed (Status %08lx)\n", Status);
        ApiStatus = NetpNtStatusToApiStatus(Status);
        goto done;
    }

done:
    if (Dacl != NULL)
        HeapFree(GetProcessHeap(), 0, Dacl);

    return ApiStatus;
}