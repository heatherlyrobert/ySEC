/*===[[ START ]]==============================================================*/
#include    "ySEC.h"
#include    "ySEC_priv.h"


tLOCAL      mySEC;
char        rc          = 0;

char        n_utmp      [LEN_FULL]  = F_UTMP;
char        n_wtmp      [LEN_FULL]  = F_WTMP;
char        n_btmp      [LEN_FULL]  = F_BTMP;
char        n_last      [LEN_FULL]  = F_LASTLOG;
char        n_sulog     [LEN_FULL]  = F_SULOG;
char        n_getty     [LEN_FULL]  = F_GETTY;
char        n_hestia    [LEN_FULL]  = F_LOGGING;


char
ysec__file_rename       (char *a_terse, char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_recd      [LEN_RECD]  = "";
   int         l           =    0;
   char       *x_valid     = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_/.";
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YSEC   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YSEC   yLOG_spoint  (a_terse);
   --rce;  if (a_terse == NULL) {
      DEBUG_YSEC   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSEC   yLOG_snote   (a_terse);
   DEBUG_YSEC   yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL) {
      /*---(copy)---------------------------*/
      --rce;  switch (a_terse [0]) {
      case 'u' :
         strlcpy (n_utmp   , F_UTMP   , LEN_FULL);
         DEBUG_YSEC  yLOG_snote   (n_utmp);
         break;
      case 'w' :
         strlcpy (n_wtmp   , F_WTMP   , LEN_FULL);
         DEBUG_YSEC  yLOG_snote   (n_wtmp);
         break;
      case 'b' :
         strlcpy (n_btmp   , F_BTMP   , LEN_FULL);
         DEBUG_YSEC  yLOG_snote   (n_btmp);
         break;
      case 'l' :
         strlcpy (n_last   , F_LASTLOG, LEN_FULL);
         DEBUG_YSEC  yLOG_snote   (n_last);
         break;
      case 's' :
         strlcpy (n_sulog  , F_SULOG  , LEN_FULL);
         DEBUG_YSEC  yLOG_snote   (n_sulog);
         break;
      case 'g' :
         strlcpy (n_getty  , F_GETTY  , LEN_FULL);
         DEBUG_YSEC  yLOG_snote   (n_getty);
         break;
      case 'h' :
         strlcpy (n_hestia , F_LOGGING, LEN_FULL);
         DEBUG_YSEC  yLOG_snote   (n_hestia);
         break;
      }
      DEBUG_YSEC   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   DEBUG_YSEC   yLOG_snote   (a_name);
   strlcpy (x_recd, a_name, LEN_RECD);
   /*---(check length)-------------------*/
   l = strlen (x_recd);
   DEBUG_YSEC  yLOG_sint     (l);
   --rce;  if (l <= 0) {
      DEBUG_YSEC   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check characters)---------------*/
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (x_valid, x_recd [i]) != NULL)  continue;
      DEBUG_YSEC   yLOG_schar   (x_recd [i]);
      DEBUG_YSEC   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(copy)---------------------------*/
   --rce;  switch (a_terse [0]) {
   case 'u' :
      strlcpy (n_utmp   , x_recd, LEN_FULL);
      DEBUG_YSEC  yLOG_snote   (n_utmp);
      break;
   case 'w' :
      strlcpy (n_wtmp   , x_recd, LEN_FULL);
      DEBUG_YSEC  yLOG_snote   (n_wtmp);
      break;
   case 'b' :
      strlcpy (n_btmp   , x_recd, LEN_FULL);
      DEBUG_YSEC  yLOG_snote   (n_btmp);
      break;
   case 'l' :
      strlcpy (n_last   , x_recd, LEN_FULL);
      DEBUG_YSEC  yLOG_snote   (n_last);
      break;
   case 's' :
      strlcpy (n_sulog  , x_recd, LEN_FULL);
      DEBUG_YSEC  yLOG_snote   (n_sulog);
      break;
   case 'g' :
      strlcpy (n_getty  , x_recd, LEN_FULL);
      DEBUG_YSEC  yLOG_snote   (n_getty);
      break;
   case 'h' :
      strlcpy (n_hestia , x_recd, LEN_FULL);
      DEBUG_YSEC  yLOG_snote   (n_hestia);
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YSEC   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                             UTILITIES                        ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITIES_______________o (void) {;}

static char      ySEC_ver [200] = "";

char*      /* ---- : return library versioning information -------------------*/
ySEC_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 18);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 18);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strncpy (t, "[unknown    ]", 18);
#endif
   snprintf (ySEC_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return ySEC_ver;
}



