/*===[[ START ]]==============================================================*/
#include    "ySEC.h"
#include    "ySEC_priv.h"

/*
 *   timestamp   %-26.26s
 *   status      %-8.8s       ACTIVE, failure, complete
 *   host        %-10.10s
 *   dev         %-12.12s
 *   rpid        %6d
 *   beg         %-10ld      secs in epoch
 *   timeout     %4d
 *   lockout     %4d
 *   hint        %c
 *   challenge   %-42.42s
 *
 *
 *   phase       %c
 *   judgement   %c
 *   status      %c
 *   result      %4d
 *   user        %-12.12s
 *   end         %-10ld      secs in epoch
 *   dur         %-10ld      secs
 *
 *   20.12.10,20.28.07.6.49.340 § complete   § siguei     § /dev/tty1    §  98765 § 123456789- § 320 § 100 § - § '++'+'12'63'78'44'23'AJx'123'698'454''+''' § 0101010101010101010101010101010101010101 § k § i § Z § -23 § 123456789- § 12345 §
 *
 *
 *
 */

int              /* [------] search in audit log for a particular login ------*/
ysec__find         (char *a_type, int a_rpid, int *a_pos)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   FILE       *f           = NULL;          /* audit file                     */
   int         x_line      = 0;             /* audit file current line        */
   char        x_recd      [LEN_RECD];      /* audit file current record      */
   int         x_len       = 0;             /* audit file current line length */
   char        t           [LEN_LABEL];     /* sprintf temp string            */
   int         x_pos       = 0;
   /*---(default)------------------------*/
   if (a_pos != NULL)  *a_pos = 0;
   /*---(defense)------------------------*/
   --rce;  if (a_type == NULL)  return rce;
   --rce;  if (a_rpid <= 0   )  return rce;
   /*---(gather info)--------------------*/
   f = fopen (n_hestia, "rt");
   --rce;  if (f == NULL) return rce;
   while (1) {
      /*---(read)------------------------*/
      x_pos = ftell (f);
      /*> printf ("run %d is %d\n", line, x_pos);                                       <*/
      fgets (x_recd, LEN_RECD, f);
      if (feof (f))      break;
      /*---(prepare)---------------------*/
      x_len = strlen (x_recd) - 1;
      x_recd [x_len] = '\0';
      ++x_line;
      /*---(defense)---------------------*/
      if (x_len        ==  0 )            continue;
      if (x_recd [0] == '#')            continue;
      /*---(compare status)--------------*/
      if (strncmp (x_recd + 29, a_type, strlen (a_type)) != 0)  continue;
      sprintf (t, " %6d ", a_rpid);
      if (strncmp (x_recd + 67, t, 8) != 0)                     continue;
      /*---(success)---------------------*/
      fclose (f);
      if (a_pos != NULL)  *a_pos = x_pos;
      /*> printf ("find x_pos is %d, %p\n", x_pos, a_pos);                                <*/
      return x_line;
   }
   /*---(failure)------------------------*/
   --rce;
   fclose (f);
   /*---(complete)-----------------------*/
   return rce;
}

char
ysec__request           (long a_now, char *a_dev, int a_rpid, int a_timeout, int a_lockout, char a_hint, char *a_challenge)
{
   char        rce         =  -10;
   tTIME      *x_broke     = NULL;
   char        x_time      [LEN_DESC]  = "";
   char        x_host      [LEN_LABEL] = "";
   FILE       *f           = NULL;
   char        x_recd      [LEN_RECD]  = "";
   /*---(get the date)-------------------*/
   if (a_now < 0)  a_now   = time (NULL);
   x_broke = localtime (&a_now);
   strftime (x_time, LEN_DESC, "%y.%m.%d.%H.%M.%S.%w.%V.%j", x_broke);
   /*---(get the host)-------------------*/
   gethostname (x_host, LEN_LABEL);
   /*---(write the record)---------------*/
   f = fopen (n_hestia, "at");
   --rce;  if (f == NULL)  return rce;
   fprintf (f, "%26.26s  REQUEST   %-10.10s  %-12.12s  %6d  ", x_time, x_host, a_dev, a_rpid);
   fprintf (f, "%10ld  %3d  %3d  %c  %-42.42s  ", a_now, a_timeout, a_lockout, a_hint, a_challenge);
   fprintf (f, "%-13.13s  ", "-------------");
   fprintf (f, "-  -  -  %3d  -             ", 0);
   fprintf (f, "%3d  %10ld  %8d  -       \n", 0, 0, 0);
   /*---(complete)-----------------------*/
   fclose (f);
   return 0;
}

