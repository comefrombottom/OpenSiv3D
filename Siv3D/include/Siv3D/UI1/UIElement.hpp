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
# include "../PointVector.hpp"
# include "Margin.hpp"
# include "UIFwd.hpp"

namespace s3d
{
	inline namespace UI1
	{
		using UIElementName = String;
		using UIElementNameView = StringView;

		class UIElement
		{
		public:

			UIElement() = default;

			virtual ~UIElement();

			[[nodiscard]]
			virtual SizeF getSize() const noexcept = 0;

			[[nodiscard]]
			virtual Margin getMargin() const noexcept;

			bool update(bool cursorCapturable = true);

			void draw() const;

			void drawOverlay() const;

			void drawDebug() const;

			[[nodiscard]]
			bool isEnabled() const noexcept;

			void setEnabled(const bool enabled) noexcept;

			[[nodiscard]]
			bool isHovered() const noexcept;

			void setHovered(const bool hovered) noexcept;

			[[nodiscard]]
			bool hasMouseCapture() const noexcept;

			void setMouseCapture(const bool captured) noexcept;

			void setParentContainer(const std::shared_ptr<UIContainer>& container);

			[[nodiscard]]
			std::shared_ptr<UIContainer> getParentContainer() const;

		protected:

			virtual bool onUpdate(bool cursorCapturable);

			/// @brief UI 要素の描画処理を記述します。
			virtual void onDraw() const;

			/// @brief UI 要素のオーバーレイ描画処理を記述します。
			virtual void onDrawOverlay() const;

			/// @brief UI 要素のデバッグ描画処理を記述します。
			virtual void onDrawDebug() const;

		private:

			std::weak_ptr<UIContainer> m_parentContainer;

			bool m_enabled = true;

			bool m_hasMouseCapture = false;

			bool m_hovered = false;
		};
	}
}
