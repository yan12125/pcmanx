#ifndef PCMANX_INTERNAL_UTIL
#define PCMANX_INTERNAL_UTIL

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#if __WORDSIZE == 64
typedef unsigned long int word_t;
#else
typedef unsigned int word_t;
#endif

#ifdef USE_DEBUG
#define DEBUG(format...) g_log(G_LOG_DOMAIN, G_LOG_LEVEL_DEBUG, format)
#define INFO(format...) g_log(G_LOG_DOMAIN, G_LOG_LEVEL_INFO, format)
#else
#define DEBUG(format...)
#define INFO(format...)
#endif

#if (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3)) && defined(__ELF__)
#  define X_EXPORT __attribute__((visibility("default")))
#else
#  define X_EXPORT
#endif

#include <gtk/gtk.h>
#if GTK_CHECK_VERSION(3, 0, 0)

typedef GtkAdjustment GTK_ADJUSTMENT_TYPE;

#else

inline gboolean
gtk_widget_is_visible (GtkWidget *widget)
{
    return GTK_WIDGET_VISIBLE(widget);
}

typedef GtkObject GTK_ADJUSTMENT_TYPE;

#endif

#endif