/*====================------------------------------------====================*/
/*===----                       utmpx handling                         ----===*/
/*====================------------------------------------====================*/
static void  o___UTMPX___________o () { return; }

int              /* [------] append a new wtmpx record -----------------------*/
ysec__utmp_read    (char w, char n, char *a_recd)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   FILE       *f           = NULL;
   int         c           =    0;
   int         b           =    0;
   tUTMP       x_utmp;
   char        r           [LEN_FULL]  = "";
   /*---(default values)-----------------*/
   sprintf (a_recd, "n/a");
   /*---(check file existance)-----------*/
   --rce;  switch (w) {
   case 'u' :  strlcpy (r, n_utmp   , LEN_FULL);   break;
   case 'w' :  strlcpy (r, n_wtmp   , LEN_FULL);   break;
   case 'b' :  strlcpy (r, n_btmp   , LEN_FULL);   break;
   default  :  return rce;
   }
   f  = fopen (r, "rb");
   --rce;  if (f == NULL)    return rce;
   /*---(read records)-------------------*/
   while (1) {
      b = fread  (&x_utmp, sizeof (tUTMP), 1, f);
      if (c != 0 && feof (f))  break;
      if (b <= 0)              break;
      if (c == n || n < 0) {
         sprintf (a_recd, "%-22.22s  %-5.5s  %10ld.%03ld  %2d  %5d  %4d  %s",
               x_utmp.ut_host, x_utmp.ut_line,
               x_utmp.ut_tv.tv_sec, x_utmp.ut_tv.tv_usec / 1000,
               x_utmp.ut_type, x_utmp.ut_pid, x_utmp.ut_session,
               x_utmp.ut_name);
      }
      ++c;
      if (feof (f))  break;
   }
   if (c > 999)  c = 999;
   /*---(close)--------------------------*/
   fclose (f);
   /*---(complete)-----------------------*/
   return c;
}

char             /* [------] append a new wtmpx record -----------------------*/
ysec__utmp_write   (char w, char *a_dev, char a_type, int a_pid, int a_sid, char *a_user)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        r           [LEN_FULL]  = "";
   int         f           =    0;
   tUTMP       x_utmp;
   tTIMEVAL    x_time;
   tUNAME      sys_name;
   char        id          [5];
   /*---(check file existance)-----------*/
   --rce;  switch (w) {
   case 'u' :  strlcpy (r, n_utmp   , LEN_FULL);   break;
   case 'w' :  strlcpy (r, n_wtmp   , LEN_FULL);   break;
   case 'b' :  strlcpy (r, n_btmp   , LEN_FULL);   break;
   default  :  return rce;
   }
   rc = access (r, W_OK);
   --rce;  if (rc < 0) {
      f = creat (r, 0644);
      if (f < 0) return rce;
      close (f);
      f = 0;
   }
   /*---(initialize)---------------------*/
   memset  (&x_utmp, 0, sizeof (x_utmp));
   /*---(set time)-----------------------*/
   gettimeofday (&x_time, NULL);
   x_utmp.ut_tv.tv_sec  = x_time.tv_sec;
   x_utmp.ut_tv.tv_usec = x_time.tv_usec;
   /*---(basics)-------------------------*/
   x_utmp.ut_type    = a_type;
   x_utmp.ut_pid     = a_pid;
   x_utmp.ut_session = a_sid;
   strncpy (x_utmp.ut_name, a_user   , sizeof(x_utmp.ut_name));
   strncpy (x_utmp.ut_line, a_dev + 5, sizeof(x_utmp.ut_line));
   uname   (&sys_name);
   sprintf (x_utmp.ut_host, "%s, %s", sys_name.nodename, sys_name.release);
   /*---(deal with id)-------------------*/
   if (strcmp (a_dev, "-") == 0) {
      strcpy (id, "----");
   } else if (strncmp (a_dev, "/dev/tty", 8) == 0) {
      strcpy (id, "c");
      strcat (id, a_dev + 8);
   } else if (strncmp (a_dev, "/dev/pts/", 9) == 0) {
      strcpy (id, "p");
      strcat (id, a_dev + 9);
   }
   strncpy (x_utmp.ut_id  , id       , sizeof(x_utmp.ut_id  ));
   /*---(write)--------------------------*/
   --rce;  switch (w) {
   case 'u' :
      utmpxname  (r);
      setutxent  ();
      pututxline (&x_utmp);
      endutxent  ();
      break;
   case 'w' :
      updwtmp    (r, &x_utmp);
      break;
   case 'b' :
      f  = open   (r,  O_WRONLY | O_APPEND);
      if (f < 0)  return rce;
      write      (f, &x_utmp, sizeof (tUTMP));
      close      (f);
      break;
   }
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     lastlog handling                         ----===*/
/*====================------------------------------------====================*/
static void  o___LASTLOG_________o () { return; }

