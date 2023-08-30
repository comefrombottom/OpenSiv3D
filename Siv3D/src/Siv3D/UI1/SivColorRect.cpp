//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/UI1/ColorRect.hpp>
# include <Siv3D/2DShapes.hpp>

namespace s3d
{
	namespace UI1
	{
		ColorRect::ColorRect(const SizeF& size, const ColorF& color)
			: m_size{ size }
			, m_color{ color } {}

		std::shared_ptr<ColorRect> ColorRect::Create(const SizeF& size, const ColorF& color)
		{
			return std::make_shared<ColorRect>(size, color);
		}

		SizeF ColorRect::getSize() const noexcept
		{
			return m_size;
		}

		void ColorRect::onDraw() const
		{
			RectF{ m_size }.draw(m_color);
		}
	}
}
