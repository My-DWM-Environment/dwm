#include "layouts.h"
#include "cmds.h"

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  		          = 1;        /* border pixel of windows */
static const unsigned int snap      		          = 32;       /* snap pixel */
static const unsigned int systraypinning          = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft           = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing          = 2;   /* systray spacing */
static const int systraypinningfailfirst          = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray                      = 1;     /* 0 means no systray */
static const int showbar                          = 1;     /* 0 means no bar */
static const int topbar                           = 1;     /* 0 means bottom bar */
static const unsigned int mousewrap		            = 1; // 1 - enable mouse warp, 0 - disable mouse warp
static const char *fonts[]                        = {
	"monospace:size=10",
	"Terminus:size=10",
	"Font Awesome 6 Pro:size=12",
	"Font Awesome 6 Brands:size=12",
	"Layout Font:size=14",
};
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     border width    isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            borderpx,       1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       borderpx,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "␧",          tile },
	{ "␨",          tile2 },
	{ "␩",   	      NULL },
	{ "␪",          monocle },
	{ "␫",          grid },
	{ "␬",          dwindle },
	{ "␭",          spiral },
	{ "␮",          bstack },
	{ "␯",          bstackhoriz },
};

/* tagging */
static Tag tags[] = {
	{ "", &layouts[7] },
	{ "", &layouts[3] },
	{ "", &layouts[0] },
	{ "", &layouts[3] },
	{ "", &layouts[1] },
	{ "", &layouts[3] },
	{ "", &layouts[3] },
	{ "", &layouts[0] },
	{ "", &layouts[0] }
};

#include "funcions.h"

/* key definitions */
#define ALT Mod1Mask
#define MODKEY Mod4Mask
#define SHIFT ShiftMask
#define CTRL ControlMask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|CTRL,                  KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|SHIFT,                 KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|CTRL|SHIFT,            KEY,      toggletag,      {.ui = 1 << TAG} },

static Key keys[] = {
	/* modifier                     key        function        argument */

	/* rofi menu shortcuts */
	{ ALT,  	                      XK_p,      spawn,          {.v = dmenucmd } },
	{ ALT,  	                      XK_c,      spawn,          {.v = dmenuClipCmd } },
	{ ALT,  	                      XK_r,      spawn,          {.v = dmenuRecentCmd } },

	/* run app shortcuts */
	{ ALT,						              XK_t, 		 spawn,          {.v = termcmd } },
	{ ALT,						              XK_w, 		 spawn,          {.v = googlechromecmd } },
	{ ALT,						              XK_a, 		 spawn,          {.v = audaciouscmd } },
	{ ALT,						              XK_x, 		 spawn,          {.v = vscodecmd } },
	{ ALT,						              XK_e, 		 spawn,          {.v = nemocmd } },

	/* system shortcuts */
	{ MODKEY ,				              XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_x,	   	 spawn,	       	 {.v = xkillcmd } },

	/* layouts */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|SHIFT,                 XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|SHIFT,                 XK_g,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|SHIFT,                 XK_d,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|SHIFT,                 XK_s,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY|SHIFT,                 XK_c,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY|SHIFT,                 XK_h,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY,                       XK_b,      setlayout,      {0} },

	/* dwm shortcuts */
	{ MODKEY,                       XK_space,  togglebar,      {0} },
	{ MODKEY,                       XK_s,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_w,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Left,   shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_Right,  shiftview,      {.i = +1 } },
	{ MODKEY|ALT,                   XK_w,      movestack,      {.i = -1 } },
	{ MODKEY|ALT,                   XK_s,      movestack,      {.i = +1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_a,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_d,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|SHIFT,             		XK_b,  		 togglefloating, {0} },

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|SHIFT,                 XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|SHIFT,                 XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|SHIFT,                 XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|SHIFT,                 XK_Left,   tagtoleft,      {0} },
	{ MODKEY|SHIFT,                 XK_Right,  tagtoright,     {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|CTRL|SHIFT,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

