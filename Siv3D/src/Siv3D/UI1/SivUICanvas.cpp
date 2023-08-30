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

# include <Siv3D/UI1/UICanvas.hpp>
# include <Siv3D/UI1/UIContainer.hpp>
# include "UICanvasDetail.hpp"

namespace s3d
{
	namespace UI1
	{
		UICanvas::UICanvas()
			: pImpl{ std::make_shared<UICanvasDetail>() } {}

		void UICanvas::update()
		{
			pImpl->update();
		}

		void UICanvas::draw() const
		{
			pImpl->draw();
		}

		void UICanvas::drawDebug() const
		{
			pImpl->drawDebug();
		}

		UIContainer& UICanvas::addContainer(const std::shared_ptr<UIContainer>& container)
		{
			return pImpl->addContainer(container);
		}

		void UICanvas::removeContainer(const UIContainerNameView name)
		{
			pImpl->removeContainer(name);
		}

		void UICanvas::clear()
		{
			pImpl->clear();
		}

		bool UICanvas::isEmpty() const noexcept
		{
			return pImpl->isEmpty();
		}

		size_t UICanvas::num_containers() const noexcept
		{
			return pImpl->num_containers();
		}

		const Array<std::shared_ptr<UIContainer>>& UICanvas::containers() const noexcept
		{
			return pImpl->containers();
		}

		bool UICanvas::hasContainer(const UIContainerNameView name) const noexcept
		{
			return pImpl->hasContainer(name);
		}

		UIContainer* UICanvas::findContainer(const UIContainerNameView name) const noexcept
		{
			return pImpl->findContainer(name);
		}

		UIContainer* UICanvas::findTopmostContainer() const noexcept
		{
			return pImpl->findTopmostContainer();
		}

		UIContainer* UICanvas::findBottommostContainer() const noexcept
		{
			return pImpl->findBottommostContainer();
		}

		//Array<UIContainer*> UICanvas::findByAttribute(const StringView attribute, const StringView value) const
		//{
		//	return pImpl->findByAttribute(attribute, value);
		//}

		//UIContainer* UICanvas::findFromPoint(const Vec2& pos) const noexcept
		//{
		//	return pImpl->findFromPoint(pos);
		//}

		void UICanvas::moveToTopmost(const UIContainerNameView name)
		{
			pImpl->moveToTopmost(name);
		}

		void UICanvas::moveUpward(const UIContainerNameView name) noexcept
		{
			pImpl->moveUpward(name);
		}

		void UICanvas::moveToBottommost(const UIContainerNameView name)
		{
			pImpl->moveToBottommost(name);
		}

		void UICanvas::moveDownward(const UIContainerNameView name) noexcept
		{
			pImpl->moveDownward(name);
		}

		String UICanvas::dumpDebugInfo() const
		{
			return pImpl->dumpDebugInfo();
		}
	}
}
