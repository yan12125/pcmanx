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

#ifndef TERMVIEW_H
#define TERMVIEW_H

#ifdef __GNUG__
  #pragma interface "termview.h"
#endif

#include "pcmanx_utils.h"

#include "view.h"
#include "caret.h"

#include <string>

#include <X11/Xft/Xft.h>

using namespace std;

/**
@author PCMan
*/
class CTermData;
class CHyperLink;
class CFont;

// Modified from /usr/include/gtk-2.0/gdk/gdkdrawable.h
struct Trapezoid
{
  double y1, x11, x21, y2, x12, x22;
};

class X_EXPORT CTermView : public CView
{
friend class CTermData;
public:
    enum {FONT_START = 0, FONT_DEFAULT = 0, FONT_EN, FONT_END};

    CTermView();

    virtual bool PreKeyDown(GdkEventKey *evt);
    virtual bool OnKeyDown(GdkEventKey* evt);
    virtual void OnTextInput(const gchar* string);
    int DrawChar(int row, int col);
    void PointToLineCol(int *x, int *y, bool *left = NULL);

    GtkIMContext* m_IMContext;

    virtual void OnLButtonDown(GdkEventButton* evt);
    virtual void OnRButtonDown(GdkEventButton* evt);
    virtual void OnLButtonUp(GdkEventButton* evt);
    virtual void OnRButtonUp(GdkEventButton* evt);
    virtual void OnMouseMove(GdkEventMotion* evt);
    virtual void OnMouseScroll(GdkEventScroll* evt);
    virtual void OnHyperlinkClicked(string url);
    void OnBlinkTimer();
    virtual void OnMButtonDown(GdkEventButton* evt);
    void PasteFromClipboard(bool primary);
    virtual void DoPasteFromClipboard(string text, bool contain_ansi_color);
    virtual void CopyToClipboard(bool primary, bool with_color, bool trim);
    void SetFont( string name, int pt_size, bool compact, bool anti_alias, int font_type);
    void SetFontFamily(string name, int font_type);
    void SetFont(CFont* font, int font_type);
    void SetHyperLinkColor( GdkColor* clr ){	m_pHyperLinkColor = clr;	}
    CFont* GetFont(int font_type){	return m_Font[font_type];	}
    void SetHorizontalCenterAlign( bool is_hcenter );
    void SetVerticalCenterAlign( bool is_vcenter );
    void SetUAO( gint idx );
    void SetTermData(CTermData* data){	m_pTermData = data;	}

public:
    static int Opacity;

protected:
    void OnPaint(GdkEventExpose* evt);
    void OnSetFocus(GdkEventFocus* evt);
    void OnCreate();
    void OnSize(GdkEventConfigure* evt);
    void OnKillFocus(GdkEventFocus *evt);
	static void OnBeforeDestroy( GtkWidget* widget, CTermView* _this);
    void UpdateCaretPos();
    bool HyperLinkHitTest(int x, int y, int* start, int* end);
    void OnDestroy();
    void RecalcCharDimension();
    void GetCellSize( int &w, int &h );
    void ClearSelection();
    void ExtendSelection( int row, int col, bool left );
    bool DrawSpaceFillingChar(cairo_t *cr, const char* ch, int x, int y, GdkColor* clr);
    bool IsSpaceFillingChar( const char* ch, int len ) {	return bool( len >= 3 && *(guchar*)ch == 0xe2 );	}

private:
    void SetSource(cairo_t* cr, GdkColor* color, bool transparent = true);
    void Rectangle(cairo_t* cr, bool fill, int top, int left, int width, int height);
    void Line(cairo_t* cr, int x0, int y0, int x1, int y1);
    void Trapezoids(cairo_t *cr, Trapezoid *trapezoids, GdkColor *color);
    
protected:
	CTermData* m_pTermData;

    XftDraw* m_XftDraw;
    CFont* m_Font[FONT_END];

	int m_CharW;
	int m_CharH;
	int m_LeftMargin;
	int m_TopMargin;
	bool m_bHorizontalCenterAlign;
	bool m_bVerticalCenterAlign;
    gint m_UAO;

	CCaret m_Caret;
	CHyperLink* m_pHyperLink;

	bool m_ShowBlink;
	int m_CharPaddingX;
	int m_CharPaddingY;
    GdkColor* m_pColorTable;
	GdkColor* m_pHyperLinkColor;
    // GdkGC* m_GC;
    bool m_AutoFontSize;

    bool m_CancelSel;	// If selection is canceled in OnLButtonDown, this flag is set to true.

    static string m_s_ANSIColorStr;
    static string m_s_CharSet;

    int m_FontSize;
    string m_FontFamily;

    double m_Opacity;

    static GdkCursor* m_HandCursor;
    static GdkCursor* m_ExitCursor;
    static GdkCursor* m_BullsEyeCursor;
    static GdkCursor* m_PageDownCursor;
    static GdkCursor* m_PageUpCursor;
    static GdkCursor* m_EndCursor;
    static GdkCursor* m_HomeCursor;

    // Mouse Cursor State for Click Behaviour
    // Hand=-1, Normal=0, Exit=1, BullsEye=2, PageDown=3, PageUp=4, End=5, Home=6
    static int m_CursorState;
};

#endif