char             /* [------] update lastlog record ---------------------------*/
ysec__last_read         (int a_uid, char *a_recd)
{
   /*---(locals)-----------+-----------+-*/
   int         f           = 0;
   int         b           =    0;
   tLASTLOG    x_last;   
   char        id          [6];
   /*---(default values)-----------------*/
   sprintf (a_recd, "n/a");
   /*---(check file access)--------------*/
   f  = open   (n_last, O_RDONLY);
   if (f < 0)    return -2;
   /*---(write)--------------------------*/
   lseek (f, ((long) a_uid) * sizeof (tLASTLOG), 0);
   b = read  (f, &x_last, sizeof (tLASTLOG));
   sprintf (a_recd, "%-22.22s  %-5.5s  %10ld  %4d",
         x_last.ll_host, x_last.ll_line, x_last.ll_time, a_uid);
   close (f);
   return 0;
}

char             /* [------] update lastlog record ---------------------------*/
ysec__last_write        (char *a_dev, char *a_user)
{
   /*---(locals)-----------+-----------+-*/
   int         f           = 0;
   tLASTLOG    x_last;
   tUNAME      sys_name;
   tPASSWD    *pw          = NULL;
   char        id          [6];
   /*---(check file existance)-----------*/
   f  = access (n_last, W_OK);
   if (f < 0) {
      f = creat (n_last, 0644);
      if (f < 0) return -1;
      close (f);
   }
   /*---(check file access)--------------*/
   f  = open   (n_last, O_WRONLY);
   if (f < 0)    return -2;
   /*---(initialize)---------------------*/
   memset  (&x_last, 0, sizeof (x_last));
   /*---(get uid)------------------------*/
   pw  = getpwnam (a_user);
   if (pw == NULL) {
      return -3;
   }
   /*---(set time)-----------------------*/
   x_last.ll_time = time (NULL);
   /*---(deal with id)-------------------*/
   strcpy (id, a_dev + 5);
   /*---(basics)-------------------------*/
   strncpy (x_last.ll_line, id      , sizeof(x_last.ll_line));
   uname   (&sys_name);
   sprintf (x_last.ll_host, "%-8.8s", sys_name.nodename);
   /*---(write)--------------------------*/
   lseek (f, ((long) pw->pw_uid) * sizeof (tLASTLOG), 0);
   write (f, &x_last, sizeof (tLASTLOG));
   close (f);
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       simplifiers                            ----===*/
/*====================------------------------------------====================*/
static void  o___SIMPLE__________o () { return; }

char             /* [------] create a system reboot/startup record -----------*/
ySEC_startup       (void)
{
   ysec__utmp_write    ('u', "-", BOOT_TIME    , 0, 0, "--- EOS ----------------");
   ysec__utmp_write    ('w', "-", BOOT_TIME    , 0, 0, "--- EOS ----------------");
   ysec_system         ('b');
   return 0;
}

char             /* [------] create a system shutdown record -----------------*/
ySEC_shutdown      (void)
{
   ysec__utmp_write    ('u', "-", RUN_LVL      , 0, 0, "---------------- NYX ---");
   ysec__utmp_write    ('w', "-", RUN_LVL      , 0, 0, "---------------- NYX ---");
   ysec_system         ('d');
   return 0;
}

char             /* [------] create a getty login record ---------------------*/
ySEC_watch         (char *a_line)
{
   ysec__utmp_write    ('u', a_line, LOGIN_PROCESS, getpid(), getsid(getpid()), "HESTIA");
   ysec__utmp_write    ('w', a_line, LOGIN_PROCESS, getpid(), getsid(getpid()), "HESTIA");
   return 0;
}

char             /* [------] close a getty login record ----------------------*/
ySEC_ignore        (char *a_line, int a_pid)
{
   ysec__utmp_write    ('u', a_line, DEAD_PROCESS , a_pid, 0, "");
   ysec__utmp_write    ('w', a_line, DEAD_PROCESS , a_pid, 0, "");
   return 0;
}

char             /* [------] create a user record ----------------------------*/
ySEC_login         (char *a_line, char *a_user, int a_pid)
{
   rc = 0;
   rc = ysec__utmp_write    ('u', a_line, USER_PROCESS , a_pid, getsid(a_pid), a_user);
   rc = ysec__utmp_write    ('w', a_line, USER_PROCESS , a_pid, getsid(a_pid), a_user);
   rc = ysec__last_write    (a_line, a_user);
   return rc;
}

char             /* [------] record a failed login ---------------------------*/
ySEC_failed        (char *a_line, char *a_user)
{
   rc = 0;
   rc = ysec__utmp_write    ('b', a_line, USER_PROCESS , 0, 0, a_user);
   return rc;
}

char             /* [------] create a user record ----------------------------*/
ySEC_logout        (char *a_line, char *a_user, int a_pid)
{
   ysec__utmp_write    ('u', a_line, DEAD_PROCESS , a_pid, 0, a_user);
   ysec__utmp_write    ('w', a_line, DEAD_PROCESS , a_pid, 0, a_user);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char        unit_answer [LEN_RECD];

char       /*----: set up program urgents/debugging --------------------------*/
ysec__unit_quiet       (void)
{
   yLOGS_begin ("ySEC" , YLOG_SYS, YLOG_QUIET);
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ysec__unit_loud        (void)
{
   yLOGS_begin   ("ySEC" , YLOG_SYS, YLOG_NOISE);
   yURG_name     ("ysec" , YURG_ON);
   DEBUG_YEXEC  yLOG_info     ("ySEC"      , ySEC_version   ());
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ysec__unit_end         (void)
{
   yLOGS_end     ();
   return 0;
}

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
ysec_utmp__unit         (char *a_question, char w, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         c           =    0;
   char        x_recd      [LEN_RECD]  = "";
   char        r           [LEN_FULL]  = "";
   char        s           [LEN_RECD]  = "";
   char        t           [LEN_RECD]  = "";
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "UTMP unit        : question unknown");
   /*---(simple)-------------------------*/
   if      (strcmp (a_question, "file"      )     == 0) {
      switch (w) {
      case 'u' :  strlcpy (r, n_utmp   , LEN_FULL);   break;
      case 'w' :  strlcpy (r, n_wtmp   , LEN_FULL);   break;
      case 'b' :  strlcpy (r, n_btmp   , LEN_FULL);   break;
      case 'l' :  strlcpy (r, n_last   , LEN_FULL);   break;
      case 's' :  strlcpy (r, n_sulog  , LEN_FULL);   break;
      case 'g' :  strlcpy (r, n_getty  , LEN_FULL);   break;
      case 'h' :  strlcpy (r, n_hestia , LEN_FULL);   break;
      }
      snprintf (unit_answer, LEN_RECD, "UTMP %c file      : %2d[%s]", w, strlen (r), r);
   }
   else if (strcmp (a_question, "entry"     )     == 0) {
      switch (w) {
      case 'u' :
         strlcpy (r, n_utmp   , LEN_FULL);
         c = ysec__utmp_read (w, n, x_recd);
         break;
      case 'w' :
         strlcpy (r, n_wtmp   , LEN_FULL);
         c = ysec__utmp_read (w, n, x_recd);
         break;
      case 'b' :
         strlcpy (r, n_btmp   , LEN_FULL);
         c = ysec__utmp_read (w, n, x_recd);
         break;
      case 'l' :
         strlcpy (r, n_last   , LEN_FULL);
         c = ysec__last_read (n, x_recd);
         break;
      case 's' :  strlcpy (r, n_sulog  , LEN_FULL);   break;
      case 'g' :  strlcpy (r, n_getty  , LEN_FULL);   break;
      case 'h' :  strlcpy (r, n_hestia , LEN_FULL);   break;
      }
      if (n > 99)  n = 99;
      snprintf (unit_answer, LEN_RECD, "UTMP %c recd (%2d) : %3d  %s", w, n, c, x_recd);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}






/*===[[ END ]]================================================================*/
