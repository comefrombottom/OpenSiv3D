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

# include <Siv3D/UI1/UIPanel.hpp>
namespace s3d
{
	namespace UI1
	{
		UIPanel::Style UIPanel::Style::Default()
		{
			return UIPanel::Style{};
		}

		UIPanel::UIPanel(const UIContainerNameView name, const RectF& rect, const Style& style)
			: UIContainer{ name }
			, m_style{ style }
			, m_rect{ rect } {}

		StringView UIPanel::type() const noexcept
		{
			return U"UIPanel";
		}

		SizeF UIPanel::getSize() const noexcept
		{
			return m_rect.size;
		}

		RectF UIPanel::getBounds() const noexcept
		{
			return m_rect;
		}

		bool UIPanel::onUpdate(bool cursorCapturable)
		{
			return(false);
		}

		void UIPanel::onDraw() const
		{
			drawBackground();

			// 子要素を描画する
			{

			}
		}

		void UIPanel::onDrawOverlay() const
		{
			// 子要素を描画する
			{

			}
		}

		void UIPanel::onDrawDebug() const
		{
			drawDebugBackground();
		}

		void UIPanel::setPos(const Vec2& pos) noexcept
		{
			m_rect.pos = pos;
		}

		void UIPanel::setSize(const SizeF& size) noexcept
		{
			m_rect.size = size;
		}

		std::shared_ptr<UIPanel> UIPanel::Create(const UIContainerNameView name, const RectF& rect, const Style& style)
		{
			return std::make_shared<UIPanel>(name, rect, style);
		}

		RoundRect UIPanel::getShape() const noexcept
		{
			return{ m_rect, m_style.borderRadius };
		}

		void UIPanel::drawBackground() const
		{
			const RoundRect shape = getShape();

			if (m_style.boxShadow)
			{
				shape.drawShadow(m_style.boxShadow->offset, m_style.boxShadow->blur, m_style.boxShadow->spread, m_style.boxShadow->color);
			}

			if (m_style.backgroundColor)
			{
				shape.draw(*m_style.backgroundColor);
			}

			if (0.0 < m_style.borderThickness)
			{
				if (isEnabled() && m_style.borderColor)
				{
					shape.drawFrame(0.0, m_style.borderThickness, *m_style.borderColor);
				}
				else if ((not isEnabled()) && m_style.disabledBorderColor)
				{
					shape.drawFrame(0.0, m_style.borderThickness, *m_style.disabledBorderColor);
				}
			}
		}

		void UIPanel::drawDebugBackground() const
		{
			const RectF rect = getBounds();

			rect.drawFrame(1, 0, Palette::Red);

			if (not isEnabled())
			{
				Line{ rect.tl(), rect.br() }.draw(1, Palette::Red);
				Line{ rect.bl(), rect.tr() }.draw(1, Palette::Red);
			}

			if (isHovered())
			{
				rect.stretched(-1).drawFrame(5, 0, Palette::Orange);
			}

			if (hasMouseCapture())
			{
				Circle{ rect.tl(), 10 }.drawFrame(3, 0, Palette::Red);
				Circle{ rect.tr(), 10 }.drawFrame(3, 0, Palette::Red);
				Circle{ rect.br(), 10 }.drawFrame(3, 0, Palette::Red);
				Circle{ rect.bl(), 10 }.drawFrame(3, 0, Palette::Red);
			}
		}
	}
}
