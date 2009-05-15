#include <stdlib.h>
#include <string.h>
#ifndef lint
#ifdef __unused
__unused
#endif
static char const 
yyrcsid[] = "$FreeBSD: src/usr.bin/yacc/skeleton.c,v 1.37.22.1.2.1 2008/11/25 02:59:29 kensmith Exp $";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
#if defined(__cplusplus) || __STDC__
static int yygrowstack(void);
#else
static int yygrowstack();
#endif
#define YYPREFIX "yy"
#line 2 "parser.y"
/*
 * parser.y
 */

/*-
 * Copyright (c) 2006 Maksim Yevmenkin <m_evmenkin@yahoo.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id: parser.y 2 2007-04-17 21:22:08Z chhsiao $
 * $FreeBSD: src/usr.sbin/bluetooth/bthidd/parser.y,v 1.4.2.2 2006/12/01 23:33:22 emax Exp $
 */

#include <sys/queue.h>
#include <bluetooth.h>
#include <dev/usb/usb.h>
#include <dev/usb/usbhid.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <usbhid.h>

#ifndef BTHIDCONTROL
#include <stdarg.h>
#include <syslog.h>
#define	SYSLOG		syslog
#define	LOGCRIT		LOG_CRIT
#define	LOGERR		LOG_ERR
#define	LOGWARNING	LOG_WARNING
#define	EOL
#else
#define	SYSLOG		fprintf
#define	LOGCRIT		stderr
#define	LOGERR		stderr
#define	LOGWARNING	stderr
#define	EOL	"\n"
#endif /* ndef BTHIDCONTROL */

#include "bsdmote_config.h"

	int	yyparse		(void);
	int	yylex		(void);
	void	yyerror		(char const *);
static	int32_t	check_hid_device(hid_device_p hid_device);
static	void	free_hid_device	(hid_device_p hid_device);

extern	FILE			*yyin;
extern	int			 yylineno;
	char const		*config_file_1 = BTHIDD_CONFFILE_1;
        char const              *config_file_2 = BTHIDD_CONFFILE_2;
	char const		*hids_file   = BTHIDD_HIDSFILE;

static	char			 buffer[1024];
static	int32_t			 hid_descriptor_size;
static	hid_device_t		*hid_device = NULL;
static	LIST_HEAD(, hid_device)	 hid_devices;

