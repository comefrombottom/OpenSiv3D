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

# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Transformer2D.hpp>
# include <Siv3D/UI1/Padding.hpp>
# include <Siv3D/UI1/UIContainer.hpp>

namespace s3d
{
	namespace detail
	{
		struct LineInfo
		{
			double areaWidth = 0.0;

			// ペンの X 座標
			double penPosX = 0.0;

			// 最後の要素の右マージン
			double previousRightMargin = 0.0;

			// 前の行で最も Y 座標が大きい要素の Y 座標
			double previousMaxElementY = 0.0;

			// 前の行で最も Y 座標が大きいマージン
			double previousMaxMarginY = 0.0;

			// 最も Y 座標が大きい要素の Y 座標
			double maxElementY = 0.0;

			// 最も Y 座標が大きいマージン
			double maxMarginY = 0.0;

			void lineBreak() noexcept
			{
				penPosX = 0.0;
				previousRightMargin = 0.0;
				previousMaxElementY = maxElementY;
				previousMaxMarginY = maxMarginY;
				maxElementY = 0.0;
				maxMarginY = 0.0;
			}

			[[nodiscard]]
			bool shouldBreak(const SizeF& elementSize, const Margin& elementMargin) const noexcept
			{
				const double leftMargin = Max(previousRightMargin, elementMargin.left);
				const double rightMargin = elementMargin.right;
				return (areaWidth < (penPosX + (leftMargin + elementSize.x + rightMargin)));
			}

			[[nodiscard]]
			double calculatePenPosY(const Margin& elementMargin) const noexcept
			{
				return Max(previousMaxMarginY, (previousMaxElementY + elementMargin.top));
			}

			void next(const double penPosY, const double leftMargin, const SizeF& elementSize, const Margin& elementMargin)
			{
				penPosX += (leftMargin + elementSize.x);
				previousRightMargin = elementMargin.right;
				maxElementY = Max(maxElementY, (penPosY + elementSize.y));
				maxMarginY = Max(maxMarginY, (penPosY + elementSize.y + elementMargin.bottom));
			}
		};
	}

	namespace UI1
	{
		UIContainer::UIContainer(const UIContainerNameView name)
			: m_name{ name } {}

		const String& UIContainer::name() const noexcept
		{
			return m_name;
		}

		void UIContainer::show(const bool show)
		{
			m_shown = show;
		}

		void UIContainer::hide()
		{
			m_shown = false;
		}

		bool UIContainer::shouldUpdate() const noexcept
		{
			return isEnabled();
		}

		bool UIContainer::shouldDraw() const noexcept
		{
			return isShown();
		}

		bool UIContainer::isShown() const noexcept
		{
			return m_shown;
		}

		bool UIContainer::isHidden() const noexcept
		{
			return (not m_shown);
		}

		size_t UIContainer::num_elements() const noexcept
		{
			return m_elements.size();
		}

		UIContainer& UIContainer::add(const UIElementNameView name, const std::shared_ptr<UIElement>& element)
		{
			element->setParentContainer(shared_from_this());
			m_elements.push_back({ UIElementName{ name }, element });
			return *this;
		}

		UIContainer& UIContainer::_setRoot(const std::shared_ptr<UICanvas::UICanvasDetail>& pCanvas)
		{
			m_pCanvas = pCanvas;
			return *this;
		}

		String UIContainer::dumpDebugInfo() const
		{
			String result = U"{} ({}) {:.1f} "_fmt(m_name, type(), getBounds());

			if (shouldUpdate())
			{
				result += U".update ";
			}

			if (shouldDraw())
			{
				result += U".draw ";
			}

			if (not isShown())
			{
				result += U"[hidden]";
			}

			if (not isEnabled())
			{
				result += U"[disabled]";
			}

			return result;
		}

