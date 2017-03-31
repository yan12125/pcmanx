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

#ifdef __GNUG__
  #pragma implementation "generalprefpage.h"
#endif

#include <glib/gi18n.h>
#include "generalprefpage.h"
#include "appconfig.h"

#ifdef USE_MOUSE
static void cb_mouse_switch( GtkComboBox *opt, gpointer data )
{
        gint idx = gtk_combo_box_get_active(opt);
	AppConfig.WithMiddleButton = (idx == 0);
}

static bool withMiddleButton = TRUE;
static GtkWidget *make_menu_item ( const char *name, GCallback callback, bool withMB)
{
	GtkWidget *item;

	item = gtk_menu_item_new_with_label (name);
	withMiddleButton = withMB;
	g_signal_connect (item, "activate", callback, (gpointer) &withMiddleButton);
	gtk_widget_show (item);

	return item;
}
#endif

CGeneralPrefPage::CGeneralPrefPage()
 : CWidget()
{
	m_Widget = gtk_vbox_new (FALSE, 2);
	gtk_widget_show (m_Widget);

	PostCreate();

  GtkWidget *hbox18;
	GtkWidget *hbox19;
	GtkWidget *label27;
	GtkWidget *hbox20;
	GtkAdjustment *m_PopupTimeout_adj;
	GtkWidget *label29;
	GtkWidget *hbox21;
	GtkWidget *label30;

	m_QueryOnCloseCon = gtk_check_button_new_with_mnemonic (_("Confirm before closing connected connections"));
	gtk_widget_show (m_QueryOnCloseCon);
	gtk_box_pack_start (GTK_BOX (m_Widget), m_QueryOnCloseCon, FALSE, FALSE, 0);

	m_QueryOnExit = gtk_check_button_new_with_mnemonic (_("Confirm before exiting the program if there are still connections"));
	gtk_widget_show (m_QueryOnExit);
	gtk_box_pack_start (GTK_BOX (m_Widget), m_QueryOnExit, FALSE, FALSE, 0);

	m_CancelSelAfterCopy = gtk_check_button_new_with_mnemonic (_("Cancel selection after copying text"));
	gtk_widget_show (m_CancelSelAfterCopy);
	gtk_box_pack_start (GTK_BOX (m_Widget), m_CancelSelAfterCopy, FALSE, FALSE, 0);

#ifdef USE_MOUSE
	GtkWidget *hboxMouse;
	hboxMouse = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hboxMouse);
	gtk_box_pack_start (GTK_BOX (m_Widget), hboxMouse, FALSE, FALSE, 0);

	m_MouseSupport = gtk_check_button_new_with_mnemonic (_("Enable Mouse Support"));
	gtk_widget_show (m_MouseSupport);
	gtk_box_pack_start (GTK_BOX (hboxMouse), m_MouseSupport, FALSE, FALSE, 0);

	GtkWidget *opt;
        GtkTreeIter iter;

        GtkTreeStore *store = gtk_tree_store_new( 1, G_TYPE_STRING );

        gtk_tree_store_append( store, &iter, NULL );
        gtk_tree_store_set( store, &iter, 0, _("with middle button"), -1 );
        gtk_tree_store_append( store, &iter, NULL );
        gtk_tree_store_set( store, &iter, 0, _("without middle button"), -1 );

        GtkTreeModel* mbModel = GTK_TREE_MODEL( store );
        opt = gtk_combo_box_new_with_model( mbModel );

        g_signal_connect(opt, "changed", G_CALLBACK(cb_mouse_switch), NULL);

	gtk_widget_show (opt);
	gtk_box_pack_start (GTK_BOX (hboxMouse), opt, FALSE, FALSE, 0);

	GtkCellRenderer* renderer = gtk_cell_renderer_text_new ();
	gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (opt), renderer, TRUE);
	gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (opt), renderer, "text", 0, NULL);
	gtk_cell_layout_set_cell_data_func (GTK_CELL_LAYOUT (opt), renderer, NULL, NULL, NULL);

	GtkTreePath* path = gtk_tree_path_new_from_indices (withMiddleButton ? 0 : 1, -1);
	gtk_tree_model_get_iter (mbModel, &iter, path);
	gtk_tree_path_free (path);
	gtk_combo_box_set_active_iter (GTK_COMBO_BOX (opt), &iter);
#endif

#ifdef USE_DOCKLET
	m_ShowTrayIcon = gtk_check_button_new_with_mnemonic (_("Show System Tray Icon (Docklet)"));
	gtk_widget_show (m_ShowTrayIcon);
	gtk_box_pack_start (GTK_BOX (m_Widget), m_ShowTrayIcon, FALSE, FALSE, 0);
