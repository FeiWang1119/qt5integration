#ifndef UTILITY_H
#define UTILITY_H

#include <QImage>

#include <xcb/xproto.h>

#include "global.h"

QT_BEGIN_NAMESPACE
class QXcbWindow;
QT_END_NAMESPACE

typedef uint32_t xcb_atom_t;

DPP_BEGIN_NAMESPACE

class Utility
{
public:
    enum CornerEdge {
        TopLeftCorner = 0,
        TopEdge = 1,
        TopRightCorner = 2,
        RightEdge = 3,
        BottomRightCorner = 4,
        BottomEdge = 5,
        BottomLeftCorner = 6,
        LeftEdge = 7
    };

    static QImage dropShadow(const QPixmap &px, qreal radius, const QColor &color);
    static QImage borderImage(const QPixmap &px, const QMargins &borders, const QSize &size,
                              QImage::Format format = QImage::Format_ARGB32_Premultiplied);

    static QList<QRect> sudokuByRect(const QRect &rect, QMargins borders);

    static xcb_atom_t internAtom(const char *name);
    static void startWindowSystemMove(quint32 WId);
    static void cancelWindowMoveResize(quint32 WId);
    static void setFrameExtents(quint32 WId, const QMargins &margins);
    static void setRectangles(quint32 WId, const QRegion &region, bool onlyInput = true);
    static void setRectangles(quint32 WId, const QVector<xcb_rectangle_t> &rectangles, bool onlyInput = true);
    static void setShapePath(quint32 WId, const QPainterPath &path, bool onlyInput = true);
    static void startWindowSystemResize(quint32 WId, CornerEdge cornerEdge, const QPoint &globalPos = QPoint());
    static bool setWindowCursor(quint32 WId, CornerEdge ce);

    static QRegion regionAddMargins(const QRegion &region, const QMargins &margins, const QPoint &offset = QPoint(0, 0));

    static QByteArray windowProperty(quint32 WId, xcb_atom_t propAtom, xcb_atom_t typeAtom, quint32 len);
    static void setWindowProperty(quint32 WId, xcb_atom_t propAtom, xcb_atom_t typeAtom, const void *data, quint32 len, uint8_t format = 8);

    struct BlurArea {
        qint32 x;
        qint32 y;
        qint32 width;
        qint32 height;
        qint32 xRadius;
        qint32 yRaduis;
    };

    // by Deepin Window Manager
    static bool hasBlurWindow();
    static bool hasComposite();
    static bool blurWindowBackground(const quint32 WId, const QVector<BlurArea> &areas);
    static bool blurWindowBackgroundByPaths(const quint32 WId, const QList<QPainterPath> &paths);
    static bool blurWindowBackgroundByImage(const quint32 WId, const QRect &blurRect, const QImage &maskImage);

    static quint32 getWorkspaceForWindow(quint32 WId);
    static QVector<quint32> getWindows();
    static QVector<quint32> getCurrentWorkspaceWindows();

private:
    static void sendMoveResizeMessage(quint32 WId, uint32_t action, QPoint globalPos = QPoint(), Qt::MouseButton qbutton = Qt::LeftButton);
    static QVector<xcb_rectangle_t> qregion2XcbRectangles(const QRegion &region);
};

DPP_END_NAMESPACE

QT_BEGIN_NAMESPACE
DPP_USE_NAMESPACE
QDebug operator<<(QDebug deg, const Utility::BlurArea &area);
QT_END_NAMESPACE

#endif // UTILITY_H
