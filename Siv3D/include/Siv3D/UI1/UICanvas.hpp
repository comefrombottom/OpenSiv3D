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
# include "../PointVector.hpp"
# include "UIFwd.hpp"

namespace s3d
{
	inline namespace UI1
	{
		/// @brief UI コンテナ管理クラス
		class UICanvas
		{
		public:

			UICanvas();

			/// @brief 保持する全ての UI コンテナを更新します。
			void update();

			/// @brief 保持する全ての UI コンテナを描画します。
			void draw() const;

			/// @brief 保持する全ての UI コンテナをデバッグ表示します。
			void drawDebug() const;

			/// @brief UI コンテナを追加します。
			/// @param container 追加する UI コンテナ
			/// @return 追加した UI コンテナの参照
			UIContainer& addContainer(const std::shared_ptr<UIContainer>& container);

			/// @brief 指定した名前の UI コンテナを削除します。
			/// @param name 削除する UI コンテナの名前
			void removeContainer(UIContainerNameView name);

			/// @brief 保持する全ての UI コンテナを削除します。
			void clear();

			/// @brief 保持する UI コンテナがないかを返します。
			/// @return 保持する UI コンテナがない場合 true, それ以外の場合は false
			[[nodiscard]]
			bool isEmpty() const noexcept;

			/// @brief 保持する UI コンテナの数を返します。
			/// @return 保持する UI コンテナの数
			[[nodiscard]]
			size_t num_containers() const noexcept;

			/// @brief 保持する UI コンテナの配列への参照を返します。
			/// @return 保持する UI コンテナの配列への参照
			[[nodiscard]]
			const Array<std::shared_ptr<UIContainer>>& containers() const noexcept;

			/// @brief 指定した名前の UI コンテナが存在するかを返します。
			/// @param name UI コンテナの名前
			/// @return 指定した名前の UI コンテナが存在する場合 true, それ以外の場合は false
			[[nodiscard]]
			bool hasContainer(UIContainerNameView name) const noexcept;

			/// @brief 指定した名前の UI コンテナを返します。
			/// @param name UI コンテナの名前
			/// @return 指定した名前の UI コンテナへのポインタ、見つからなかった場合は nullptr
			[[nodiscard]]
			UIContainer* find(UIContainerNameView name) const noexcept;

			/// @brief 最前面にある UI コンテナを返します。
			/// @return 最前面にある UI コンテナへのポインタ、保持する UI コンテナがない場合は nullptr
			[[nodiscard]]
			UIContainer* findTopmost() const noexcept;

			/// @brief 最背面にある UI コンテナを返します。
			/// @return 最背面にある UI コンテナへのポインタ、保持する UI コンテナがない場合は nullptr
			[[nodiscard]]
			UIContainer* findBottommost() const noexcept;

			///// @brief 指定した属性と値を持つ UI コンテナを返します。
			///// @param attribute 属性
			///// @param value 値
			///// @return 指定した属性と値を持つ UI コンテナへのポインタの配列、見つからなかった場合は空の配列
			//[[nodiscard]]
			//Array<UIContainer*> findByAttribute(StringView attribute, StringView value) const;

			///// @brief 指定した座標の最前面にある UI コンテナを返します。
			///// @param pos 座標
			///// @return 指定した座標の最前面にある UI コンテナへのポインタ、見つからなかった場合は nullptr
			//[[nodiscard]]
			//UIContainer* findFromPoint(const Vec2& pos) const noexcept;

			/// @brief 指定した名前の UI コンテナを最前面に移動します。
			/// @param name UI コンテナの名前
			void moveToTopmost(UIContainerNameView name);
			
			/// @brief 指定した名前の UI コンテナを一段階前面に移動します。
			/// @param name UI コンテナの名前
			void moveUpward(UIContainerNameView name) noexcept;

			/// @brief 指定した名前の UI コンテナを最背面に移動します。
			/// @param name UI コンテナの名前
			void moveToBottommost(UIContainerNameView name);

			/// @brief 指定した名前の UI コンテナを一段階背面に移動します。
			/// @param name UI コンテナの名前
			void moveDownward(UIContainerNameView name) noexcept;

			/// @brief 保持する UI コンテナのデバッグ用情報を返します。
			/// @return 保持する UI コンテナのデバッグ用情報
			[[nodiscard]]
			String dumpDebugInfo() const;

		private:

			class UICanvasDetail;

			friend class UIContainer;

			std::shared_ptr<UICanvasDetail> pImpl;
		};
	}
}
