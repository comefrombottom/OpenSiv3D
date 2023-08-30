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
		/// @brief UI 要素を配置するウィンドウ
		class UIWindow : public UIContainer
		{
		public:

			struct Style
			{
				/// @brief 枠の太さ（ピクセル）
				double borderThickness = 1.0;

				/// @brief パネルの角の半径（ピクセル）
				double borderRadius = 4.0;

				/// @brief 背景色 | Background color
				Optional<ColorF> backgroundColor = ColorF{ 1.0 };

				/// @brief 無効時のオーバーレイ色 | Disabled overlay color
				Optional<ColorF> disabledOverlayColor = ColorF{ 0.98, 0.7 };

				/// @brief アクティブ時の枠の色 | Active border color
				Optional<ColorF> activeBorderColor = ColorF{ 0.68 };

				/// @brief 非アクティブ時の枠の色 | Inactive border color
				Optional<ColorF> inactiveBorderColor = ColorF{ 0.72 };

				/// @brief 無効時の枠の色 | Disabled border color
				Optional<ColorF> disabledBorderColor = ColorF{ 0.75 };

				/// @brief 影の設定 | Box shadow
				Optional<BoxShadow> boxShadow = BoxShadow{ Vec2{ 2, 2 }, 24, 1 };

				Padding padding = { 10, 20 };

				double titleBarHeight = 36.0;

				/// @brief アクティブ時のタイトルバーの色
				ColorF titleBarActiveColor = ColorF{ 0.82, 0.85, 0.93 };

				/// @brief 非アクティブ時のタイトルバーの色
				ColorF titleBarInactiveColor = ColorF{ 0.91 };

				[[nodiscard]]
				static Style Default();
			};

			SIV3D_NODISCARD_CXX20
			UIWindow() = default;

			SIV3D_NODISCARD_CXX20
			explicit UIWindow(UIContainerNameView name, StringView title, const RectF& rect, const Style& style = Style::Default());

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

			/// @brief UI ウィンドウを作成します。
			/// @param name UI コンテナとしての一意な名前
			/// @param rect ウィンドウの初期領域
			/// @param style スタイル
			/// @return 作成されたウィンドウ
			[[nodiscard]]
			static std::shared_ptr<UIWindow> Create(UIContainerNameView name, StringView title, const RectF& rect, const Style& style = Style::Default());

		protected:

			void onPressed() override;

			void onReleased() override;

		private:

			Style m_style;

			RectF m_rect = RectF::Empty();

			String m_title;

			bool m_active = false;

			bool m_dragging = false;

			[[nodiscard]]
			RoundRect getShape() const noexcept;

			[[nodiscard]]
			RectF getTitleBarRect() const noexcept;

			[[nodiscard]]
			void drawBackground() const;

			[[nodiscard]]
			void drawDebugBackground() const;
		};
	}
}