#endif

	m_AAFont = gtk_check_button_new_with_mnemonic (_("Use Anti-Aliasing Fonts (Take effect after restart)"));
	gtk_widget_show (m_AAFont);
	gtk_box_pack_start (GTK_BOX (m_Widget), m_AAFont, FALSE, FALSE, 0);

	hbox20 = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox20);
	gtk_box_pack_start (GTK_BOX (m_Widget), hbox20, FALSE, FALSE, 0);

	m_PopupNotifier = gtk_check_button_new_with_mnemonic (_("Display popup notifier for "));
	gtk_widget_show (m_PopupNotifier);
	gtk_box_pack_start (GTK_BOX (hbox20), m_PopupNotifier, FALSE, FALSE, 0);

	m_PopupTimeout_adj = gtk_adjustment_new (0, 0, 100, 1, 0, 0);
	m_PopupTimeout = gtk_spin_button_new (GTK_ADJUSTMENT (m_PopupTimeout_adj), 1, 0);
	gtk_widget_show (m_PopupTimeout);
	gtk_box_pack_start (GTK_BOX (hbox20), m_PopupTimeout, FALSE, TRUE, 0);

	label29 = gtk_label_new (_("seconds"));
	gtk_widget_show (label29);
	gtk_box_pack_start (GTK_BOX (hbox20), label29, FALSE, FALSE, 2);

	m_MidClickAsClose = gtk_check_button_new_with_mnemonic (_("Middle mouse click as tab close (similar to Firefox)"));
	gtk_widget_show (m_MidClickAsClose);
	gtk_box_pack_start (GTK_BOX (m_Widget), m_MidClickAsClose, FALSE, FALSE, 0);

  hbox18 = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(m_Widget), hbox18, TRUE, TRUE, 0);

  gtk_box_pack_start(GTK_BOX(hbox18), gtk_label_new(_("Opacity: ")), FALSE, TRUE, 0);

  m_Opacity_adj = gtk_adjustment_new(0, 0, 100, 1, 0, 0);
  m_Opacity = gtk_hscale_new(GTK_ADJUSTMENT(m_Opacity_adj));
  gtk_box_pack_start(GTK_BOX(hbox18), m_Opacity, TRUE, TRUE, 0);
  gtk_widget_show_all(hbox18);

	hbox19 = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox19);
	gtk_box_pack_start (GTK_BOX (m_Widget), hbox19, FALSE, FALSE, 0);

	label27 = gtk_label_new (_("Web Browser: "));
	gtk_widget_show (label27);
	gtk_box_pack_start (GTK_BOX (hbox19), label27, FALSE, FALSE, 0);

	m_WebBrowser = gtk_entry_new ();
	gtk_widget_show (m_WebBrowser);
	gtk_box_pack_start (GTK_BOX (hbox19), m_WebBrowser, TRUE, TRUE, 0);

	hbox21 = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox21);
	gtk_box_pack_start (GTK_BOX (m_Widget), hbox21, FALSE, FALSE, 0);
	label30 = gtk_label_new (_("Mail Client: "));
	gtk_widget_show (label30);
	gtk_box_pack_start (GTK_BOX (hbox21), label30, FALSE, FALSE, 0);

	m_MailClient = gtk_entry_new ();
	gtk_widget_show (m_MailClient);
 	gtk_box_pack_start (GTK_BOX (hbox21), m_MailClient, TRUE, TRUE, 0);

	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(m_QueryOnCloseCon), AppConfig.QueryOnCloseCon);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(m_QueryOnExit), AppConfig.QueryOnExit);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(m_CancelSelAfterCopy), AppConfig.CancelSelAfterCopy);

  gtk_adjustment_set_value(GTK_ADJUSTMENT(m_Opacity_adj), AppConfig.Opacity * 1.);
#ifdef USE_MOUSE
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(m_MouseSupport), AppConfig.MouseSupport);
#endif
#ifdef USE_DOCKLET
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(m_ShowTrayIcon), AppConfig.ShowTrayIcon);
#endif
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(m_AAFont), AppConfig.AntiAliasFont);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(m_PopupNotifier), AppConfig.PopupNotifier);

	gtk_spin_button_set_value(GTK_SPIN_BUTTON(m_PopupTimeout), AppConfig.PopupTimeout);

	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(m_MidClickAsClose),
	                             AppConfig.MidClickAsClose);

	gtk_entry_set_text(GTK_ENTRY(m_WebBrowser), AppConfig.WebBrowser.c_str());
	gtk_entry_set_text(GTK_ENTRY(m_MailClient), AppConfig.MailClient.c_str());
}


void CGeneralPrefPage::OnOK()
{
	AppConfig.QueryOnCloseCon = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(m_QueryOnCloseCon));
	AppConfig.QueryOnExit = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(m_QueryOnExit));
	AppConfig.CancelSelAfterCopy = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(m_CancelSelAfterCopy));
  AppConfig.Opacity = (int) gtk_adjustment_get_value(GTK_ADJUSTMENT(m_Opacity_adj));
#ifdef USE_MOUSE
	AppConfig.MouseSupport = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(m_MouseSupport));
#endif
#ifdef USE_DOCKLET
	AppConfig.ShowTrayIcon = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(m_ShowTrayIcon));
#endif
	AppConfig.AntiAliasFont = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(m_AAFont));
	AppConfig.PopupNotifier =  gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON(m_PopupNotifier));
	AppConfig.PopupTimeout = (int)gtk_spin_button_get_value( GTK_SPIN_BUTTON(m_PopupTimeout));
	AppConfig.MidClickAsClose = gtk_toggle_button_get_active(
			GTK_TOGGLE_BUTTON(m_MidClickAsClose));
	AppConfig.WebBrowser = gtk_entry_get_text(GTK_ENTRY(m_WebBrowser));
	AppConfig.MailClient = gtk_entry_get_text(GTK_ENTRY(m_MailClient));
}
