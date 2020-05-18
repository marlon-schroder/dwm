/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char buttonbar[]       = "";
static const char *fonts[]          = { "Sans:size=11", "HackNerdFont:size=16", };

static const char normbordercolor[]	= "#777777";
static const char normbgcolor[]		= "#000000";
static const char normfgcolor[]		= "#777777";
static const char selbordercolor[]	= "#FF5D73";
static const char selbgcolor[]		= "#000000";
static const char selfgcolor[]		= "#ffffff";

static const unsigned int baralpha = 0xCC;
static const unsigned int borderalpha = OPAQUE;

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/*
static const char normbordercolor[]	= "#555555";
static const char normbgcolor[]		= "#F6F5F4";
static const char normfgcolor[]		= "#31363d";
static const char selbordercolor[]	= "#FF5D73";
static const char selbgcolor[]		= "#F6F5F4";
static const char selfgcolor[]		= "#FF5D73";
*/

/*
#FF5D73
#3584E4
95% - F2
90% - E6
85% - D9
80% - CC
75% - BF
*/

static const char *colors[][3]      = {
	/*					fg				bg				border   */
	[SchemeNorm]	= { normfgcolor,	normbgcolor,	normbordercolor },
	[SchemeSel]		= { selfgcolor,		selbgcolor,		selbordercolor },
	[SchemeWarn]	= { normfgcolor,	selbgcolor,		selbordercolor },
	[SchemeUrgent]	= { selfgcolor,		selbgcolor,		selbordercolor },
	[SchemeHid]		= { normfgcolor,	normbgcolor,	normbordercolor },
};

