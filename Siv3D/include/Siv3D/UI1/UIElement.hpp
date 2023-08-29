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

		private:

		};
	}
}
