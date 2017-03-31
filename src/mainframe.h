/**
 * Copyright (c) 2005 PCMan <pcman.tw@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef MAINFRAME_H
#define MAINFRAME_H

#ifdef __GNUG__
  #pragma interface "mainframe.h"
#endif

#include "pcmanx_utils.h"

#include "widget.h"

#ifdef USE_DOCKLET
#include "docklet/api.h"
#endif

#include <string>
#include <vector>
#include <ltdl.h>

using namespace std;

#include "telnetview.h"
#include "editorview.h"
#include <signal.h>

/**
@author PCMan
*/

class CTelnetView;
class CEditorView;
class CNotebook;
class CTelnetCon;
class CEditor;
class CSite;

class CMainFrame : public CWidget
{
public:
	CMainFrame();

	CTelnetCon* NewCon( string title, string url, CSite* site = NULL );
	CNotebook* GetNotebook(){	return m_pNotebook;	}
	void OnTelnetConBell(CTelnetView* con);
	void OnTelnetConClose(CTelnetView* con);
	void OnTelnetConConnect(CTelnetView* con);
	void OnTelnetConRecv(CTelnetView* con);
	static void OnFont(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnAbout(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnShortcutList(GtkMenuItem* mitem, CMainFrame* _this);
	static void pasteFromClipboard(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnCloseSelectCon(GtkWidget* notebook, GtkMenuItem* mitem, CMainFrame* _this);
	static void OnPopupMenuSelectCon(GtkWidget *widget, GtkWidget* menu, GdkEventButton* event, CMainFrame* _this);
	static void OnCloseCon(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnCopy(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnCopyWithColor(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnNextCon(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnFirstCon(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnLastCon(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnPaste(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnDownArticle(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnPreference(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnPrevCon(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnSiteList(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnNotebookChangeCurPage(GtkNotebook* widget, GtkWidget* page,  gint page_num, CMainFrame* _this);
	static gboolean OnNotebookPopupMenu(GtkWidget* widget, GdkEventButton* event, CMainFrame* _this);
	void SetCurView(CTelnetView* view);
	CTelnetView* GetCurView(){	return (m_pView);	}
	CTelnetCon* GetCurCon() {	return (m_pView ? m_pView->GetCon():NULL);	}
	//get Ansi Editor information
	CEditorView* GetCurEditorView() {	return (m_eView);	}
	CEditor* GetCurEditor() {	return (m_eView ? m_eView->GetEditor():NULL);	}
//	CTelnetView* LookupView(GtkWidget* view){	return (CTelnetView*) g_hash_table_lookup(m_TelnetViewHash, view);	}
	static gboolean OnBlinkTimer(CMainFrame* _this);
	static gboolean OnEverySecondTimer(CMainFrame* _this);
	static gboolean OnWindowStateEvent(GtkWindow* window, GdkEventWindowState* event, CMainFrame* _this);
	static gboolean OnClose( GtkWidget* widget, GdkEvent* evt, CMainFrame* _this );
	static gboolean OnSize( GtkWidget* widget, GdkEventConfigure* evt, CMainFrame* _this );
	GObject* m_JumpTos[10];
	void OnDestroy();
	virtual void OnCreate();
	virtual bool CanClose();
	void NotImpl(const char* str);
	static void OnEditFavorites(GtkMenuItem* widget, CMainFrame* _this);
	static void OnFavorite(GtkMenuItem* item, CMainFrame* _this);
	static void OnEmoticons(GtkMenuItem* mitem, CMainFrame* _this);
	static gboolean OnActivated( GtkWidget* widget, GdkEventFocus* evt, CMainFrame* _this );

	bool IsActivated(){	return gtk_window_is_active(GTK_WINDOW(m_Widget));	}
	static gboolean OnURLEntryKeyDown(GtkWidget *widget,GdkEventKey *evt, CMainFrame* _this);
	int GetViewIndex(CTermView* view);
	int GetNearestTab(GtkWidget *widget, GdkEventButton *event);
	void SwitchToCon(CTelnetCon* con);

	vector<CTelnetView*> m_Views;
#ifdef USE_DOCKLET
	void ShowTrayIcon() { if (m_TrayIcon) gtk_status_icon_set_visible(m_TrayIcon, TRUE); };
	void HideTrayIcon() { if (m_TrayIcon) gtk_status_icon_set_visible(m_TrayIcon, FALSE); };
#endif

#ifdef USE_NOTIFIER
	GdkPixbuf *GetMainIcon() { return m_MainIcon; };
#endif

	// Statusbar control.
	unsigned PushStatus(const char *context_desc, const char *text)
	{
	  unsigned context_id = gtk_statusbar_get_context_id(GTK_STATUSBAR(m_Statusbar), context_desc);
	  return gtk_statusbar_push(GTK_STATUSBAR(m_Statusbar), context_id, text);
	}

	void PopStatus(const char *context_desc)
	{
	  unsigned context_id = gtk_statusbar_get_context_id(GTK_STATUSBAR(m_Statusbar), context_desc);
	  return gtk_statusbar_pop(GTK_STATUSBAR(m_Statusbar), context_id);
	}

protected:
	void MakeUI();
	static void OnNewCon(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnQuit(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnFullscreenMode(GtkMenuItem* mitem, CMainFrame* _this);
	void LoadIcons();
	void LoadStartupSites();
	static void OnJumpToPage(GObject* obj, CMainFrame* _this);
	void CloseConAndPageSwitch(int idx, bool confirm UNUSED, GtkWidget *notebook, int page_idx);
	void CloseCon(int idx, bool confirm = false);
	static bool QueryOnCloseCon(CMainFrame* _this);
	static void OnAddToFavorites(GtkMenuItem* widget, CMainFrame* _this);
	void CreateFavoritesMenu();
	void CreateTrayIcon();
	static void OnSelectAll(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnReconnect(GtkMenuItem* mitem, CMainFrame* _this);
	void FlashWindow( bool flash );
	static gboolean OnURLEntryKillFocus(GtkWidget* entry, GdkEventFocus* evt, CMainFrame* _this);

	// Ansi Editor methods.
	static void OnAnsiEditor(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnOpenAnsiFile(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnSaveAnsiFile(GtkMenuItem* mitem, CMainFrame* _this);
	static void OnClearScreen(GtkMenuItem* mitem, CMainFrame* _this);
	//static void OnDownloadToEditor(GtkMenuItem* mitem, CMainFrame* _this);	//todo
	static void SetBlink(GtkToggleButton *togglebutton, CMainFrame* _this);
	static void SetTextColor(GtkComboBox *widget, CMainFrame* _this);
	static void SetBgColor(GtkComboBox *widget, CMainFrame* _this);

#ifdef USE_NANCY
	static GtkRadioActionEntry cur_bot_entries[];
	static GtkRadioActionEntry all_bot_entries[];
	void UpdateBotStatus();
	static void OnChangeCurrentBot(GtkRadioAction* action, GtkRadioAction* current, CMainFrame* _this);
	static void OnChangeAllBot(GtkRadioAction* action, GtkRadioAction* all, CMainFrame* _this);
#endif

#ifdef USE_DOCKLET
	static void OnTrayButton_Toggled(GtkToggleButton *button, CMainFrame* _this);
	static void OnShowHide(GtkToggleAction *toggleaction, CMainFrame *_this);
//	static void OnTrayButton_Changed(GtkWidget* widget, GtkAllocation *allocation, CMainFrame* _this);
	static void OnTray_Popup(GtkStatusIcon *status_icon, guint button, guint activate_time, CMainFrame *_this);
	GtkStatusIcon *m_TrayIcon;
#endif

	static void OnToggleToolBar(GtkToggleAction *toggleaction, CMainFrame *_this);
	static void OnToggleStatusBar(GtkToggleAction *toggleaction, CMainFrame *_this);
	static void OnToggleTabBar(GtkToggleAction *toggleaction, CMainFrame *_this);
	static void OnToggleMenuBar(GtkToggleAction *toggleaction, CMainFrame *_this);

	GdkPixbuf* m_ConnIcon;
	GdkPixbuf* m_MainIcon;
	GdkPixbuf* m_InverseMainIcon;

protected:
	CTelnetView* m_pView;
	CEditorView* m_eView;
	CNotebook* m_pNotebook;
	GtkUIManager* m_UIManager;
	GtkActionGroup* m_ActionGroup;
	GtkWidget* m_Toolbar;
	GtkWidget* m_Menubar;
	GtkWidget* m_EditMenu;
	GtkWidget* m_Statusbar;
	GtkWidget* m_TrayPopup;

	// Ansi editor widgets
	GtkWidget *m_chkBlink;		//checkbox: set text blink
	GtkWidget *m_cbTextColor;	//combobox: set text color
	GtkWidget *m_cbBgColor;		//combobox: set background color

	guint m_BlinkTimer;
	guint m_EverySecondTimer;
	GtkWidget* m_FavoritesMenuItem;
	GtkWidget* m_FavoritesMenu;

	bool m_IsFlashing;
	GtkWidget* m_URLEntry;
/*
	GtkTooltips* m_Tooltips;
*/
	GtkLabel* m_StatusBarTime;

#ifdef USE_NANCY
	GtkLabel* m_StatusBarBotState;
	GtkRadioMenuItem* m_DisableCurBotRadio;
	GtkRadioMenuItem* m_CurBotNancyRadio;
	GtkRadioMenuItem* m_DisableAllBotRadio;
	GtkRadioMenuItem* m_AllBotNancyRadio;
#endif

	static bool g_bIsUpateHandlerExisted;
	static bool g_bUpdateingBBSList;
	static CMainFrame* g_pMyself;
	static GtkActionEntry m_ActionEntries[];
	static GtkToggleActionEntry m_ToggleActionEntries[];

private:
	enum {NORMAL_MODE, FULLSCREEN_MODE} m_Mode;
	lt_dlhandle m_dlhandle;
	void *m_indicator;
	bool m_Unity;
	void AppendRow(GtkTreeIter *iter, GtkListStore *store, const gchar *display, const gchar *color);
	void ParseColor(GdkColor *color, gchar *res, size_t res_len);
};

#endif
