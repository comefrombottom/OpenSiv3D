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

# include <Siv3D/UI1/UIContainer.hpp>

namespace s3d
{
	namespace UI1
	{
		UIContainer::UIContainer(const UIContainerNameView name)
			: m_name{ name } {}

		const String& UIContainer::name() const noexcept
		{
			return m_name;
		}

		void UIContainer::show(const bool show)
		{
			m_shown = show;
		}

		void UIContainer::hide()
		{
			m_shown = false;
		}

		bool UIContainer::isShown() const noexcept
		{
			return m_shown;
		}

		bool UIContainer::isHidden() const noexcept
		{
			return (not m_shown);
		}

		size_t UIContainer::num_elements() const noexcept
		{
			return m_elements.size();
		}

		UIContainer& UIContainer::add(const UIElementNameView name, const std::shared_ptr<UIElement>& element)
		{
			element->setParentContainer(shared_from_this());
			m_elements.push_back({ UIElementName{ name }, element });
			return *this;
		}

		UIContainer& UIContainer::_setRoot(const std::shared_ptr<UICanvas::UICanvasDetail>& pCanvas)
		{
			m_pCanvas = pCanvas;
			return *this;
		}
	}
}
