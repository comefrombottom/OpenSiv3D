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
# include <Siv3D/UI1/UICanvas.hpp>
# include <Siv3D/HashTable.hpp>
# include "UIUtility.hpp"

namespace s3d
{
	namespace UI1
	{
		class UICanvas::UICanvasDetail
		{
		public:

			UICanvasDetail() = default;

			void update();

			void draw() const;

			void drawDebug() const;

			UIContainer& addContainer(const std::shared_ptr<UIContainer>& container);

			void removeContainer(UIContainerNameView name);

			void clear();

			[[nodiscard]]
			bool isEmpty() const noexcept;

			[[nodiscard]]
			size_t num_containers() const noexcept;

			[[nodiscard]]
			const Array<std::shared_ptr<UIContainer>>& containers() const noexcept;

			/// @brief 更新可能な UI コンテナのビューを返します。
			/// @return 更新可能な UI コンテナのビュー
			[[nodiscard]]
			auto updatableView() const noexcept
			{
				return FilterReverseView{ containers(), ShouldUpdate };
			}

			/// @brief 描画可能な UI コンテナのビューを返します。
			/// @return 描画可能な UI コンテナのビュー
			[[nodiscard]]
			auto drawableView() const noexcept
			{
				return FilterView{ containers(), ShouldDraw };
			}

			[[nodiscard]]
			bool hasContainer(UIContainerNameView name) const noexcept;

			[[nodiscard]]
			UIContainer* findContainer(UIContainerNameView name) const noexcept;

			[[nodiscard]]
			UIContainer* findTopmostContainer() const noexcept;

			[[nodiscard]]
			UIContainer* findBottommostContainer() const noexcept;

			//[[nodiscard]]
			//Array<UIContainer*> findByAttribute(StringView attribute, StringView value) const;

			//[[nodiscard]]
			//UIContainer* findFromPoint(const Vec2& pos) const noexcept;

			void moveToTopmost(UIContainerNameView name);

			void moveUpward(UIContainerNameView name) noexcept;

			void moveToBottommost(UIContainerNameView name);

			void moveDownward(UIContainerNameView name) noexcept;

			[[nodiscard]]
			String dumpDebugInfo() const;

		private:

			// 末尾の要素ほど前面に描画される
			Array<std::shared_ptr<UIContainer>> m_containers;

			HashTable<UIContainerName, std::shared_ptr<UIContainer>> m_table;

			static bool ShouldUpdate(const std::shared_ptr<UIContainer>& c) noexcept;

			static bool ShouldDraw(const std::shared_ptr<UIContainer>& c) noexcept;
		};
	}
}
