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

# include <Siv3D/Math.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Polygon.hpp>
# include <Siv3D/SimpleGUI.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/DrawableText.hpp>
# include <Siv3D/UI1/UIWindow.hpp>
# include "UICanvasDetail.hpp"

namespace s3d
{
	namespace UI1
	{
		UIWindow::Style UIWindow::Style::Default()
		{
			return UIWindow::Style{};
		}

		UIWindow::UIWindow(const UIContainerNameView name, const StringView title, const RectF& rect, const Style& style)
			: UIContainer{ name }
			, m_style{ style }
			, m_rect{ rect }
		{
			setTitle(title);
		}

		StringView UIWindow::type() const noexcept
		{
			return U"UIWindow";
		}

		SizeF UIWindow::getSize() const noexcept
		{
			return m_rect.size;
		}

		RectF UIWindow::getBounds() const noexcept
		{
			return m_rect;
		}

		bool UIWindow::onUpdate(const bool cursorCapturable)
		{
			if (auto pCanvas = m_pCanvas.lock())
			{
				m_active = (pCanvas->findTopmostContainer() == this);
			}
			else
			{
				m_active = true;
			}

			if (m_dragging)
			{
				setPos(getBounds().pos + Cursor::DeltaF());
			}

			return onUpdateHelper(cursorCapturable, getShape().mouseOver(), m_style.titleBarHeight, m_style.padding, [this](SizeF size) { setSize(size + SizeF{ 0, m_style.titleBarHeight }); });
		}

		void UIWindow::onDraw() const
		{
			drawBackground();

			onDrawHelper(m_style.titleBarHeight, m_style.padding);
		}

		void UIWindow::onDrawOverlay() const
		{
			onDrawOverlayHelper(m_style.titleBarHeight, m_style.padding);

			// 無効状態の場合、全体にオーバーレイを描画する
			if (not isEnabled())
			{
				if (m_style.disabledOverlayColor)
				{
					getShape().draw(*m_style.disabledOverlayColor);
				}
			}
		}

		void UIWindow::onDrawDebug() const
		{
			drawDebugBackground();

			onDrawDebugHelper(m_style.titleBarHeight, m_style.padding);
		}

		void UIWindow::setPos(const Vec2& pos) noexcept
		{
			m_rect.pos = pos;
		}

		void UIWindow::setSize(const SizeF& size) noexcept
		{
			m_rect.size = size;
		}

		void UIWindow::setTitle(const StringView title)
		{
			m_title = String{ title }.removed(U'\n');
		}

		const String& UIWindow::getTitle() const noexcept
		{
			return m_title;
		}

		std::shared_ptr<UIWindow> UIWindow::Create(const UIContainerNameView name, const StringView title, const RectF& rect, const Style& style)
		{
			return std::make_shared<UIWindow>(name, title, rect, style);
		}

		void UIWindow::onPressed()
		{
			if (getTitleBarRect().mouseOver())
			{
				m_dragging = true;
			}
		}

		void UIWindow::onReleased()
		{
			m_dragging = false;
		}

		RoundRect UIWindow::getShape() const noexcept
		{
			return{ m_rect, m_style.borderRadius };
		}

		RectF UIWindow::getTitleBarRect() const noexcept
		{
			return{ m_rect.pos, m_rect.w, m_style.titleBarHeight };
		}

		void UIWindow::drawBackground() const
		{
			const RoundRect shape = getShape();

			if (m_style.boxShadow)
			{
				// [Siv3D ToDo] より多くのケースで fill を false にする
				const bool fill = ((m_style.boxShadow->blur * 0.5 + m_style.boxShadow->spread) < (Math::Abs(m_style.boxShadow->offset).maxComponent()));
				shape.drawShadow(m_style.boxShadow->offset, m_style.boxShadow->blur, m_style.boxShadow->spread, m_style.boxShadow->color, fill);
			}

			if (m_style.backgroundColor)
			{
				shape.draw(*m_style.backgroundColor);
			}

			const RectF titleBarRect = getTitleBarRect();
			titleBarRect.rounded(m_style.borderRadius, m_style.borderRadius, 0, 0).draw(m_active ? m_style.titleBarActiveColor : m_style.titleBarInactiveColor);
			
			{
				constexpr double TitleMargin = 10.0;
				const SizeF titleSize = SimpleGUI::GetFont()(18, m_title).region().size;

				if (titleBarRect.w < (titleSize.x + (TitleMargin * 2)))
				{
					SimpleGUI::GetFont()(m_title).draw(18, titleBarRect.movedBy(TitleMargin, ((titleBarRect.h - titleSize.y) / 2)), ColorF{ 0.11 });
				}
				else
				{
					SimpleGUI::GetFont()(m_title).drawAt(18, titleBarRect.center().movedBy(0, -1), ColorF{ 0.11 });
				}
			}

			if (0.0 < m_style.borderThickness)
			{
				if (isEnabled())
				{
					if (m_active && m_style.activeBorderColor)
					{
						shape.drawFrame(0.0, m_style.borderThickness, *m_style.activeBorderColor);
					}
					else if ((not m_active) && m_style.inactiveBorderColor)
					{
						shape.drawFrame(0.0, m_style.borderThickness, *m_style.inactiveBorderColor);
					}
				}
				else if ((not isEnabled()) && m_style.disabledBorderColor)
				{
					shape.drawFrame(0.0, m_style.borderThickness, *m_style.disabledBorderColor);
				}
			}
		}

		void UIWindow::drawDebugBackground() const
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