char
ySEC_request            (char *a_dev, int a_rpid, int a_timeout, int a_lockout, char a_hint, char *a_challenge)
{
   return ysec__request (-1, a_dev, a_rpid, a_timeout, a_lockout, a_hint, a_challenge);
}

char
ysec__active            (int a_rpid, long a_now, char *a_response, char a_phase, char a_judge, char a_status, char a_result, char *a_user)
{
   char        rce         =  -10;
   char        rc          =    0;
   int         x_pos       =    0;
   FILE       *f           = NULL;
   char        x_recd      [LEN_RECD]  = "";
   char        x_salt      [LEN_TERSE] = "";
   char        t           [LEN_LABEL] = "";
   long        x_prev      =    0;
   int         x_dur       =    0;
   /*---(check for existing)-------------*/
   rc = ysec__find ("REQUEST", a_rpid, &x_pos);
   yLOG_sint   (rc);
   --rce;  if  (rc <  0) {
      yLOG_sexitr (__FUNCTION__, rce);
      return rce;
   }
   yLOG_sint   (x_pos);
   /*---(gather info)--------------------*/
   f = fopen (n_hestia, "r+");
   yLOG_spoint (f);
   --rce;  if (f == NULL) {
      yLOG_sexitr (__FUNCTION__, rce);
   }
   /*---(get the whole record)-----------*/
   fseek   (f, x_pos      , SEEK_SET);
   fread   (x_recd, 220,  1, f);
   /*---(mark active)--------------------*/
   fseek   (f, x_pos +  29, SEEK_SET);
   if (a_judge == 'Y')   fprintf (f, "ACTIVE  ");
   else                  fprintf (f, "failed  ");
   yLOG_snote  ("marked");
   /*---(get start time)-----------------*/
   fseek   (f, x_pos +  77, SEEK_SET);
   fread   (t, 10,  1, f);
   x_prev = atol (t);
   x_dur  = a_now - x_prev;
   if (x_dur <   0)  x_dur = 0;
   if (x_dur > 999)  x_dur = 999;
   /*---(get the stop)-------------------*/
   if (strlen (a_user) == 0)  ystrlcpy (t, "-"   , LEN_LABEL);
   else                       ystrlcpy (t, a_user, LEN_LABEL);
   sprintf (x_salt, "%c%c", x_recd [73], x_recd [128]);
   fseek   (f, x_pos + 151, SEEK_SET);
   fprintf (f, "%-13.13s  %c  %c  %c  %3d  %-12.12s  %3d",
         crypt (a_response, x_salt), a_phase, a_judge,
         a_status, a_result, t, x_dur);
   /*---(if failure)---------------------*/
   if (a_judge != 'Y') {
      fseek   (f, x_pos + 206, SEEK_SET);
      fprintf (f, "%-10.10ld  %8ld", a_now, x_dur);
   }
   /*---(complete)-----------------------*/
   fflush (f);
   fclose (f);
   yLOG_sexit  (__FUNCTION__);
   return 0;
}

char
ySEC_active             (int a_rpid, char *a_response, char a_phase, char a_judge, char a_status, char a_result, char *a_user)
{
   return ysec__active (a_rpid, -1, a_response, a_phase, a_judge, a_status, a_result, a_user);
}

