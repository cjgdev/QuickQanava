/*
 Copyright (c) 2008-2017, Benoit AUTHEMAN All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the author or Destrat.io nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL AUTHOR BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

//-----------------------------------------------------------------------------
// This file is a part of the QuickQanava software library.
//
// \file    qanStyle.h
// \author  benoit@destrat.io
// \date    2015 06 05
//-----------------------------------------------------------------------------

#ifndef qanStyle_h
#define qanStyle_h

// Qt headers
#include <QColor>
#include <QFont>
#include <QSizeF>
#include <QVector>
#include <QQmlEngine>

namespace qan { // ::qan

/*! Models a set of properties affecting a graph primitive visual appearance.
 *
 *  Style instances should be created from StyleManager createStyle() or createStyleFrom() methods,
 *  and associed to nodes trought their setStyle() method. Changing a style property will
 *  automatically be reflected in styled nodes or edges appearance. While Style use standard QObject
 *  properties to store style settings, the QuickContainers ObjectModel interface could be use to edit
 *  style properties.
 *
 *  Main qan::Style properties are:
 * \li \b name: Style name as it will appears in style edition dialogs.
 *
 * \sa qan::NodeItem::setStyle()
 * \sa qan::EdgeItem::setStyle()
 */
class Style : public QObject
{
    Q_OBJECT
    /*! \name Style Object Management *///-------------------------------------
    //@{
public:
    /*! \brief Style constructor with style name initialisation.
     */
    explicit Style( QString name = "", QObject* parent = nullptr );
    virtual ~Style( ) { }
    Style( const Style& ) = delete;
    //@}
    //-------------------------------------------------------------------------

    /*! \name Style Management *///--------------------------------------------
    //@{
public:
    Q_PROPERTY( QString name READ getName WRITE setName NOTIFY nameChanged FINAL )
    inline  void        setName( QString name ) noexcept { if ( name != _name ) { _name = name; emit nameChanged( ); } }
    inline  QString     getName() noexcept { return _name; }
    inline  QString     getName() const noexcept { return _name; }
signals:
    void        nameChanged( );
private:
    QString     _name{ QStringLiteral("") };
    //@}
    //-------------------------------------------------------------------------
};

class NodeStyle : public qan::Style
{
    /*! \name NodeStyle Object Management *///---------------------------------
    //@{
    Q_OBJECT
public:
    /*! \brief Style constructor with style \c name and \c target initialisation.
     *
     * Style \c metaTarget is "qan::Node". NodeStyle objects are usually created
     * with qan:StyleManager::createNodeStyle() factory method.
     */
    explicit NodeStyle( QString name = "", QObject* parent = nullptr );
    virtual ~NodeStyle( ) { }
    NodeStyle( const NodeStyle& ) = delete;
    //@}
    //-------------------------------------------------------------------------