#line 83 "parser.y"
typedef union {
	bdaddr_t	bdaddr;
	int32_t		num;
} YYSTYPE;
#line 110 "parser.c"
#define YYERRCODE 256
#define T_BDADDRSTRING 257
#define T_HEXBYTE 258
#define T_DEVICE 259
#define T_BDADDR 260
#define T_CONTROL_PSM 261
#define T_INTERRUPT_PSM 262
#define T_RECONNECT_INITIATE 263
#define T_BATTERY_POWER 264
#define T_NORMALLY_CONNECTABLE 265
#define T_HID_DESCRIPTOR 266
#define T_TRUE 267
#define T_FALSE 268
#define T_ERROR 269
const short yylhs[] = {                                        -1,
    0,    0,    2,    1,    3,    3,    4,    4,    4,    4,
    4,    4,    4,    4,    5,    6,    7,    8,    8,    9,
    9,   10,   10,   13,   11,   14,   14,   15,   12,
};
const short yylen[] = {                                         2,
    1,    2,    0,    5,    2,    3,    1,    1,    1,    1,
    1,    1,    1,    1,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    0,    5,    1,    2,    1,    1,
};
const short yydefred[] = {                                      0,
    3,    0,    1,    0,    2,    0,    0,    0,    0,    0,
    0,    0,   24,   29,    0,    0,    7,    8,    9,   10,
   11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
   21,   22,   23,    0,    4,    0,    5,    0,    6,   28,
    0,   26,   25,   27,
};
const short yydgoto[] = {                                       2,
    3,    4,   15,   16,   17,   18,   19,   20,   21,   22,
   23,   24,   34,   41,   42,
};
const short yysindex[] = {                                   -250,
    0, -250,    0, -113,    0, -258, -239, -238, -237, -255,
 -253, -251,    0,    0, -125,  -40,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -101,    0,  -36,    0, -234,    0,    0,
 -124,    0,    0,    0,
};
const short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,
};
const short yygindex[] = {                                      0,
   23,    0,    0,   11,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -14,
};
#define YYTABLESIZE 144
const short yytable[] = {                                      35,
   43,    7,    8,    9,   10,   11,   12,   13,    1,    6,
   14,   28,   29,   30,   31,   32,   33,   25,   37,   26,
   27,   38,   39,   40,    5,   36,   44,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   40,    7,    8,    9,   10,   11,   12,
   13,    0,    0,   14,
};
const short yycheck[] = {                                     125,
  125,  260,  261,  262,  263,  264,  265,  266,  259,  123,
  269,  267,  268,  267,  268,  267,  268,  257,   59,  258,
  258,  123,   59,  258,    2,   15,   41,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  258,  260,  261,  262,  263,  264,  265,
  266,   -1,   -1,  269,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 269
#if YYDEBUG
const char * const yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"';'",0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"T_BDADDRSTRING",
"T_HEXBYTE","T_DEVICE","T_BDADDR","T_CONTROL_PSM","T_INTERRUPT_PSM",
"T_RECONNECT_INITIATE","T_BATTERY_POWER","T_NORMALLY_CONNECTABLE",
"T_HID_DESCRIPTOR","T_TRUE","T_FALSE","T_ERROR",
};
const char * const yyrule[] = {
"$accept : config",
"config : line",
"config : config line",
"$$1 :",
"line : T_DEVICE $$1 '{' options '}'",
"options : option ';'",
"options : options option ';'",
"option : bdaddr",
"option : control_psm",
"option : interrupt_psm",
"option : reconnect_initiate",
"option : battery_power",
"option : normally_connectable",
"option : hid_descriptor",
"option : parser_error",
"bdaddr : T_BDADDR T_BDADDRSTRING",
"control_psm : T_CONTROL_PSM T_HEXBYTE",
"interrupt_psm : T_INTERRUPT_PSM T_HEXBYTE",
"reconnect_initiate : T_RECONNECT_INITIATE T_TRUE",
"reconnect_initiate : T_RECONNECT_INITIATE T_FALSE",
"battery_power : T_BATTERY_POWER T_TRUE",
"battery_power : T_BATTERY_POWER T_FALSE",
"normally_connectable : T_NORMALLY_CONNECTABLE T_TRUE",
"normally_connectable : T_NORMALLY_CONNECTABLE T_FALSE",
"$$2 :",
"hid_descriptor : T_HID_DESCRIPTOR $$2 '{' hid_descriptor_bytes '}'",
"hid_descriptor_bytes : hid_descriptor_byte",
"hid_descriptor_bytes : hid_descriptor_bytes hid_descriptor_byte",
"hid_descriptor_byte : T_HEXBYTE",
"parser_error : T_ERROR",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
#line 222 "parser.y"

/* Display parser error message */
void
yyerror(char const *message)
{
	SYSLOG(LOGERR, "%s in line %d" EOL, message, yylineno); 
}

/* Re-read config file */
int32_t
read_config_file(void)
{
	int32_t	e;

	if (config_file_1 == NULL && config_file_2 == NULL) {
		SYSLOG(LOGERR, "Unknown config file name!" EOL);
		return (-1);
	}

	if ((yyin = fopen(config_file_1, "r")) == NULL)
            if((yyin = fopen(config_file_2, "r")) == NULL) {
                SYSLOG(LOGERR, "Could not open config file '%s'. %s (%d)" EOL,
                       config_file_1, strerror(errno), errno);
		return (-1);
            }
        

	clean_config();
	if (yyparse() < 0) {
		SYSLOG(LOGERR, "Could not parse config file '%s'" EOL,
                       config_file_1);
		e = -1;
	} else
		e = 0;

	fclose(yyin);
	yyin = NULL;

	return (e);
}

/* Clean config */
void
clean_config(void)
{
	while (!LIST_EMPTY(&hid_devices)) {
		hid_device_p	d = LIST_FIRST(&hid_devices);

		LIST_REMOVE(d, next);
		free_hid_device(d);
	}
}

/* Lookup config entry */
hid_device_p
get_hid_device(bdaddr_p bdaddr)
{
	hid_device_p	d;

	LIST_FOREACH(d, &hid_devices, next)
		if (memcmp(&d->bdaddr, bdaddr, sizeof(bdaddr_t)) == 0)
			break;

	return (d);
}

/* Get next config entry */
hid_device_p
get_next_hid_device(hid_device_p d)
{
	return ((d == NULL)? LIST_FIRST(&hid_devices) : LIST_NEXT(d, next));
}

/* Print config entry */
void
print_hid_device(hid_device_p d, FILE *f)
{
	/* XXX FIXME hack! */
	struct report_desc {
		unsigned int	size;
		unsigned char	data[1];
	};
	/* XXX FIXME hack! */

	struct report_desc	*desc = (struct report_desc *) d->desc;
	uint32_t		 i;

	fprintf(f,
"device {\n"					\
"	bdaddr			%s;\n"		\
"	control_psm		0x%x;\n"	\
"	interrupt_psm		0x%x;\n"	\
"	reconnect_initiate	%s;\n"		\
"	battery_power		%s;\n"		\
"	normally_connectable	%s;\n"		\
"	hid_descriptor		{",
		bt_ntoa(&d->bdaddr, NULL),
		d->control_psm, d->interrupt_psm,
                d->reconnect_initiate? "true" : "false",
                d->battery_power? "true" : "false",
                d->normally_connectable? "true" : "false");
 
	for (i = 0; i < desc->size; i ++) {
			if ((i % 8) == 0)
				fprintf(f, "\n		");
 
			fprintf(f, "0x%2.2x ", desc->data[i]);
	}
                
	fprintf(f,
"\n"		\
"	};\n"	\
"}\n");
}

/* Check config entry */
static int32_t
check_hid_device(hid_device_p d)
{
	hid_data_t	hd;
	hid_item_t	hi;
	int32_t		page;

	if (get_hid_device(&d->bdaddr) != NULL) {
		SYSLOG(LOGERR, "Ignoring duplicated entry for bdaddr %s" EOL,
				bt_ntoa(&d->bdaddr, NULL));
		return (0);
	}

	if (d->control_psm == 0) {
		SYSLOG(LOGERR, "Ignoring entry with invalid control PSM" EOL);
		return (0);
	}

	if (d->interrupt_psm == 0) {
		SYSLOG(LOGERR, "Ignoring entry with invalid interrupt PSM" EOL);
		return (0);
	}

	if (d->desc == NULL) {
		SYSLOG(LOGERR, "Ignoring entry without HID descriptor" EOL);
		return (0);
	}

	/* XXX somehow need to make sure descriptor is valid */
	for (hd = hid_start_parse(d->desc, ~0, -1); hid_get_item(hd, &hi) > 0; ) {
		switch (hi.kind) {
		case hid_collection:
		case hid_endcollection:
		case hid_output:
		case hid_feature:
			break;

		case hid_input:
			/* Check if the device may send keystrokes */
			page = HID_PAGE(hi.usage);
			if (page == HUP_KEYBOARD)
				d->keyboard = 1;
			break;
		}
	}
	hid_end_parse(hd);

	return (1);
}

/* Free config entry */
static void
free_hid_device(hid_device_p d)
{
	if (d->desc != NULL)
		hid_dispose_report_desc(d->desc);

	memset(d, 0, sizeof(*d));
	free(d);
}

/* Re-read hids file */
int32_t
read_hids_file(void)
{
	FILE		*f;
	hid_device_t	*d;
	char		*line;
	bdaddr_t	 bdaddr;
	int32_t		 lineno;

	if (hids_file == NULL) {
		SYSLOG(LOGERR, "Unknown HIDs file name!" EOL);
		return (-1);
	}

	if ((f = fopen(hids_file, "r")) == NULL) {
		if (errno == ENOENT)
			return (0);

		SYSLOG(LOGERR, "Could not open HIDs file '%s'. %s (%d)" EOL,
			hids_file, strerror(errno), errno);
		return (-1);
	}

	for (lineno = 1; fgets(buffer, sizeof(buffer), f) != NULL; lineno ++) {
		if ((line = strtok(buffer, "\r\n\t ")) == NULL)
			continue; /* ignore empty lines */

		if (!bt_aton(line, &bdaddr)) {
			SYSLOG(LOGWARNING, "Ignoring unparseable BD_ADDR in " \
				"%s:%d" EOL, hids_file, lineno);
			continue;
		}

		if ((d = get_hid_device(&bdaddr)) != NULL)
			d->new_device = 0;
	}

	fclose(f);

	return (0);
}

/* Write hids file */
int32_t
write_hids_file(void)
{
	char		 path[PATH_MAX];
	FILE		*f;
	hid_device_t	*d;

	if (hids_file == NULL) {
		SYSLOG(LOGERR, "Unknown HIDs file name!" EOL);
		return (-1);
	}

	snprintf(path, sizeof(path), "%s.new", hids_file);

	if ((f = fopen(path, "w")) == NULL) {
		SYSLOG(LOGERR, "Could not open HIDs file '%s'. %s (%d)" EOL,
			path, strerror(errno), errno);
		return (-1);
	}

	LIST_FOREACH(d, &hid_devices, next)
		if (!d->new_device)
			fprintf(f, "%s\n", bt_ntoa(&d->bdaddr, NULL));

	fclose(f);

	if (rename(path, hids_file) < 0) {
		SYSLOG(LOGERR, "Could not rename new HIDs file '%s' to '%s'. " \
			"%s (%d)" EOL, path, hids_file, strerror(errno), errno);
		unlink(path);
		return (-1);
	}

	return (0);
}

#line 535 "parser.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack()
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = yyssp - yyss;
    newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss);
    if (newss == NULL)
        return -1;
    yyss = newss;
    yyssp = newss + i;
    newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs);
    if (newvs == NULL)
        return -1;
    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#ifndef YYPARSE_PARAM
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG void
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif	/* ANSI-C/C++ */
#else	/* YYPARSE_PARAM */
#ifndef YYPARSE_PARAM_TYPE
#define YYPARSE_PARAM_TYPE void *
#endif
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG YYPARSE_PARAM_TYPE YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL YYPARSE_PARAM_TYPE YYPARSE_PARAM;
#endif	/* ANSI-C/C++ */
#endif	/* ! YYPARSE_PARAM */

