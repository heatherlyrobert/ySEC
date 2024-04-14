/*===[[ ONE_LINERS ]]=========================================================*/
/*-------   --12345678  "123456789-123456789-123456789-123456789-123456789-123456789-"  */

#define     P_FOCUS     "SA (systems administration)"
#define     P_NICHE     "sl (security logging)"
#define     P_SUBJECT   "security logging"
#define     P_PURPOSE   "provide consistent, standard security logging services"

#define     P_NAMESAKE  "aeolus-hippotades (keeper of the winds)"
#define     P_HERITAGE  ""
#define     P_IMAGERY   "pios, just, and kind king of the floating sky-island of aiolia"
#define     P_REASON    "guides stormy seas (system) to help keep sailors safe"

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  ""
#define     P_FULLPATH  ""
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"
#define     P_DEPENDS   "ySTR"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2012-08"

#define     P_VERMAJOR  "0.-- preproduction building and testing"
#define     P_VERMINOR  "0.9- advancing and readying for hestia/hearth"
#define     P_VERNUM    "0.9e"
#define     P_VERTXT    "minor updates to support library changes"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*-------   --12345678  "123456789-123456789-123456789-123456789-123456789-123456789-"  */
/*===[[ END ONE_LINERS ]]=====================================================*/





/*===[[ HEADERS ]]========================================*/
#include    <stdio.h>             /* printf, scanf                            */
#include    <stdlib.h>            /* exit, system, ...                        */
#include    <unistd.h>            /* crypt                                    */
#include    <sys/unistd.h>        /* fork, execl, getpid, getuid, gethostname */
#include    <string.h>            /* strcat, strcpy, strlen, ...              */

#include    <sys/utsname.h>       /* uname                                    */
#include    <time.h>              /* gettimeofday                             */
#include    <sys/time.h>          /* gettimeofday                             */

#include    <fcntl.h>             /* open                                     */
#include    <sys/stat.h>          /* fstat, umask                             */
#include    <utmp.h>              /* utmp, btmp, wtmp, and lastlog tracking   */
#include    <pwd.h>               /* getpwuid, getpwnam                       */
#include    <shadow.h>            /* LINIX     password shadow access    */

#include    <errno.h>             /*                                          */
#include    <termios.h>           /* clibc standard terminal control          */


#include    <yLOG.h>              /* heatherly logging                        */
#include    <yURG.h>              /* heatherly debugging framework            */
#include    <ySTR.h>              /* heatherly string handling                */
#include    <yEXEC.h>             /* heatherly process handling               */

extern char        n_utmp      [LEN_FULL];  /* name of file                       */
extern char        n_wtmp      [LEN_FULL];  /* name of file                       */
extern char        n_btmp      [LEN_FULL];  /* name of file                       */
extern char        n_last      [LEN_FULL];  /* name of file                       */
extern char        n_sulog     [LEN_FULL];  /* name of file                       */
extern char        n_getty     [LEN_FULL];  /* name of file                       */
extern char        n_hestia    [LEN_FULL];  /* name of file                       */

typedef struct cLOCAL tLOCAL;
struct cLOCAL {
};
extern tLOCAL mySEC;

extern char        unit_answer [LEN_RECD];
char*       unit_accessor      (char*, int);

/*===[[ CONSTANTS ]]======================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
#define     F_UTMP      "/var/run/utmp"
#define     F_WTMP      "/var/log/wtmp"
#define     F_BTMP      "/var/log/btmp"
#define     F_LASTLOG   "/var/log/lastlog"
#define     F_SULOG     "/var/log/sulog"
#define     F_GETTY     "/var/log/hestia_active"
#define     F_LOGGING   "/var/log/hestia_logging"

#define     PASSWD           "/etc/passwd"
#define     SHADOW           "/etc/shadow"
#define     GROUP            "/etc/group"
#define     GSHADOW          "/etc/gshadow"
#define     STTY             "/etc/securetty"
#define     HESTIA           "/var/log/hestia.logging"


/*===[[ TYPES ]]==========================================*/
typedef     const char         cchar;
typedef     long long          llong;
typedef     const int          cint;

typedef     struct utmp        tUTMP;
typedef     struct lastlog     tLASTLOG;
typedef     struct utsname     tUNAME;

typedef     struct timeval     tTIMEVAL;
typedef     struct tm          tTIME;

typedef     struct passwd      tPASSWD;
typedef     struct spwd        tSHADOW;

typedef     struct stat        tSTAT;
typedef     struct termios     tTERMIOS;



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
int         ysec__utmp_read         (char w, char n, char *x_recd);
char        ysec__utmp_write        (char w, char *a_dev, char a_type, int a_pid, int a_sid, char *a_user);
char        ysec__last_read         (int a_uid, char *a_recd);
char        ysec__last_write        (char *a_dev, char *a_user);

char        ysec__unit_quiet        (void);
char        ysec__unit_loud         (void);
char        ysec__unit_end          (void);
char*       ysec_utmp__unit         (char *a_question, char w, int n);

char        ysec__username          (char *a_user, char a_rotate, char *a_true);
char        ysec__password          (char *a_user, char *a_pass);

int         ysec__find              (char *a_type, int a_rpid, int *a_pos);
char        ysec__request           (long a_now, char *a_dev, int a_rpid, int a_timeout, int a_lockout, char a_hint, char *a_challenge);
char        ysec__active            (int a_rpid, long a_now, char *a_response, char a_phase, char a_judge, char a_status, char a_result, char *a_user);
char        ysec__complete          (int a_rpid, long a_now, char a_good);
char        ysec__system            (char a_type, long a_now);
char        ysec_system             (char a_type);

char*       ysec__challenge_42byte  (int a_seed, char *a_challenge);
char*       ysec__challenge_65byte  (int a_seed, char *a_challenge);
char        ysec__prepare           (char *a_response, char *a_phase, char *a_judgement, char *a_position, char *a_user);
char        ysec__prepare_unit      (char a_test, char *a_response, char a_judge);
char        ysec__knock             (void);
char        ysec__prefix            (void);
char        ysec__user              (void);
char        ysec__infix             (void);
char        ysec__pass              (void);
char        ysec__suffix            (void);
char        ysec__final             (void);
char        ysec__response_42byte   (char *a_response, char *a_phase, char *a_judgement, char *a_position, char *a_user);
char        ysec__response_65byte   (char *a_response, char *a_phase, char *a_judgement, char *a_position, char *a_user);

char*       ysec_coded__unit        (char *a_question);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        ysec__file_rename       (char *a_terse, char *a_name);

