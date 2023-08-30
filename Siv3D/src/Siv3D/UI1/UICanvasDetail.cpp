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

# include <Siv3D/Error.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/UI1/UIContainer.hpp>
# include "UICanvasDetail.hpp"

namespace s3d
{
	namespace UI1
	{
		void UICanvas::UICanvasDetail::update()
		{
			bool cursorCapturable = true;

			Optional<UIContainerName> topmostContainerName;

			for (auto& container : updatableView())
			{
				const bool oldMouseCapture = Cursor::IsCaptured();

				if (container->update(cursorCapturable && (not oldMouseCapture)))
				{
					cursorCapturable = false;
				}

				if (const bool touched = (not oldMouseCapture && Cursor::IsCaptured()))
				{
					topmostContainerName = container->name();
				}
			}

			if (topmostContainerName)
			{
				moveToTopmost(*topmostContainerName);
			}
		}

		void UICanvas::UICanvasDetail::draw() const
		{
			for (const auto& container : drawableView())
			{
				container->draw();
				container->drawOverlay();
			}
		}

		void UICanvas::UICanvasDetail::drawDebug() const
		{
			for (const auto& container : drawableView())
			{
				container->drawDebug();
			}
		}

		UIContainer& UICanvas::UICanvasDetail::addContainer(const std::shared_ptr<UIContainer>& container)
		{
			const UIContainerName& name = container->name();

			if (m_table.contains(name))
			{
				throw Error{ U"UICanvas::addContainer(): UIContainer `{}` already exists"_fmt(name) };
			}

			m_containers.push_back(container);
			m_table.emplace(name, container);

			return *container;
		}

		void UICanvas::UICanvasDetail::removeContainer(const UIContainerNameView name)
		{
			const auto it = m_table.find(name);

			if (it == m_table.end())
			{
				return;
			}

			m_containers.remove(it->second);
			m_table.erase(it); // ここで it は無効になる
		}

		void UICanvas::UICanvasDetail::clear()
		{
			m_containers.clear();
			m_table.clear();
		}

		bool UICanvas::UICanvasDetail::isEmpty() const noexcept
		{
			return m_containers.isEmpty();
		}

		size_t UICanvas::UICanvasDetail::num_containers() const noexcept
		{
			return m_containers.size();
		}

		const Array<std::shared_ptr<UIContainer>>& UICanvas::UICanvasDetail::containers() const noexcept
		{
			return m_containers;
		}

		bool UICanvas::UICanvasDetail::hasContainer(const UIContainerNameView name) const noexcept
		{
			return m_table.contains(name);
		}

		UIContainer* UICanvas::UICanvasDetail::findContainer(const UIContainerNameView name) const noexcept
		{
			const auto it = m_table.find(name);

			if (it == m_table.end())
			{
				return nullptr;
			}

			return it->second.get();
		}

		UIContainer* UICanvas::UICanvasDetail::findTopmostContainer() const noexcept
		{
			if (m_containers.isEmpty())
			{
				return nullptr;
			}

			return m_containers.back().get();
		}

		UIContainer* UICanvas::UICanvasDetail::findBottommostContainer() const noexcept
		{
			if (m_containers.isEmpty())
			{
				return nullptr;
			}

			return m_containers.front().get();
		}

		//Array<UIContainer*> UICanvas::UICanvasDetail::findByAttribute(const StringView attribute, const StringView value) const
		//{
		//	return{};
		//}

		//UIContainer* UICanvas::UICanvasDetail::findFromPoint(const Vec2& pos) const noexcept
		//{
		//	return(nullptr);
		//}

		void UICanvas::UICanvasDetail::moveToTopmost(const UIContainerNameView name)
		{
			const auto it = m_table.find(name);

			if (it == m_table.end())
			{
				return;
			}

			const std::shared_ptr<UIContainer> pContainer = it->second;
			m_containers.remove(pContainer);
			m_containers.push_back(pContainer);
		}

		void UICanvas::UICanvasDetail::moveUpward(const UIContainerNameView name) noexcept
		{
			if (m_containers.size() < 2)
			{
				return;
			}

			const auto it = m_table.find(name);

			if (it == m_table.end())
			{
				return;
			}

			const std::shared_ptr<UIContainer> pContainer = it->second;
			const auto it2 = std::find(m_containers.begin(), m_containers.end(), pContainer);

			assert(it2 != m_containers.end());

			if (it2 == m_containers.begin())
			{
				return;
			}

			std::iter_swap(it2, std::prev(it2));
		}

		void UICanvas::UICanvasDetail::moveToBottommost(const UIContainerNameView name)
		{
			const auto it = m_table.find(name);

			if (it == m_table.end())
			{
				return;
			}

			const std::shared_ptr<UIContainer> pContainer = it->second;
			m_containers.remove(pContainer);
			m_containers.push_front(pContainer);
		}

		void UICanvas::UICanvasDetail::moveDownward(const UIContainerNameView name) noexcept
		{
			if (m_containers.size() < 2)
			{
				return;
			}

			const auto it = m_table.find(name);

			if (it == m_table.end())
			{
				return;
			}

			const std::shared_ptr<UIContainer> pContainer = it->second;
			const auto it2 = std::find(m_containers.begin(), m_containers.end(), pContainer);

			assert(it2 != m_containers.end());

			if (it2 == std::prev(m_containers.end()))
			{
				return;
			}

			std::iter_swap(it2, std::next(it2));
		}

		String UICanvas::UICanvasDetail::dumpDebugInfo() const
		{
			String result;

			for (auto it = m_containers.rbegin(); it != m_containers.rend(); ++it)
			{
				result += (*it)->dumpDebugInfo();
				result.push_back(U'\n');
			}

			return result;
		}

		bool UICanvas::UICanvasDetail::ShouldUpdate(const std::shared_ptr<UIContainer>& c) noexcept
		{
			return c->shouldUpdate();
		}

		bool UICanvas::UICanvasDetail::ShouldDraw(const std::shared_ptr<UIContainer>& c) noexcept
		{
			return c->shouldDraw();
		}
	}
}
