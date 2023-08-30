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
# include "../Optional.hpp"
# include "../ColorHSV.hpp"
# include "Padding.hpp"
# include "BoxShadow.hpp"
# include "UIContainer.hpp"

namespace s3d
{
	inline namespace UI1
	{
		/// @brief UI 要素を配置するパネル
		class UIPanel final : public UIContainer
		{
		public:

			struct Style
			{
				/// @brief 枠の太さ（ピクセル）
				double borderThickness = 0.0;

				/// @brief パネルの角の半径（ピクセル）
				double borderRadius = 0.0;

				/// @brief 背景色 | Background color
				Optional<ColorF> backgroundColor = ColorF{ 0.92 };

				/// @brief 無効時のオーバーレイ色 | Disabled overlay color
				Optional<ColorF> disabledOverlayColor = ColorF{ 0.98, 0.75 };

				/// @brief 枠の色 | Border color
				Optional<ColorF> borderColor = ColorF{ 0.5 };

				/// @brief 無効時の枠の色 | Disabled border color
				Optional<ColorF> disabledBorderColor = ColorF{ 0.75 };

				/// @brief 影の設定 | Box shadow
				Optional<BoxShadow> boxShadow;

				Padding padding = { 20, 20 };

				[[nodiscard]]
				static Style Default();
			};

			SIV3D_NODISCARD_CXX20
			UIPanel() = default;

			SIV3D_NODISCARD_CXX20
			explicit UIPanel(UIContainerNameView name, const RectF& rect, const Style& style = Style::Default());

			[[nodiscard]]
			StringView type() const noexcept override;

			[[nodiscard]]
			SizeF getSize() const noexcept override;

			[[nodiscard]]
			RectF getBounds() const noexcept override;

			bool onUpdate(bool cursorCapturable = true) override;

			void onDraw() const override;

			void onDrawOverlay() const override;

			void onDrawDebug() const override;

			void setPos(const Vec2& pos) noexcept;

			void setSize(const SizeF& size) noexcept;

			/// @brief UI パネルを作成します。
			/// @param name UI コンテナとしての一意な名前
			/// @param rect パネルの領域
			/// @param style スタイル
			/// @return 作成されたパネル
			[[nodiscard]]
			static std::shared_ptr<UIPanel> Create(UIContainerNameView name, const RectF& rect, const Style& style = Style::Default());

		private:

			Style m_style;

			RectF m_rect = RectF::Empty();

			[[nodiscard]]
			RoundRect getShape() const noexcept;

			[[nodiscard]]
			void drawBackground() const;

			[[nodiscard]]
			void drawDebugBackground() const;
		};
	}
}
