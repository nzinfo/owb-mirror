/*
    Copyright (C) 2004, 2005, 2006 Nikolas Zimmermann <wildfox@kde.org>
                  2004, 2005, 2006 Rob Buis <buis@kde.org>

    This file is part of the KDE project

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
*/

#include "config.h"

#ifdef SVG_SUPPORT
#include "SVGEllipseElement.h"

#include "FloatPoint.h"
#include "SVGLength.h"
#include "SVGNames.h"

namespace WebCore {

SVGEllipseElement::SVGEllipseElement(const QualifiedName& tagName, Document* doc)
    : SVGStyledTransformableElement(tagName, doc)
    , SVGTests()
    , SVGLangSpace()
    , SVGExternalResourcesRequired()
    , m_cx(this, LengthModeWidth)
    , m_cy(this, LengthModeHeight)
    , m_rx(this, LengthModeWidth)
    , m_ry(this, LengthModeHeight)
{
}    

SVGEllipseElement::~SVGEllipseElement()
{
}

ANIMATED_PROPERTY_DEFINITIONS(SVGEllipseElement, SVGLength, Length, length, Cx, cx, SVGNames::cxAttr.localName(), m_cx)
ANIMATED_PROPERTY_DEFINITIONS(SVGEllipseElement, SVGLength, Length, length, Cy, cy, SVGNames::cyAttr.localName(), m_cy)
ANIMATED_PROPERTY_DEFINITIONS(SVGEllipseElement, SVGLength, Length, length, Rx, rx, SVGNames::rxAttr.localName(), m_rx)
ANIMATED_PROPERTY_DEFINITIONS(SVGEllipseElement, SVGLength, Length, length, Ry, ry, SVGNames::ryAttr.localName(), m_ry)

void SVGEllipseElement::parseMappedAttribute(MappedAttribute* attr)
{
    const AtomicString& value = attr->value();
    if (attr->name() == SVGNames::cxAttr)
        setCxBaseValue(SVGLength(this, LengthModeWidth, value));
    else if (attr->name() == SVGNames::cyAttr)
        setCyBaseValue(SVGLength(this, LengthModeHeight, value));
    else if (attr->name() == SVGNames::rxAttr) {
        setRxBaseValue(SVGLength(this, LengthModeWidth, value));
        if (rx().value() < 0.0)
            document()->accessSVGExtensions()->reportError("A negative value for ellipse <rx> is not allowed");
    } else if (attr->name() == SVGNames::ryAttr) {
        setRyBaseValue(SVGLength(this, LengthModeHeight, value));
        if (ry().value() < 0.0)
            document()->accessSVGExtensions()->reportError("A negative value for ellipse <ry> is not allowed");
    } else {
        if (SVGTests::parseMappedAttribute(attr))
            return;
        if (SVGLangSpace::parseMappedAttribute(attr))
            return;
        if (SVGExternalResourcesRequired::parseMappedAttribute(attr))
            return;
        SVGStyledTransformableElement::parseMappedAttribute(attr);
    }
}

void SVGEllipseElement::notifyAttributeChange() const
{
    if (!ownerDocument()->parsing())
        rebuildRenderer();

    SVGStyledElement::notifyAttributeChange();
}

Path SVGEllipseElement::toPathData() const
{
    return Path::createEllipse(FloatPoint(cx().value(), cy().value()),
                               rx().value(), ry().value());
}
 
bool SVGEllipseElement::hasRelativeValues() const
{
    return (cx().isRelative() || cy().isRelative() ||
            rx().isRelative() || ry().isRelative());
}

}

#endif // SVG_SUPPORT

// vim:ts=4:noet
