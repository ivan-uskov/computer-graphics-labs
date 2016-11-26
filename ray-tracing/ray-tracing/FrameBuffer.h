#pragma once
#include <vector>
#include <assert.h>
#include <boost/cstdint.hpp>

class CFrameBuffer
{
public:
    CFrameBuffer(unsigned width, unsigned height);
    ~CFrameBuffer();

    // ������ ������ � ��������
    unsigned GetWidth()const throw();

    // ������ ������ � ��������
    unsigned GetHeight()const throw();

    // ������� ����������� ������ �������� ������
    void Clear(boost::uint32_t color = 0);

    // ��������� ������ ������ �����. ������ �������� (��� ������)
    const boost::uint32_t * GetPixels(unsigned row = 0)const throw()
    {
        assert(row < m_height);
        return &m_pixels[size_t(row * m_width)];
    }

    // ��������� ������ ������ �����. ������ �������� (��� ������)
    boost::uint32_t * GetPixels(unsigned row = 0)throw()
    {
        assert(row < m_height);
        return &m_pixels[size_t(row * m_width)];
    }

    // ��������� ����� ������� � ��������� ������������
    boost::uint32_t GetPixel(unsigned x, unsigned y)const throw();

    // ��������� ����� ������� � ��������� ������������
    void SetPixel(unsigned x, unsigned y, boost::uint32_t color) throw();

private:
    std::vector<boost::uint32_t> m_pixels;
    unsigned m_width;
    unsigned m_height;
};
