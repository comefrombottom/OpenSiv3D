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
# include "../ColorHSV.hpp"
# include "UIElement.hpp"

namespace s3d
{
	inline namespace UI1
	{
		class ColorRect final : public UIElement
		{
		public:

			SIV3D_NODISCARD_CXX20
			ColorRect() = default;

			SIV3D_NODISCARD_CXX20
			explicit ColorRect(const SizeF& size, const ColorF& color = ColorF{ 1.0 });

			[[nodiscard]]
			static std::shared_ptr<ColorRect> Create(const SizeF& size, const ColorF& color = ColorF{ 1.0 });

		private:

			[[nodiscard]]
			SizeF getSize() const noexcept override;

			void onDraw() const override;

			SizeF m_size = { 0, 0 };

			ColorF m_color = ColorF{ 1.0 };
		};
	}
}