		bool UIContainer::onUpdateHelper(bool cursorCapturable, const bool shapeMouseOver, const Padding& padding, const std::function<void(SizeF)>& resizeFunction)
		{
			bool childHasCursorCapture = false;
			bool childHasMouseCapture = false;

			// 子要素の配置を計算する
			{
				const Vec2 basePos = (getBounds().pos + padding.topLeft());
				const Transformer2D containerTransform{ Mat3x2::Translate(basePos), TransformCursor::Yes };

				detail::LineInfo lineInfo
				{
					.areaWidth = (getBounds().w - padding.totalWidth()),
				};

				double areaHeight = (getBounds().h - padding.totalHeight());

				for (const auto& element : m_elements)
				{
					// 要素のサイズ
					const SizeF elementSize = element.element->getSize();

					// 要素のマージン
					const Margin elementMargin = element.element->getMargin();

					// 改行が必要な場合
					if (lineInfo.shouldBreak(elementSize, elementMargin))
					{
						lineInfo.lineBreak();
					}

					// 左マージン
					const double leftMargin = Max(lineInfo.previousRightMargin, elementMargin.left);

					// 下マージン
					const double bottomMargin = elementMargin.bottom;

					// ペンの Y 座標
					const double penPosY = lineInfo.calculatePenPosY(elementMargin);

					if (areaHeight < (penPosY + elementSize.y + bottomMargin))
					{
						const SizeF newSize{ getSize().x, (penPosY + elementSize.y + bottomMargin + padding.totalHeight()) };
						resizeFunction(newSize);
					}

					{
						const Transformer2D elementTransform{ Mat3x2::Translate((lineInfo.penPosX + leftMargin), penPosY), TransformCursor::Yes };

						if (element.element->update(cursorCapturable))
						{
							cursorCapturable = false;
							childHasCursorCapture = true;
						}

						childHasMouseCapture |= element.element->hasMouseCapture();
					}

					lineInfo.next(penPosY, leftMargin, elementSize, elementMargin);
				}
			}

			return (updateState((cursorCapturable || childHasCursorCapture || childHasMouseCapture), shapeMouseOver) || childHasCursorCapture);
		}

		void UIContainer::onDrawHelper(const Padding& padding) const
		{
			const Vec2 basePos = (getBounds().pos + padding.topLeft());
			const Transformer2D containerTransform{ Mat3x2::Translate(basePos), TransformCursor::Yes };

			detail::LineInfo lineInfo
			{
				.areaWidth = (getBounds().w - padding.totalWidth()),
			};

			for (const auto& element : m_elements)
			{
				// 要素のサイズ
				const SizeF elementSize = element.element->getSize();

				// 要素のマージン
				const Margin elementMargin = element.element->getMargin();

				// 改行が必要な場合
				if (lineInfo.shouldBreak(elementSize, elementMargin))
				{
					lineInfo.lineBreak();
				}

				// 左マージン
				const double leftMargin = Max(lineInfo.previousRightMargin, elementMargin.left);

				// ペンの Y 座標
				const double penPosY = lineInfo.calculatePenPosY(elementMargin);

				{
					const Transformer2D elementTransform{ Mat3x2::Translate((lineInfo.penPosX + leftMargin), penPosY), TransformCursor::Yes };
					element.element->draw();
				}

				lineInfo.next(penPosY, leftMargin, elementSize, elementMargin);
			}
		}

		void UIContainer::onDrawOverlayHelper(const Padding& padding) const
		{
			const Vec2 basePos = (getBounds().pos + padding.topLeft());
			const Transformer2D containerTransform{ Mat3x2::Translate(basePos), TransformCursor::Yes };

			detail::LineInfo lineInfo
			{
				.areaWidth = (getBounds().w - padding.totalWidth()),
			};

			for (const auto& element : m_elements)
			{
				// 要素のサイズ
				const SizeF elementSize = element.element->getSize();

				// 要素のマージン
				const Margin elementMargin = element.element->getMargin();

				// 改行が必要な場合
				if (lineInfo.shouldBreak(elementSize, elementMargin))
				{
					lineInfo.lineBreak();
				}

				// 左マージン
				const double leftMargin = Max(lineInfo.previousRightMargin, elementMargin.left);

				// ペンの Y 座標
				const double penPosY = lineInfo.calculatePenPosY(elementMargin);

				{
					const Transformer2D elementTransform{ Mat3x2::Translate((lineInfo.penPosX + leftMargin), penPosY), TransformCursor::Yes };
					element.element->drawOverlay();
				}

				lineInfo.next(penPosY, leftMargin, elementSize, elementMargin);
			}
		}

		void UIContainer::onDrawDebugHelper(const Padding& padding) const
		{
			const Vec2 basePos = (getBounds().pos + padding.topLeft());
			const Transformer2D containerTransform{ Mat3x2::Translate(basePos), TransformCursor::Yes };

			detail::LineInfo lineInfo
			{
				.areaWidth = (getBounds().w - padding.totalWidth()),
			};

			for (const auto& element : m_elements)
			{
				// 要素のサイズ
				const SizeF elementSize = element.element->getSize();

				// 要素のマージン
				const Margin elementMargin = element.element->getMargin();

				// 改行が必要な場合
				if (lineInfo.shouldBreak(elementSize, elementMargin))
				{
					lineInfo.lineBreak();
				}

				// 左マージン
				const double leftMargin = Max(lineInfo.previousRightMargin, elementMargin.left);

				// ペンの Y 座標
				const double penPosY = lineInfo.calculatePenPosY(elementMargin);

				{
					const Transformer2D elementTransform{ Mat3x2::Translate((lineInfo.penPosX + leftMargin), penPosY), TransformCursor::Yes };
					element.element->drawDebug();
				}

				lineInfo.next(penPosY, leftMargin, elementSize, elementMargin);
			}
		}
	}
}
