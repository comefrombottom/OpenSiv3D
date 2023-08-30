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
# include <Siv3D/Common.hpp>
# include <Siv3D/Array.hpp>

namespace s3d
{
	inline namespace UI1
	{
        template <class Container, class Predicate>
        class FilterView
        {
        public:

            template <class BaseIter>
            class iterator
            {
            public:

                iterator(BaseIter current, BaseIter end, Predicate pred)
                    : m_current{ current }
                    , m_end{ end }
                    , m_predicate{ std::move(pred) }
                {
                    advance();
                }

                iterator& operator ++()
                {
                    ++m_current;
                    advance();
                    return *this;
                }

                auto& operator *()
                {
                    return *m_current;
                }

                bool operator ==(const iterator& other) const noexcept
                {
                    return (m_current == other.m_current);
                }

                bool operator !=(const iterator& other) const noexcept
                {
                    return (m_current != other.m_current);
                }

            private:

                void advance()
                {
                    while ((m_current != m_end) && (not m_predicate(*m_current)))
                    {
                        ++m_current;
                    }
                }

                BaseIter m_current;
                BaseIter m_end;
                Predicate m_predicate;
            };

            FilterView(Container& container, Predicate pred)
                : m_container{ container }
                , m_predicate{ pred } {}

            auto begin()
            {
                return iterator{ m_container.begin(), m_container.end(), m_predicate };
            }

            auto end()
            {
                return iterator{ m_container.end(), m_container.end(), m_predicate };
            }

            auto begin() const
            {
                return iterator{ m_container.cbegin(), m_container.cend(), m_predicate };
            }

            auto end() const
            {
                return iterator{ m_container.cend(), m_container.cend(), m_predicate };
            }

            auto cbegin() const
            {
                return iterator{ m_container.cbegin(), m_container.cend(), m_predicate };
            }

            auto cend() const
            {
                return iterator{ m_container.cend(), m_container.cend(), m_predicate };
            }

        private:

            Container& m_container;
            Predicate m_predicate;
        };

        template <class Container, class Predicate>
        class FilterReverseView
        {
        public:

            template <class BaseIter>
            class reverse_iterator
            {
            public:

                reverse_iterator(BaseIter current, BaseIter end, Predicate pred)
                    : m_current{ current }
                    , m_end{ end }
                    , m_predicate{ std::move(pred) }
                {
                    advance();
                }

                reverse_iterator& operator ++()
                {
                    ++m_current;
                    advance();
                    return *this;
                }

                auto& operator *() 
                {
                    return *m_current;
                }

                bool operator ==(const reverse_iterator& other) const noexcept
                {
                    return (m_current == other.m_current);
                }

                bool operator !=(const reverse_iterator& other) const noexcept
                {
                    return (m_current != other.m_current);
                }

            private:

                void advance()
                {
                    while ((m_current != m_end) && (not m_predicate(*m_current)))
                    {
                        ++m_current;
                    }
                }

                BaseIter m_current;
                BaseIter m_end;
                Predicate m_predicate;
            };

            FilterReverseView(Container& container, Predicate pred)
                : m_container{ container }
                , m_predicate{ pred } {}

            auto begin()
            {
                return reverse_iterator{ m_container.rbegin(), m_container.rend(), m_predicate };
            }

            auto end()
            {
                return reverse_iterator{ m_container.rend(), m_container.rend(), m_predicate };
            }

            auto begin() const
            {
                return reverse_iterator{ m_container.crbegin(), m_container.crend(), m_predicate };
            }

            auto end() const
            {
                return reverse_iterator{ m_container.crend(), m_container.crend(), m_predicate };
            }

            auto cbegin() const
            {
                return reverse_iterator{ m_container.crbegin(), m_container.crend(), m_predicate };
            }

            auto cend() const
            {
                return reverse_iterator{ m_container.crend(), m_container.crend(), m_predicate };
            }

        private:

            Container& m_container;
            Predicate m_predicate;
        };
	}
}