int
yyparse (YYPARSE_PARAM_ARG)
    YYPARSE_PARAM_DECL
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate])) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 3:
#line 101 "parser.y"
{
			hid_device = (hid_device_t *) calloc(1, sizeof(*hid_device));
			if (hid_device == NULL) {
				SYSLOG(LOGCRIT, "Could not allocate new " \
						"config entry" EOL);
				YYABORT;
			}

			hid_device->new_device = 1;
			}
break;
case 4:
#line 112 "parser.y"
{
			if (check_hid_device(hid_device))
				LIST_INSERT_HEAD(&hid_devices,hid_device,next);
			else
				free_hid_device(hid_device);

			hid_device = NULL;
			}
break;
case 15:
#line 137 "parser.y"
{
			memcpy(&hid_device->bdaddr, &yyvsp[0].bdaddr, sizeof(hid_device->bdaddr));
			}
break;
case 16:
#line 143 "parser.y"
{
			hid_device->control_psm = yyvsp[0].num;
			}
break;
case 17:
#line 149 "parser.y"
{
			hid_device->interrupt_psm = yyvsp[0].num;
			}
break;
case 18:
#line 155 "parser.y"
{
			hid_device->reconnect_initiate = 1;
			}
break;
case 19:
#line 159 "parser.y"
{
			hid_device->reconnect_initiate = 0;
			}