    /*! \name Node Style Properties *///---------------------------------------
    //@{
public:
    /*! \brief Node background rectangle border (corner) radius (default to 4.).
     *
     * \note \c backRadius is interpreted as background rectangle border radius when nodes items are
     * built using Qan.RectNodeTemplate and Qan.RectNodeBackground. When defining custom node
     * items, value can't be interpreted by the user with no limitations.
     */
    Q_PROPERTY( qreal backRadius READ getBackRadius WRITE setBackRadius NOTIFY backRadiusChanged FINAL )
    //! \copydoc backRadius
    void            setBackRadius( qreal backRadius ) noexcept;
    //! \copydoc backRadius
    inline qreal    getBackRadius() const noexcept { return _backRadius; }
protected:
    //! \copydoc backRadius
    qreal           _backRadius{4.};
signals:
    //! \copydoc backRadius
    void            backRadiusChanged();

public:
    /*! \brief Node item background opacity (default to 0.85, ie 85% opaque).
     *
     * \note \c backOpacity affect node item background, but not it's content or border shadow opacity. Changing
     * node opacity directly is more efficient, but also affect node content and shadows. Property works
     * when using Qan.RectNodeTemplate and Qan.RectGroupTemplate, it could be used in custom node items with no
     * limitations (Qan.RectNodeBackground could be used to add backOpacity support to custom node delegates).
     *
     */
    Q_PROPERTY( qreal backOpacity READ getBackOpacity WRITE setBackOpacity NOTIFY backOpacityChanged FINAL )
    //! \copydoc backOpacity
    void            setBackOpacity( qreal backOpacity ) noexcept;
    //! \copydoc backOpacity
    inline qreal    getBackOpacity() const noexcept { return _backOpacity; }
protected:
    //! \copydoc backOpacity
    qreal           _backOpacity{0.85};
signals:
    //! \copydoc backOpacity
    void            backOpacityChanged();

public:
    Q_PROPERTY( QColor backColor READ getBackColor WRITE setBackColor NOTIFY backColorChanged FINAL )
    void            setBackColor( const QColor& backColor ) noexcept;
    const QColor&   getBackColor() const noexcept { return _backColor; }
protected:
    QColor          _backColor{Qt::white};
signals:
    void            backColorChanged();

public:
    Q_PROPERTY( QColor borderColor READ getBorderColor WRITE setBorderColor NOTIFY borderColorChanged FINAL )
    void            setBorderColor( const QColor& borderColor ) noexcept;
    const QColor&   getBorderColor() const noexcept { return _borderColor; }
protected:
    QColor          _borderColor = QColor(Qt::black);
signals:
    void            borderColorChanged();

public:
    Q_PROPERTY( qreal borderWidth READ getBorderWidth WRITE setBorderWidth NOTIFY borderWidthChanged FINAL )
    void            setBorderWidth( qreal borderWidth ) noexcept;
    inline qreal    getBorderWidth() const noexcept { return _borderWidth; }
protected:
    qreal           _borderWidth = 1.0;
signals:
    void            borderWidthChanged();

public:
    Q_PROPERTY( bool hasShadow READ getHasShadow WRITE setHasShadow NOTIFY hasShadowChanged FINAL )
    void            setHasShadow( bool hasShadow ) noexcept;
    inline bool     getHasShadow() const noexcept { return _hasShadow; }
protected:
    bool            _hasShadow = true;
signals:
    void            hasShadowChanged();

public:
    Q_PROPERTY( QColor shadowColor READ getShadowColor WRITE setShadowColor NOTIFY shadowColorChanged FINAL )
    void            setShadowColor( QColor shadowColor ) noexcept;
    inline QColor   getShadowColor() const noexcept { return _shadowColor; }
protected:
    QColor          _shadowColor = QColor{ 0, 0, 0, 127 };
signals:
    void            shadowColorChanged();

public:
    Q_PROPERTY( qreal shadowRadius READ getShadowRadius WRITE setShadowRadius NOTIFY shadowRadiusChanged FINAL )
    void            setShadowRadius( qreal shadowRadius ) noexcept;
    inline qreal    getShadowRadius() const noexcept { return _shadowRadius; }
protected:
    qreal           _shadowRadius{3.};
signals:
    void            shadowRadiusChanged();

public:
    /*! \brief Node content text font \c pointSize, set to -1 to use system default (default to -1 ie system default size).
     */
    Q_PROPERTY( int fontPointSize READ getFontPointSize WRITE setFontPointSize NOTIFY fontPointSizeChanged FINAL )
    //! \copydoc fontPointSize
    void            setFontPointSize( int fontPointSize ) noexcept;
    //! \copydoc fontPointSize
    inline int      getFontPointSize() const noexcept { return _fontPointSize; }
protected:
    //! \copydoc fontPointSize
    int             _fontPointSize{-1};
signals:
    //! \copydoc fontPointSize
    void            fontPointSizeChanged();

public:
    /*! \brief Set to true to display node text with bold font (default to false).
     */
    Q_PROPERTY( bool fontBold READ getFontBold WRITE setFontBold NOTIFY fontBoldChanged FINAL )
    //! \copydoc fontBold
    void            setFontBold( bool fontBold ) noexcept;
    //! \copydoc fontBold
    inline bool     getFontBold() const noexcept { return _fontBold; }
protected:
    //! \copydoc fontBold
    bool            _fontBold{false};
signals:
    //! \copydoc fontBold
    void            fontBoldChanged();
    //@}
    //-------------------------------------------------------------------------
};

