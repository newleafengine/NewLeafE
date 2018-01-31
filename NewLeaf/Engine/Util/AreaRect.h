#pragma once
#include <glm\vec2.hpp>

namespace nle
{
	enum ResizeFlag
	{
		RESIZE_X = 1 << 0,
		RESIZE_Y = 1 << 1,

		RESIZE_ALL = RESIZE_X | RESIZE_Y
	};

	class AreaRect
	{
		public:
			AreaRect();
			AreaRect(int left, int top, int width, int height);
			~AreaRect();

			// Expects a new pixel size to be resized to
			AreaRect Resize(int factor, ResizeFlag flag = RESIZE_ALL);
			// Exects a percentage to resize the object, > 1 = upscale, < 1 = downscale
			AreaRect Resize(float factor, ResizeFlag flag = RESIZE_ALL);

			inline bool Contains(const glm::ivec2 point)
			{
				return ((point.x >= m_Left && point.x <= m_Right) && (point.y >= m_Top && point.y <= m_Bottom));
			};
	private:
			int m_Left, m_Top, m_Right, m_Bottom;
			int m_Width, m_Height;
	};
}