break;
case 20:
#line 165 "parser.y"
{
			hid_device->battery_power = 1;
			}
break;
case 21:
#line 169 "parser.y"
{
			hid_device->battery_power = 0;
			}
break;
case 22:
#line 175 "parser.y"
{
			hid_device->normally_connectable = 1;
			}
break;
case 23:
#line 179 "parser.y"
{
			hid_device->normally_connectable = 0;
			}
break;
case 24:
#line 185 "parser.y"
{
			hid_descriptor_size = 0;
			}
break;
case 25:
#line 189 "parser.y"
{
			if (hid_device->desc != NULL)
				hid_dispose_report_desc(hid_device->desc);

			hid_device->desc = hid_use_report_desc((unsigned char *) buffer, hid_descriptor_size);
			if (hid_device->desc == NULL) {
				SYSLOG(LOGCRIT, "Could not use HID descriptor" EOL);
				YYABORT;
			}
			}
break;
case 28:
#line 206 "parser.y"
{
			if (hid_descriptor_size >= (int32_t) sizeof(buffer)) {
				SYSLOG(LOGCRIT, "HID descriptor is too big" EOL);
				YYABORT;
			}

			buffer[hid_descriptor_size ++] = yyvsp[0].num;
			}
break;
case 29:
#line 217 "parser.y"
{
				YYABORT;
			}
break;
#line 847 "parser.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
