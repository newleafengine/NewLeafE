#include "AreaRect.h"

nle::AreaRect::AreaRect()
{
}

nle::AreaRect::AreaRect(int left, int top, int width, int height)
{
	m_Left = left;
	m_Top = top;
	m_Width = width;
	m_Height = height;
	m_Right = m_Left + m_Width;
	m_Bottom = m_Top + m_Height;
}

nle::AreaRect::~AreaRect()
{
}

nle::AreaRect nle::AreaRect::Resize(int factor, ResizeFlag flag)
{
	AreaRect r;
	r = *this;
	if (flag & RESIZE_X)
	{
		r.m_Width = factor;
		r.m_Right = r.m_Left + r.m_Width;
	}
	if (flag & RESIZE_Y)
	{
		r.m_Height = factor;
		r.m_Bottom = r.m_Top + r.m_Height;
	}
	return r;
}

nle::AreaRect nle::AreaRect::Resize(float factor, ResizeFlag flag)
{

	AreaRect r;
	r = *this;
	if (factor <= 1)
	{
		if (flag & RESIZE_X)
		{
			r.m_Width *= 1.0 - factor;
			r.m_Right = r.m_Left + r.m_Width;
		}
		if (flag & RESIZE_Y)
		{
			r.m_Height *= 1.0 - factor;
			r.m_Bottom = r.m_Top + r.m_Height;
		}
	}
	else
	{
		if (flag & RESIZE_X)
		{
			r.m_Width *= factor;
			r.m_Right = r.m_Left + r.m_Width;
		}
		if (flag & RESIZE_Y)
		{
			r.m_Height *= factor;
			r.m_Bottom = r.m_Top + r.m_Height;
		}
	}
	return r;
}