/* ﯇  *         */
static const char *tags[] = { "  ", "  ", "  ", "  ﱮ", "  ", "  ", "  ", "  ", "  " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      			instance    title       tags mask    	iscentered	isfloating	monitor */
	{ "Gimp",				NULL,		NULL,		0,				1,			1,		-1 },
	{ "XCalc",				NULL,		NULL,		0,				1,			1,		-1 },
	{ "St",					NULL,		NULL,		1 << 0,			0,			0,		-1 },
	{ "Google-chrome",		NULL,		NULL,		1 << 1,			0,			0,		-1 },
	{ "Chromium",			NULL,		NULL,		1 << 1,			0,			0,		-1 },
    { "Firefox",            NULL,       NULL,       1 << 1,         0,			0,      -1 },
    { "firefox",            NULL,       NULL,       1 << 1,         0,			0,      -1 },
	{ "Min",				NULL,		NULL,		1 << 1,			0,			0,		-1 },
	{ "Sublime_text",		NULL,		NULL,		1 << 2,			0,			0,		-1 },
    { "Code - OSS",         NULL,       NULL,       1 << 2,         0,			0,      -1 },
    { "Gnome-calculator",	NULL,		NULL,		1 << 2,			0,			0,		-1 },
	{ "Nemo",				NULL,		NULL,		1 << 3,			0,			0,		-1 },
	{ "Pcmanfm",			NULL,		NULL,		1 << 3,			0,			0,		-1 },
	{ "Thunar",				NULL,		NULL,		1 << 3,			0,			0,		-1 },
	{ "Org.gnome.Nautilus",	NULL,		NULL,		1 << 3,			0,			0,		-1 },
	{ "Transmission-gtk",	NULL,		NULL,		1 << 4,			0,			0,		-1 },
	{ "Steam",				NULL,		NULL,		1 << 5,			0,			0,		-1 },
	{ "mpv",				NULL,		NULL,		1 << 6,			0,			0,		-1 },
	{ "qemu-system-x86_64",	NULL,		NULL,		1 << 7,			1,			1,		-1 },
	{ "kvm",				NULL,		NULL,		1 << 7,			1,			1,		-1 },
	{ "VirtualBox",			NULL,		NULL,		1 << 7,			0,			0,		-1 },
    { "Virt-manager",       NULL,       NULL,       1 << 7,         0,			0,      -1 },
	{ "DB Browser for SQLite",	NULL,	NULL,		1 << 8,			0,			0,		-1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "layout.c"
#include "fibonacci.c"
static const Layout layouts[] = {
	{ "[M]",      monocle }, /* first entry is default */
	{ "[@]",      spiral },
	{ "[&]",      dwindle },
 	{ "[#]",      grid },
	{ "[T]",      tile },
	{ "[F]",      NULL }, /* no layout function means floating behavior */
};

#define MOD1	Mod1Mask	/* ALT key */
#define MOD4	Mod4Mask	/* Super/Windows key */
#define CONTROL	ControlMask	/* Control key */
#define SHIFT	ShiftMask	/* Shift key */

#define TAGKEYS(KEY,TAG) \
{ MOD4,					KEY, view,			{.ui = 1 << TAG} }, \
{ MOD4|CONTROL,			KEY, toggleview,	{.ui = 1 << TAG} }, \
{ MOD4|SHIFT,			KEY, tag,			{.ui = 1 << TAG} }, \
{ MOD4|CONTROL|SHIFT,	KEY, toggletag,		{.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
// #define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *launchcmd[]		= { "launcher.sh", NULL };
static const char *dmenucmd[]		= { "rox.sh", NULL };
static const char *termcmd[]		= { "terminal.sh", NULL };
static const char *lockcmd[]		= { "lock.sh", NULL };
static const char *scrotcmd[]		= { "popup.sh", "screenshot", NULL };
static const char *actions[]		= { "actions.sh", NULL };
static const char *todo[]			= { "todo.sh", NULL };
static const char *clipmenu[]		= { "clipboard.sh", NULL };
static const char *winviewcmd[]		= { "winview.sh", NULL };
static const char *killcmd[]		= { "kill.sh", NULL };
static const char *monitorcmd[]		= { "monitor.sh", NULL };
static const char *netmenucmd[]		= { "netmenu.sh", NULL };
static const char *off_touchpad[]	= { "popup.sh", "touchpad", NULL };
static const char *off_monitor[]	= { "popup.sh", "brightness", "off", NULL };
static const char *down_bright[]	= { "popup.sh", "brightness", "down", NULL };
static const char *up_bright[]		= { "popup.sh", "brightness", "up", NULL };
static const char *mute[]			= { "popup.sh", "volume", "mute", NULL };
static const char *up_vol[]			= { "popup.sh", "volume", "up", NULL };
static const char *down_vol[]		= { "popup.sh", "volume", "down", NULL };

//static const char scratchpadname[] = "scratchpad";
//static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, NULL };

static Key keys[] = {
	/* modifier			key			function		argument */
	{ 0,				XK_Print,	spawn,			{.v = scrotcmd } },
	{ MOD4,				XK_t,		spawn,			{.v = lockcmd } },
	{ MOD4,				XK_d,		spawn,			{.v = dmenucmd } },
	{ MOD4,				XK_p,		spawn,			{.v = dmenucmd } },
	//{ MOD4,			XK_w,		tabmode,		{-1} },
	{ MOD4,				XK_space,	spawn,			{.v = launchcmd } },
	{ MOD4,				XK_l,		spawn,			{.v = todo } },
	{ MOD4,				XK_Delete,	spawn,			{.v = clipmenu } },
	{ 0,				XK_F12,		spawn,			{.v = termcmd } },
	//{ 0,				XK_F12,		togglescratch,  {.v = scratchpadcmd } },
	{ MOD4,				XK_Return,	spawn,			{.v = termcmd } },
	{ MOD4,				XK_Escape,	spawn,			{.v = actions } },
	{ MOD4,				XK_F7,		spawn,			{.v = off_monitor } },
	{ MOD4,				XK_F5,		spawn,			{.v = down_bright } },
	{ MOD4,				XK_F6,		spawn,			{.v = up_bright } },
	{ MOD4,				XK_F8,		spawn,			{.v = monitorcmd } },
	{ MOD4,				XK_F2,		spawn,			{.v = netmenucmd } },
	{ MOD4,				XK_F10,		spawn,			{.v = mute } },
	{ MOD4,				XK_F12,		spawn,			{.v = up_vol } },
	{ MOD4,				XK_F11,		spawn,			{.v = down_vol } },
	{ MOD4,				XK_F9,		spawn,			{.v = off_touchpad } },
	{ MOD4,				XK_w,		spawn,			{.v = winviewcmd } },
	{ MOD4,				XK_q,		spawn,			{.v = killcmd } },
	{ MOD4,				XK_b,		togglebar,		{0} },
	{ MOD4,				XK_h,		incnmaster,		{.i = +1 } },			// divida as janelas horizontalmente
	{ MOD4,				XK_v,		incnmaster,		{.i = -1 } },			// divide as janelas verticalmente
	{ MOD4,				XK_Page_Down,	setmfact,		{.f = -0.05} },		// diminui lateralmente
	{ MOD4,				XK_Page_Up,		setmfact,		{.f = +0.05} },		// aumenta lateralmente
	{ MOD4,				XK_z,		zoom,			{0} },
	//{ MOD4,			    XK_Tab,		view,			{0} },					// alterna entre workspace
	{ MOD4,				XK_Tab,		focusstack,		{.i = +1 } },
	{ MOD4,				XK_j,		focusstack,		{.i = +1 } },			// proxima janela
	{ MOD1,				XK_Tab,		focusstack,		{.i = +1 } },
	{ MOD4,				XK_k,		focusstack,		{.i = -1 } },			// janela anterior
	{ MOD1,				XK_F4,		killclient,		{0} },					// fecha a janela
	{ MOD4|SHIFT,		XK_q,		quit,			{0} },
	{ MOD4,				XK_Left,	setlayout,		{.v = &layouts[1]} },	// fibonacci
	{ MOD4,				XK_Right,	setlayout,		{.v = &layouts[1]} },	// fibonacci
	{ MOD4,				XK_g,		setlayout,		{.v = &layouts[3]} },	// grid
	//{ MOD4,			XK_t,		setlayout,		{.v = &layouts[2]} },
	{ MOD4,				XK_o,		winview,		{0} },
	//{ MOD4,			XK_w,		setlayout,		{.v = &layouts[1]} },
	{ MOD4,				XK_Down,	setlayout,		{.v = &layouts[5]} },	// float
	{ MOD4,				XK_Up,		setlayout,		{.v = &layouts[0]} },	// maximiza a janela
	//{ MOD4,			XK_space,	setlayout,		{0} },					// alterna tipos de janelas
	{ MOD4,				XK_Down,	togglefloating, {0} },					// faz float da janela ou a agrupa ao ramo
	{ MOD4,				XK_0,		view,			{.ui = ~0 } },			// Seleciona todas as workspaces
	{ MOD4|SHIFT,		XK_0,		tag,			{.ui = ~0 } },			// faz janela vista em todos workspaces
	{ MOD4,				XK_comma,	focusmon,		{.i = -1 } },			// focus left monitor
	{ MOD4,				XK_period,	focusmon,		{.i = +1 } },			// focus right monitor
	{ MOD4|SHIFT,		XK_comma,	tagmon,			{.i = -1 } },			// comma = virgula
	{ MOD4|SHIFT,		XK_period,	tagmon,			{.i = +1 } },			// period = ponto
	{ MOD4|SHIFT,		XK_Down,	moveresize,		{.v = (int []){ 0, 25, 0, 0 }}},
	{ MOD4|SHIFT,		XK_Up,		moveresize,		{.v = (int []){ 0, -25, 0, 0 }}},
	{ MOD4|SHIFT,		XK_Right,	moveresize,		{.v = (int []){ 25, 0, 0, 0 }}},
	{ MOD4|SHIFT,		XK_Left,	moveresize,		{.v = (int []){ -25, 0, 0, 0 }}},
	{ MOD4|CONTROL,		XK_Up,		moveresize,		{.v = (int []){ 0, 0, 0, 25 }}},
	{ MOD4|CONTROL,		XK_Down,	moveresize,		{.v = (int []){ 0, 0, 0, -25 }}},
	{ MOD4|CONTROL,		XK_Right,	moveresize,		{.v = (int []){ 0, 0, 25, 0 }}},
	{ MOD4|CONTROL,		XK_Left,	moveresize,		{.v = (int []){ 0, 0, -25, 0 }}},
	TAGKEYS(			XK_1, 0)
	TAGKEYS(			XK_2, 1)
	TAGKEYS(			XK_3, 2)
	TAGKEYS(			XK_4, 3)
	TAGKEYS(			XK_5, 4)
	TAGKEYS(			XK_6, 5)
	TAGKEYS(			XK_7, 6)
	TAGKEYS(			XK_8, 7)
	TAGKEYS(			XK_9, 8)
};

/* ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, ClkRootWin */
// Button1 (left)
// Button2 (middle)
// Button3 (right)
// Button4 (scroll down)
// Button5 (scroll up)
static Button buttons[] = {
	/* click			event mask	button		function		argument */
	{ ClkWinTitle,		0,			Button1,	togglewin,		{0} },
	{ ClkButton,		0,			Button1,	spawn,			{.v = dmenucmd } },
	{ ClkClientWin,		MOD4,		Button5,	setmfact,		{.f = +0.05} },		// aumenta lateralmente com scroll pra cima
	{ ClkClientWin,		MOD4,		Button4,	setmfact,		{.f = -0.05} },		// diminui lateralmente com scroll pra baixo
	{ ClkTagBar,		MOD4,		Button1,	tag,			{0} },				// manda janela para a workspace
	{ ClkTagBar,		MOD4,		Button3,	toggletag,		{0} },				// deixa a janela visivel tambem na workspace
	{ ClkClientWin,		MOD4,		Button1,	movemouse,		{0} },				// para mover
	{ ClkClientWin,		MOD4,		Button1,	winview,		{0} },
	{ ClkClientWin,		MOD4,		Button2,	togglefloating,	{0} },				// retira ou agrupa ao ramo desmaximizando*
	{ ClkClientWin,		MOD4,		Button3,	resizemouse,	{0} },				// para redimensionar
	{ ClkLtSymbol,		0,			Button1,	setlayout,		{0} },				// muda layout das janelas clicando nestes
	{ ClkWinTitle,		0,			Button4,	focusstack,		{.i = -1 } },		// scroll nos titulos para alternar janelas
	{ ClkWinTitle,		0,			Button5,	focusstack,		{.i = +1 } },		// scroll nos titulos para alternar janelas
	//{ ClkWinTitle,	0,			Button1,	focusstack,		{.i = +1 } },		// para alternar janelas
	{ ClkWinTitle,		0,			Button3,	killclient,		{0} },				// close window
	//{ ClkStatusText,	0,			Button2,	spawn,			{.v = termcmd } },	// abre terminal (botao direito no texto)
	{ ClkTagBar,		0,			Button1,	view,			{0} },				//
	{ ClkTagBar,		0,			Button3,	toggleview,		{0} },				// seleciona a workspace
	//{ ClkTabBar,		0,			Button1,	focuswin,		{0} },
};
