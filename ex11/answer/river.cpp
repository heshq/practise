#include <iostream>
#include <array>
#include <vector>
#include <unordered_set>

using namespace std;

enum Stuff {
	STUFF_WOLF,
	STUFF_SHEEP,
	STUFF_VEGE,

	STUFF_COUNT
};

char const * names[ STUFF_COUNT + 1] = {
	"Wolf",
	"Sheep",
	"Vege",
	"Human"
};

const struct {
	unsigned a, b;
} BAD_RELATIONS[] = {
	{ STUFF_WOLF, STUFF_SHEEP},
	{ STUFF_SHEEP, STUFF_VEGE},
};

// just like std::bitset, without size limit:
class DynamicBitset {
	private:
		typedef unsigned char BaseType;
		vector< BaseType> _data;
		size_t _count;
		static constexpr size_t BITS_PER_BASETYPE = sizeof( BaseType) * 8;
	public:
		DynamicBitset() : _count( 0) {};
		DynamicBitset( DynamicBitset const &set)
			: _data( set._data), _count( set._count)
		{}

		DynamicBitset &flip( size_t idx)
		{
			size_t real_idx = idx / BITS_PER_BASETYPE;
			size_t offset = idx % BITS_PER_BASETYPE;
			while ( _data.size() <= real_idx)
				_data.push_back( 0);
			_data[ real_idx] ^= 1 << offset;
			if ( _data[ real_idx] & ( 1 << offset))
				_count ++;
			else
				_count --;
			return *this;
		}

		size_t count() const
		{
			return _count;
		}

		bool get( size_t idx) const
		{
			size_t real_idx = idx / BITS_PER_BASETYPE;
			size_t offset = idx % BITS_PER_BASETYPE;
			if ( _data.size() <= real_idx)
				return false;
			else
				return _data[ real_idx] & ( 1 << offset);
		}
		bool operator[]( size_t idx) const
		{
			return get( idx);
		}

		DynamicBitset &operator=( DynamicBitset const &set)
		{
			_data = set._data;
			_count = set._count;
			return *this;
		}

		void set( size_t idx, bool value)
		{
			size_t real_idx = idx / BITS_PER_BASETYPE;
			size_t offset = idx % BITS_PER_BASETYPE;
			while ( _data.size() <= real_idx)
				_data.push_back( 0);
			if ( static_cast< bool>( _data[ real_idx] ^ ( 1 << offset)) != value) {
				if ( value)
					_count ++;
				else
					_count --;
			}
			if ( value)
				_data[ real_idx] |= 1 << offset;
			else
				_data[ real_idx] &= ~( 1 << offset);
		}

		class Setter {
			friend class DynamicBitset;
			private:
				DynamicBitset &_owner;
				size_t _idx;
				Setter( DynamicBitset &owner, size_t idx)
					: _owner( owner), _idx( idx)
				{}
			public:
				bool operator=( bool value)
				{
					_owner.set( _idx, value);
					return value;
				}
				operator bool () const
				{
					return _owner.get( _idx);
				}
		};

		Setter operator[]( size_t idx)
		{
			return Setter( *this, idx);
		}

		size_t hash() const
		{
			size_t hash = 0;
			for ( auto &number : _data)
				hash ^= number;
			return hash;
		}

		bool operator==( DynamicBitset const &set) const
		{
			size_t my_size = _data.size();
			size_t other_size = set._data.size();

			while ( my_size > other_size)
				if ( _data[ -- my_size])
					return false;
			while ( my_size < other_size)
				if ( _data[ -- other_size])
					return false;
			for ( size_t i = 0; i < my_size; i ++)
				if ( _data[ i] != set._data[ i])
					return false;
			return true;
		}
};

namespace std {
	template<>
	struct hash< DynamicBitset> {
		size_t operator() ( DynamicBitset const &set) const
		{
			return set.hash();
		}
	};
}

class World {
	private:
		vector< unsigned> *_bad_relations;
		unordered_set< DynamicBitset> _record;
		size_t _size;

		bool _search( DynamicBitset &crossed, vector< unsigned> &answer);
	public:
		size_t const &size;

		World( size_t size)
			: _bad_relations( new vector< unsigned>[ size]),
				_size( size),
				size( _size)
		{}
		~World()
		{
			delete[] _bad_relations;
		}

		World &add_conflict( unsigned a, unsigned b)
		{
			if ( a < size && b < size) {
				_bad_relations[ a].push_back( b);
				_bad_relations[ b].push_back( a);
			}
			return *this;
		}

		vector< unsigned> search()
		{
			// crossed[ size] indicates if human is crossed:
			DynamicBitset crossed;
			vector< unsigned> result;
			_record.clear();
			_search( crossed, result);
			return result;
		}

};

bool
World::_search( DynamicBitset &crossed, vector< unsigned> &answer)
{
	// check if all is crossed:
	if ( crossed.count() > size)
		return true;

	_record.insert( crossed);

	// check if situation is valid:
	bool human_crossed = crossed[ size];
	for ( unsigned i = 0; i < size; i ++)
		if ( crossed[ i] != human_crossed)	// if human not looking
			for ( auto &who : _bad_relations[ i])
				if ( crossed[ i] == crossed[ who])
					return false;
	
	// try to move one stuff with human:
	crossed.flip( size);
	for ( unsigned i = 0; i < size; i ++)
		if ( crossed[ i] == human_crossed) {
			crossed.flip( i);
			if ( _record.find( crossed) == _record.end()) {
				answer.push_back( i);
				if ( _search( crossed, answer))
					return true;
				answer.pop_back();
			}
			crossed.flip( i);
		}
	
	// try to move human only:
	if ( _record.find( crossed) == _record.end()) {
		answer.push_back( size);
		if ( _search( crossed, answer))
			return true;
		answer.pop_back();
	}

	// hopeless sitution, restore changes and return:
	crossed.flip( size);
	return false;
}

int main()
{
	World world( STUFF_COUNT);
	for ( size_t i = 0; i < sizeof( BAD_RELATIONS) / sizeof( BAD_RELATIONS[ 0]); i ++)
		world.add_conflict( BAD_RELATIONS[ i].a, BAD_RELATIONS[ i].b);
	auto result = world.search();
	if ( result.empty())
		cout << "No Can't Do !!" << endl;
	else {
		bool cross = true;
		for ( auto &who : result) {
			if ( cross)
				cout << names[ who] << " -->" << endl;
			else
				cout << "<-- " << names[ who] << endl;
			cross = ! cross;
		}
	}
	return 0;
}

