#include <iostream>
#include <memory>
#include <deque>
#include <unordered_map>
#include <map>
#include <bitset>

using namespace std;

//#define USE_HASH
//#define DEBUG_MAP

#ifdef USE_HASH
#	define MAP unordered_map
#else
#	define MAP std::map
#endif

struct Coordinate {
	static Coordinate const moves[];
	static size_t const MOVES_NUMBER;
	static size_t opposite_move( size_t idx);

	static int instant_count;
	static int instant_max_count;

	int line, column;
	Coordinate( Coordinate const &coo) : line( coo.line), column( coo.column)
	{
		if ( ++ instant_count > instant_max_count)
			instant_max_count = instant_count;
	}
	Coordinate( int l = 0, int c = 0) : line( l), column( c)
	{
		if ( ++ instant_count > instant_max_count)
			instant_max_count = instant_count;
	}
	~Coordinate() { instant_count --;}
	Coordinate operator+( Coordinate const &coo) const
	{
		Coordinate result( coo);
		result.line	+= line;
		result.column	+= column;
		return result;
	}
	// for unordered_map:
	bool operator==( Coordinate const &coo) const
	{
		return line == coo.line && column == coo.column;
	}
	// for map:
	bool operator<( Coordinate const &coo) const
	{
		if( line == coo.line)
			return column < coo.column;
		else
			return line < coo.line;
	}
	bool valid( size_t width, size_t height) const
	{
		return size_t( line) < height
			&& size_t( column) < width;
	}
};

Coordinate const
Coordinate::moves[] = {
	{ 1, 2},	{ 2, 1},	{ 2, -1},	{ 1, -2},
	{ -1, -2},	{ -2, -1},	{ -2, 1},	{ -1, 2}
};

size_t const
Coordinate::MOVES_NUMBER = sizeof( moves) / sizeof( moves[ 0]);

size_t
Coordinate::opposite_move( size_t idx)
{
	return ( idx + 4) % MOVES_NUMBER;
}

int
Coordinate::instant_count = 0;

int
Coordinate::instant_max_count = 0;

#ifdef USE_HASH
namespace std
{
	template<>
	struct hash< Coordinate> {
		size_t operator()( Coordinate const &coo) const
		{
			return coo.line ^ coo.column;
		}
	};
}
#endif

struct Step : Coordinate {
	shared_ptr< Step> from;
	bitset< Coordinate::MOVES_NUMBER> explored;

	Step( int l = 0, int c = 0) : Coordinate( l, c) {}
	Step( Coordinate const &coo) : Coordinate( coo) {}
};

shared_ptr< Step> search( size_t width, size_t height, Coordinate &start, Coordinate &target)
{
	deque< shared_ptr< Step> > queue;
	MAP< Coordinate, shared_ptr< Step> > record; // marks every coordinate currently in queue

	{ // Initialization:
		shared_ptr< Step> first_step( new Step( start));
		record[ *first_step] = first_step;
		queue.push_back( first_step);
	}

	shared_ptr< Step> answer;

	while ( ! queue.empty()) { // Searching:
		shared_ptr< Step> current_step( queue.front());
		queue.pop_front();

		if ( target == *current_step) {
			answer = current_step;
			break;
		}

		for ( size_t i = 0; i < Coordinate::MOVES_NUMBER; i ++)
			if ( ! current_step->explored[ i]) {
				Coordinate &&coo = *current_step + Coordinate::moves[ i];
				if ( coo.valid( width, height)) {
					auto it = record.find( coo);
					if ( it == record.end()) {
						shared_ptr< Step> new_step( new Step( coo));
						new_step->from = current_step;
						new_step->explored[ Coordinate::opposite_move( i)] = 1;
						record[ *new_step] = new_step;
						queue.push_back( new_step);
					} else
						it->second->explored[ Coordinate::opposite_move( i)] = 1;
				} // if moves[i] valid
			} // if moves[i] not taken yet

		record.erase( *current_step);
	} // while searching

#ifdef DEBUG_MAP
	cout << "--------------------------------------------------------" << endl;
	Coordinate coo;
	for ( coo.line = 0; coo.line < int(height); coo.line ++) {
		cout << '|';
		for ( coo.column = 0; coo.column < int(width); coo.column ++)
			if ( target == coo)
				cout << 'T';
			else if ( start == coo)
				cout << 'S';
			else if ( record.find( coo) != record.end())
				cout << '#';
			else
				cout << ' ';
		cout << '|' << endl;
	}
	cout << "--------------------------------------------------------" << endl;
#endif

	return answer;

}

void print_step( shared_ptr< Step> &step, unsigned count = 0)
{
	if ( step) {
		print_step( step->from, count + 1);
		cout << "( " << step->line << " , " << step->column << " )" << endl;
	} else
		cout << count - 1 << " step(s) total." << endl;
}

int main()
{
	size_t width, height;
	cin >> height >> width;
	Coordinate start, target;
	cin >> start.line >> start.column;
	cin >> target.line >> target.column;
	
	shared_ptr< Step> solution = search( width, height, start, target);

	if ( solution)
		print_step( solution);
	else
		cout << "NO SOLUTION FOUND !!!" << endl;

	cout << "instant count : " << Coordinate::instant_count << endl;
	cout << "max count     : " << Coordinate::instant_max_count << endl;

	return 0;
}

