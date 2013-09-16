/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "UILabel.h"

NS_CC_EXT_BEGIN

UILabel::UILabel():
m_bTouchScaleChangeEnabled(false),
m_fNormalScaleValue(1.0f),
m_sFontName("Thonburi"),
m_nFontSize(10),
m_fOnSelectedScaleOffset(0.5),
m_pLabelRenderer(NULL)
{
}

UILabel::~UILabel()
{
    
}

UILabel* UILabel::create()
{
    UILabel* widget = new UILabel();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UILabel::init()
{
    if (UIWidget::init())
    {
        return true;
    }
    return false;
}

void UILabel::initRenderer()
{
    UIWidget::initRenderer();
    m_pLabelRenderer = CCLabelTTF::create();
    _renderer->addChild(m_pLabelRenderer);
}

void UILabel::setText(const char* text)
{
	if (!text)
	{
		return;
	}
    std::string strText(text);
    m_pLabelRenderer->setString(strText.c_str());
    labelScaleChangedWithSize();
}

const char* UILabel::getStringValue()
{
    return m_pLabelRenderer->getString();
}

int UILabel::getStringLength()
{
    const char* str = m_pLabelRenderer->getString();
    return strlen(str);
}

void UILabel::setFontSize(int size)
{
    m_pLabelRenderer->setFontSize(size);
    labelScaleChangedWithSize();
}

void UILabel::setFontName(const char* name)
{
    m_pLabelRenderer->setFontName(name);
    labelScaleChangedWithSize();
}

void UILabel::setTextAreaSize(const Size &size)
{
    m_pLabelRenderer->setDimensions(size);
    labelScaleChangedWithSize();
}

void UILabel::setTextHorizontalAlignment(TextHAlignment alignment)
{
    m_pLabelRenderer->setHorizontalAlignment(alignment);
    labelScaleChangedWithSize();
}

void UILabel::setTextVerticalAlignment(TextVAlignment alignment)
{
    m_pLabelRenderer->setVerticalAlignment(alignment);
    labelScaleChangedWithSize();
}

void UILabel::setTouchScaleChangeEnabled(bool enable)
{
    m_bTouchScaleChangeEnabled = enable;
    m_fNormalScaleValue = getScale();
}

bool UILabel::isTouchScaleChangeEnabled()
{
    return m_bTouchScaleChangeEnabled;
}

void UILabel::onPressStateChangedToNormal()
{
    if (!m_bTouchScaleChangeEnabled)
    {
        return;
    }
    clickScale(m_fNormalScaleValue);
}

void UILabel::onPressStateChangedToPressed()
{
    if (!m_bTouchScaleChangeEnabled)
    {
        return;
    }
    clickScale(m_fNormalScaleValue + m_fOnSelectedScaleOffset);
}

void UILabel::onPressStateChangedToDisabled()
{
    
}

void UILabel::clickScale(float scale)
{
    _renderer->setScale(scale);
}

void UILabel::setFlipX(bool flipX)
{
    m_pLabelRenderer->setFlippedX(flipX);
}

void UILabel::setFlipY(bool flipY)
{
    m_pLabelRenderer->setFlippedY(flipY);
}

bool UILabel::isFlipX()
{
    return m_pLabelRenderer->isFlippedX();
}

bool UILabel::isFlipY()
{
    return m_pLabelRenderer->isFlippedY();
}

void UILabel::setAnchorPoint(const Point &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pLabelRenderer->setAnchorPoint(pt);
}

void UILabel::onSizeChanged()
{
    labelScaleChangedWithSize();
}

const Size& UILabel::getContentSize() const
{
    return m_pLabelRenderer->getContentSize();
}

Node* UILabel::getVirtualRenderer()
{
    return m_pLabelRenderer;
}

void UILabel::labelScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        m_pLabelRenderer->setScale(1.0f);
        _size = m_pLabelRenderer->getContentSize();
    }
    else
    {
        Size textureSize = m_pLabelRenderer->getContentSize();
        if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
        {
            m_pLabelRenderer->setScale(1.0f);
            return;
        }
        float scaleX = _size.width / textureSize.width;
        float scaleY = _size.height / textureSize.height;
        m_pLabelRenderer->setScaleX(scaleX);
        m_pLabelRenderer->setScaleY(scaleY);
    }
    
}

NS_CC_EXT_END