char
ysec__complete          (int a_rpid, long a_now, char a_good)
{
   char        rce         =  -10;
   char        rc          =    0;
   int         x_pos       =    0;
   FILE       *f           = NULL;
   char        t           [LEN_LABEL] = "";
   long        x_prev      =    0;
   long        x_dur       =    0;
   /*---(check for existing)-------------*/
   rc = ysec__find ("ACTIVE" , a_rpid, &x_pos);
   yLOG_sint   (rc);
   --rce;  if  (rc <  0) {
      yLOG_sexitr (__FUNCTION__, rce);
      return rce;
   }
   yLOG_sint   (x_pos);
   /*---(gather info)--------------------*/
   f = fopen (n_hestia, "r+");
   yLOG_spoint (f);
   --rce;  if (f == NULL) {
      yLOG_sexitr (__FUNCTION__, rce);
   }
   /*---(mark active)--------------------*/
   fseek   (f, x_pos +  29, SEEK_SET);
   if (a_good  == 'y')   fprintf (f, "complete");
   else                  fprintf (f, "mystery ");
   yLOG_snote  ("marked");
   /*---(get start time)-----------------*/
   fseek   (f, x_pos +  77, SEEK_SET);
   fread   (t, 10,  1, f);
   x_prev = atol (t);
   x_dur  = a_now - x_prev;
   if (x_dur <   0)  x_dur = 0;
   if (x_dur > 99999999)  x_dur = 99999999;
   if      (x_dur <=      5)  sprintf (t, "auto"   );
   else if (x_dur <=     60)  sprintf (t, "quickie");
   else if (x_dur <=   3600)  sprintf (t, "utility");
   else if (x_dur <=  86400)  sprintf (t, "worker" );
   else if (x_dur <= 600000)  sprintf (t, "lazy"   );
   else                       sprintf (t, "zombie");
   yLOG_snote  ("dur");
   /*---(get the stop)-------------------*/
   fseek   (f, x_pos + 206, SEEK_SET);
   fprintf (f, "%-10.10ld  %8ld  %-7.7s ", a_now, x_dur, t);
   /*---(complete)-----------------------*/
   fflush (f);
   fclose (f);
   yLOG_sexit  (__FUNCTION__);
   return 0;
}

char
ySEC_complete           (int a_rpid, char a_good)
{
   return ysec__complete (a_rpid, -1, a_good);
}


char             /* [------] register a boot record --------------------------*/
ysec__system       (char a_type, long a_now)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tTIME      *x_broke     = NULL;
   char        x_time      [LEN_DESC]  = "";
   char        x_host      [LEN_LABEL] = "";
   char        t           [LEN_LABEL] = "";
   FILE       *f           = NULL;
   char        x_recd      [LEN_RECD]  = "";
   /*---(get the date)-------------------*/
   if (a_now < 0)  a_now   = time (NULL);
   x_broke = localtime (&a_now);
   strftime (x_time, LEN_DESC, "%y.%m.%d.%H.%M.%S.%w.%V.%j", x_broke);
   /*---(get the host)-------------------*/
   gethostname (x_host, LEN_LABEL);
   /*---(write the record)---------------*/
   f = fopen (n_hestia, "at");
   --rce;  if (f == NULL)  return rce;
   /*---(gather info)--------------------*/
   f = fopen (n_hestia, "at");
   --rce;  if (a_type == 'b')  strcpy (t, "BOOT----");
   else if    (a_type == 'd')  strcpy (t, "----DOWN");
   else                        return rce;
   fprintf (f, "%26.26s  %-8.8s  %-10.10s  ------------  ------  ", x_time, t, x_host);
   fprintf (f, "%10ld  ---  ---  -  ------------------------------------------  ", a_now);
   fprintf (f, "%-13.13s  ", "-------------");
   fprintf (f, "-  -  -  ---  ------------  ---  ----------  --------  ");
   fprintf (f, "------- \n");
   /*---(complete)-----------------------*/
   fclose (f);
   return 0;
}

char             /* [------] register a boot record --------------------------*/
ysec_system       (char a_type)
{
   return ysec__system (a_type, -1);
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ light  [us.JC0.271.X1]*/ /*-[01.0000.00#.!]-*/ /*-[--.---.---.--]-*/
ysec_new__unit          (char *a_question, char w, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         c           =    0;
   char        x_recd      [LEN_RECD]  = "";
   char        r           [LEN_FULL]  = "";
   char        s           [LEN_RECD]  = "";
   char        t           [LEN_RECD]  = "";
   /*---(defense)------------------------*/
   snprintf (unit_answer, LEN_RECD, "NEW unit         : question unknown");
   /*---(simple)-------------------------*/
   if      (strcmp (a_question, "entry"     )     == 0) {
      switch (w) {
      case 'g' :  ystrlcpy (r, n_getty  , LEN_FULL);   break;
      case 'h' :  ystrlcpy (r, n_hestia , LEN_FULL);   break;
      }
      /*> c = yEXEC_file_verify (r, n, x_recd);                                       <*/
      ystrldchg (x_recd, '', '§', LEN_RECD);
      snprintf (unit_answer, LEN_RECD, "BASE %c recd (%2d) : %3d  %3d[%s]", w, n, c, strlen (x_recd), x_recd);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