class EdgeStyle : public qan::Style
{
    Q_OBJECT
    /*! \name EdgeStyle Object Management *///---------------------------------
    //@{
public:
    /*! \brief Edge style constructor with style \c name and \c target initialisation.
     *
     */
    explicit EdgeStyle( QString name = "", QObject* parent = nullptr );
    virtual ~EdgeStyle( ) { }
    EdgeStyle( const EdgeStyle& ) = delete;
    //@}
    //-------------------------------------------------------------------------

    /*! \name Properties Management *///---------------------------------------
    //@{
signals:
    void            styleModified();

public:
    //! Define edge style: either straight (drawn with a line) or curved (drawn with a cubic path).
    enum class LineType : unsigned int {
        Straight    = 0,
        Curved      = 1
    };
    Q_ENUM(LineType)

public:
    //! Define edge line type: either plain line (Straight) or curved cubic path (Curved), default to Straight.
    Q_PROPERTY( LineType lineType READ getLineType WRITE setLineType NOTIFY lineTypeChanged FINAL )
    void            setLineType( LineType lineType ) noexcept;
    inline LineType getLineType() const noexcept { return _lineType; }
protected:
    LineType        _lineType{LineType::Straight};
signals:
    void            lineTypeChanged();

public:
    Q_PROPERTY( QColor lineColor READ getLineColor WRITE setLineColor NOTIFY lineColorChanged FINAL )
    void                    setLineColor( const QColor& lineColor ) noexcept;
    inline const QColor&    getLineColor() const noexcept { return _lineColor; }
protected:
    QColor                  _lineColor = QColor( 0, 0, 0, 255 );
signals:
    void                    lineColorChanged();

public:
    Q_PROPERTY( qreal lineWidth READ getLineWidth WRITE setLineWidth NOTIFY lineWidthChanged FINAL )
    void            setLineWidth( qreal lineWidth ) noexcept;
    inline qreal    getLineWidth() const noexcept { return _lineWidth; }
protected:
    qreal           _lineWidth = 2.0;
signals:
    void            lineWidthChanged();

public:
    Q_PROPERTY( qreal arrowSize READ getArrowSize WRITE setArrowSize NOTIFY arrowSizeChanged FINAL )
    void            setArrowSize( qreal arrowSize ) noexcept;
    inline qreal    getArrowSize() const noexcept { return _arrowSize; }
protected:
    qreal           _arrowSize = 4.0;
signals:
    void            arrowSizeChanged();

public:
    //! Draw edge with dashed line (default to false), when set to true \c dashPattern is active.
    Q_PROPERTY( bool dashed READ getDashed WRITE setDashed NOTIFY dashedChanged FINAL )
    //! \copydoc dashed
    void            setDashed( bool dashed ) noexcept;
    //! \copydoc dashed
    inline bool     getDashed() const noexcept { return _dashed; }
protected:
    //! \copydoc dashed
    bool            _dashed{false};
signals:
    //! \copydoc dashed
    void            dashedChanged();

public:
    //! See QtQuick.Shape ShapePath.dashPattern property documentation, default to [2,2] ie regular dash line, used when dashed property is set to true.
    Q_PROPERTY( QVector<qreal> dashPattern READ getDashPattern WRITE setDashPattern NOTIFY dashPatternChanged FINAL )
    //! \copydoc dashPattern
    void            setDashPattern( const QVector<qreal>& dashPattern ) noexcept;
    //! \copydoc dashPattern
    const QVector<qreal>&   getDashPattern() const noexcept;
protected:
    //! \copydoc dashPattern
    QVector<qreal>  _dashPattern{ 2, 2 };
signals:
    //! \copydoc dashPattern
    void            dashPatternChanged();
    //@}
    //-------------------------------------------------------------------------
};

} // ::qan

QML_DECLARE_TYPE( qan::Style )
QML_DECLARE_TYPE( qan::NodeStyle )
QML_DECLARE_TYPE( qan::EdgeStyle )

#endif // qanStyle_h

