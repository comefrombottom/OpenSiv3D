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
# include "../Common.hpp"
# include "../String.hpp"
# include "../HashTable.hpp"
# include "../Demangle.hpp"
# include "UIElement.hpp"
# include "UICanvas.hpp"

namespace s3d
{
	inline namespace UI1
	{
		using UIContainerName = String;
		using UIContainerNameView = StringView;

		class UIContainer : public UIElement, public std::enable_shared_from_this<UIContainer>
		{
		public:

			/// @brief UI コンテナを作成します。
			/// @param name UI コンテナの一意な名前
			explicit UIContainer(UIContainerNameView name);

			virtual ~UIContainer() = default;

			/// @brief UI コンテナの名前を返します。
			/// @return UI コンテナの名前
			[[nodiscard]]
			const UIContainerName& name() const noexcept;

			/// @brief UI コンテナの種類を返します。
			/// @return UI コンテナの種類
			[[nodiscard]]
			virtual StringView type() const noexcept = 0;

			/// @brief UI コンテナの領域（ピクセル）を返します。
			/// @return UI コンテナの領域（ピクセル）
			[[nodiscard]]
			virtual RectF getBounds() const noexcept = 0;

			/// @brief UI コンテナの表示状態を設定します。
			/// @param show 表示状態にする場合 true, 非表示状態にする場合は false
			virtual void show(bool show = true);

			/// @brief UI コンテナを非表示状態にします。
			virtual void hide();

			[[nodiscard]]
			virtual bool shouldUpdate() const noexcept;

			[[nodiscard]]
			virtual bool shouldDraw() const noexcept;

			/// @brief UI コンテナが表示状態であるかを返します。
			/// @return UI コンテナが表示状態である場合 true, それ以外の場合は false
			[[nodiscard]]
			bool isShown() const noexcept;

			/// @brief UI コンテナが非表示状態であるかを返します。
			/// @return UI コンテナが非表示状態である場合 true, それ以外の場合は false
			[[nodiscard]]
			bool isHidden() const noexcept;

			/// @brief UI コンテナに UI 要素を追加します。
			/// @param name 追加する UI 要素の一意な名前
			/// @param element 追加する UI 要素
			/// @return 追加した UI 要素への参照
			virtual UIContainer& add(UIElementNameView name, const std::shared_ptr<UIElement>& element);

			/// @brief UI コンテナが持つ UI 要素の数を返します。
			/// @return UI コンテナが持つ UI 要素の数
			[[nodiscard]]
			size_t num_elements() const noexcept;

			/// @brief UI コンテナが持つ UI 要素をすべて削除します。
			void clear();

			bool hasElement(UIElementNameView name) const noexcept;

			template <class UIElementType, std::enable_if_t<std::is_base_of_v<UIElement, UIElementType>>* = nullptr>
			[[nodiscard]]
			bool is(size_t index) const noexcept;

			template <class UIElementType, std::enable_if_t<std::is_base_of_v<UIElement, UIElementType>>* = nullptr>
			[[nodiscard]]
			bool is(UIElementNameView name) const noexcept;

			template <class UIElementType, std::enable_if_t<std::is_base_of_v<UIElement, UIElementType>>* = nullptr>
			[[nodiscard]]
			const UIElementType& get(size_t index) const;

			template <class UIElementType, std::enable_if_t<std::is_base_of_v<UIElement, UIElementType>>* = nullptr>
			[[nodiscard]]
			UIElementType& get(size_t index);

			template <class UIElementType, std::enable_if_t<std::is_base_of_v<UIElement, UIElementType>>* = nullptr>
			[[nodiscard]]
			const UIElementType& get(UIElementNameView name) const;

			template <class UIElementType, std::enable_if_t<std::is_base_of_v<UIElement, UIElementType>>* = nullptr>
			[[nodiscard]]
			UIElementType& get(UIElementNameView name);

			UIContainer& _setRoot(const std::shared_ptr<UICanvas::UICanvasDetail>& pCanvas);

			[[nodiscard]]
			String dumpDebugInfo() const;

		protected:

			struct Element
			{
				UIElementName name;

				std::shared_ptr<UIElement> element;
			};

			Array<Element> m_elements;

			HashTable<UIElementName, std::shared_ptr<UIElement>> m_table;

			std::weak_ptr<UICanvas::UICanvasDetail> m_pCanvas;

			[[nodiscard]]
			bool onUpdateHelper(bool cursorCapturable, bool shapeMouseOver, double yOffset, const Padding& padding, const std::function<void(SizeF)>& resizeFunction);

			void onDrawHelper(double yOffset, const Padding& padding) const;

			void onDrawOverlayHelper(double yOffset, const Padding& padding) const;

			void onDrawDebugHelper(double yOffset, const Padding& padding) const;

		private:

			UIContainerName m_name;

			bool m_shown = false;
		};
	}
}

# include "detail/UIContainer.ipp"
