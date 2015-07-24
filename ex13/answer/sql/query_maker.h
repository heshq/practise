#ifndef _QUERY_MAKER_H
#define _QUERY_MAKER_H

#include <string>
#include <map>
#include <vector>

namespace query_maker
{
    namespace _query_maker_inner
    {
        class HasFactor;
    }

    class Factor {
        friend class _query_maker_inner::HasFactor;
        private:
            std::string _str;
            enum Type {
                NONE, PRIMITIVE, AND, OR, MIXED
            } _type;
            Factor( std::string const &, Type type);
        public:
            Factor();
            Factor( Factor const &);
            Factor( std::string const &column, std::string const &symbol, std::string const &value);
            Factor( std::string const &column, std::string const &symbol, int value);
            Factor( std::string const &column, std::string const &symbol, float value);
            Factor &operator=( Factor const &);
            Factor &operator&=( Factor const &);
            Factor &operator|=( Factor const &);
            Factor operator&( Factor const &) const;
            Factor operator|( Factor const &) const;
            std::string const &to_string() const;
    };

    class QueryBase {
        protected:
            std::string _table;
            std::string _result;
            bool _dirty;
            virtual void _build() = 0;
            QueryBase();
            void _set_table( std::string const &);
        public:
            QueryBase( std::string const &table);
            virtual ~QueryBase();
            std::string const &table() const;

            std::string const &to_string();
            operator std::string();
            virtual bool check() const = 0;
            operator bool() const;
    };

    namespace _query_maker_inner
    {
        class SetColumn {
            protected:
                std::map< std::string, std::string > _columns;
                void _set( std::string const &, int);
                void _set( std::string const &, float);
                void _set( std::string const &, std::string const &);
        };

        class HasFactor {
            protected:
                Factor _factor;
                HasFactor();
                void _where( Factor const &);
                bool _has_factor() const;
        };

        std::string chomp( std::string const &);

    } // namespace _query_maker_inner

    class Select : public QueryBase, public _query_maker_inner::HasFactor {
        private:
            virtual void _build() override;
            std::vector< std::string > _columns;
            std::vector< std::string > _orders;
            bool _asc{ true};
            void _set_single_column( std::vector< std::string > &, std::string const &, size_t begin, size_t end);
            void _set_columns( std::vector< std::string > &, std::string const &);
        public:
            using QueryBase::QueryBase;
            Select &table( std::string const &);

            Select &where( Factor const &);
            template< typename T >
            Select &where( std::string const &column, std::string const &symbol, T value);

            Select &asc();
            Select &desc();
            Select &order_by( std::string const &);
            Select &column( std::string const &);
            virtual bool check() const override;
    };

    class Insert : public QueryBase, public _query_maker_inner::SetColumn {
        private:
            virtual void _build() override;
        public:
            using QueryBase::QueryBase;
            Insert &table( std::string const &);

            template< typename T >
            Insert &set( std::string const &column, T value);

            virtual bool check() const override;
    };

    class Update : public QueryBase, public _query_maker_inner::SetColumn, public _query_maker_inner::HasFactor {
        private:
            virtual void _build() override;
        public:
            using QueryBase::QueryBase;
            Update &table( std::string const &);

            template< typename T>
            Update &set( std::string const &column, T value);

            Update &where( Factor const &);

            template< typename T >
            Update &where( std::string const &column, std::string const &symbol, T value);

            virtual bool check() const override;
    };

    class Delete : public QueryBase, public _query_maker_inner::HasFactor {
        private:
            virtual void _build() override;
        public:
            using QueryBase::QueryBase;
            Delete &table( std::string const &);
            Delete &where( Factor const &);

            template< typename T >
            Delete &where( std::string const &column, std::string const &symbol, T value);

            virtual bool check() const override;
    };

} // namespace query_maker

#endif

