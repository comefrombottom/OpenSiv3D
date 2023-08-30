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

# include <Siv3D/Cursor.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/UI1/UIElement.hpp>
# include <Siv3D/UI1/UIContainer.hpp>

namespace s3d
{
	namespace UI1
	{
		UIElement::~UIElement()
		{
			if (m_hasMouseCapture)
			{
				Cursor::SetCapture(false);
			}
		}

		Margin UIElement::getMargin() const noexcept
		{
			return Margin::Zero();
		}

		bool UIElement::update(const bool cursorCapturable)
		{
			return onUpdate(cursorCapturable);
		}

		void UIElement::draw() const
		{
			onDraw();
		}

		void UIElement::drawOverlay() const
		{
			onDrawOverlay();
		}

		void UIElement::drawDebug() const
		{
			onDrawDebug();
		}

		bool UIElement::isEnabled() const noexcept
		{
			if (not m_enabled)
			{
				return false;
			}

			if (const auto pParentContainer = getParentContainer())
			{
				return pParentContainer->isEnabled();
			}

			return true;
		}

		void UIElement::setEnabled(const bool enabled) noexcept
		{
			m_enabled = enabled;

			if (not enabled)
			{
				m_hasMouseCapture = false;
			}
		}

		bool UIElement::isHovered() const noexcept
		{
			return m_hovered;
		}

		void UIElement::setHovered(const bool hovered) noexcept
		{
			m_hovered = hovered;
		}

		bool UIElement::hasMouseCapture() const noexcept
		{
			return m_hasMouseCapture;
		}

		void UIElement::setMouseCapture(const bool captured) noexcept
		{
			m_hasMouseCapture = captured;
			MouseL.clearInput();
			Cursor::SetCapture(captured);
		}

		void UIElement::setParentContainer(const std::shared_ptr<UIContainer>& container)
		{
			m_parentContainer = container;
		}

		std::shared_ptr<UIContainer> UIElement::getParentContainer() const
		{
			return m_parentContainer.lock();
		}

		bool UIElement::onUpdate([[maybe_unused]] const bool cursorCapturable)
		{
			return false;
		}

		void UIElement::onDraw() const {}

		void UIElement::onDrawOverlay() const {}

		void UIElement::onDrawDebug() const
		{
			const RectF rect{ getSize() };

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
