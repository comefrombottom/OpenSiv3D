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
		ColorRect::ColorRect(const SizeF& size, const ColorF& color, const Margin& margin)
			: m_size{ size }
			, m_color{ color }
			, m_margin{ margin } {}

		std::shared_ptr<ColorRect> ColorRect::Create(const SizeF& size, const ColorF& color, const Margin& margin)
		{
			return std::make_shared<ColorRect>(size, color, margin);
		}

		SizeF ColorRect::getSize() const noexcept
		{
			return m_size;
		}

		void ColorRect::setSize(const SizeF& size) noexcept
		{
			m_size = size;
		}

		const ColorF& ColorRect::getColor() const noexcept
		{
			return m_color;
		}

		void ColorRect::setColor(const ColorF& color) noexcept
		{
			m_color = color;
		}

		Margin ColorRect::getMargin() const noexcept
		{
			return m_margin;
		}

		void ColorRect::onDraw() const
		{
			RectF{ m_size }.draw(m_color);
		}
	}
}
