#include "stdafx.h"
#include "FrameBuffer.h"


CFrameBuffer::CFrameBuffer(unsigned width, unsigned height)
    :m_pixels(width * height)
    , m_width(width)
    , m_height(height)
{
}

CFrameBuffer::~CFrameBuffer()
{
}

/* Public methods */

void CFrameBuffer::Clear(boost::uint32_t color)
{
    std::fill(m_pixels.begin(), m_pixels.end(), color);
}

void CFrameBuffer::SetPixel(unsigned x, unsigned y, boost::uint32_t color) throw()
{
    assert(x < m_width);
    assert(y < m_height);
    m_pixels[size_t(y * m_width + x)] = color;
}

boost::uint32_t CFrameBuffer::GetPixel(unsigned x, unsigned y)const throw()
{
    assert(x < m_width);
    assert(y < m_height);
    return m_pixels[size_t(y * m_width + x)];
}

unsigned CFrameBuffer::GetWidth()const throw()
{
    return m_width;
}

unsigned CFrameBuffer::GetHeight()const throw()
{
    return m_height;
}