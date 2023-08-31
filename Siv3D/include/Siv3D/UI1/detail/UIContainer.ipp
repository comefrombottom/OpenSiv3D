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

# pragma once

namespace s3d
{
	namespace UI1
	{
		template <class UIElementType, std::enable_if_t<std::is_base_of_v<UIElement, UIElementType>>*>
		inline bool UIContainer::is(const size_t index) const noexcept
		{
			if (m_elements.size() <= index)
			{
				return false;
			}

			return (dynamic_cast<const UIElementType*>(m_elements[index].element.get()) != nullptr);
		}

		template <class UIElementType, std::enable_if_t<std::is_base_of_v<UIElement, UIElementType>>*>
		inline bool UIContainer::is(const UIElementNameView name) const noexcept
		{
			const auto it = m_table.find(name);

			if (it == m_table.end())
			{
				return false;
			}

			return (dynamic_cast<const UIElementType*>(it->second.get()) != nullptr);
		}

		template <class UIElementType, std::enable_if_t<std::is_base_of_v<UIElement, UIElementType>>*>
		const UIElementType& UIContainer::get(const size_t index) const
		{
			if (m_elements.size() <= index)
			{
				throw Error{ U"UIContainer::get<{}>({}): index out of range"_fmt(Demangle(typeid(UIElementType).name()), index) };
			}

			UIElementType* p = dynamic_cast<UIElementType*>(m_elements[index].element.get());

			if (not p)
			{
				const String target = Demangle(typeid(UIElementType).name());
				const String actual = Demangle(typeid(*m_elements[index].element).name());
				throw Error{ U"UIContainer::get<{}>({}): invalid type (expected: {}, actual: {})"_fmt(target, index, target, actual) };
			}

			return *p;
		}

		template <class UIElementType, std::enable_if_t<std::is_base_of_v<UIElement, UIElementType>>*>
		UIElementType& UIContainer::get(const size_t index)
		{
			return const_cast<UIElementType&>(static_cast<const UIContainer&>(*this).get<UIElementType>(index));
		}

		template <class UIElementType, std::enable_if_t<std::is_base_of_v<UIElement, UIElementType>>*>
		const UIElementType& UIContainer::get(const UIElementNameView name) const
		{
			const auto it = m_table.find(name);

			if (it == m_table.end())
			{
				throw Error{ U"UIContainer::get<{}>({}): element not found"_fmt(Demangle(typeid(UIElementType).name()), name) };
			}

			UIElementType* p = dynamic_cast<UIElementType*>(it->second.get());

			if (not p)
			{
				const String target = Demangle(typeid(UIElementType).name());
				const String actual = Demangle(typeid(*it->second).name());
				throw Error{ U"UIContainer::get<{}>({}): invalid type (expected: {}, actual: {})"_fmt(target, name, target, actual) };
			}

			return *p;
		}

		template <class UIElementType, std::enable_if_t<std::is_base_of_v<UIElement, UIElementType>>*>
		UIElementType& UIContainer::get(const UIElementNameView name)
		{
			return const_cast<UIElementType&>(static_cast<const UIContainer&>(*this).get<UIElementType>(name));
		}
	}
}
