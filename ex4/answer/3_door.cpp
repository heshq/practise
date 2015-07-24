#include <iostream>
#include <iomanip>	// for setprecision()
#include <string>
#include <cstdlib>	// for rand()
#include <ctime>	// for time() as rand seed
#include <vector>
#include <algorithm>	// for find()

using namespace std;

unsigned const EXAM_ROUNDS = 1000000;

class RandomChoice {
	private:
		vector< int> _candidates;
	public:
		RandomChoice( int from, int to)
		{
			if ( from > to) {
				int tmp = from;
				from = to;
				to = tmp;
			}
			for ( int i = from; i <= to; i ++)
				_candidates.push_back( i);
		}
		RandomChoice &exclude( int x)
		{
			vector< int>::iterator it = find(
						_candidates.begin(),
						_candidates.end(),
						x
					);
			if ( it != _candidates.end())
				_candidates.erase( it);
			return *this;
		}
		int choose()
		{
			size_t which = rand() % _candidates.size();
			return _candidates[ which];
		}
};

struct Player {
	virtual string name() const = 0;
	virtual bool will_change() const = 0;
	int first_choice() const {
		return RandomChoice( 1, 3).choose();
	}
};

class Game {
	private:
		Player const &player;
		int _price_is_in;
		int _player_choose, _hoster_opened;
	public:
		Game( Player const &player)
			: player( player)
		{
			_price_is_in = RandomChoice( 1, 3).choose();
		}

		void make_first_choice()
		{
			_player_choose = player.first_choice();
		}

		void hoster_open_one_door()
		{
			_hoster_opened = RandomChoice( 1, 3)
						.exclude( _price_is_in)
						.exclude( _player_choose)
						.choose();
		}

		void give_chance_to_change()
		{
			if ( player.will_change()) {
				_player_choose = RandomChoice( 1, 3)
							.exclude( _player_choose)
							.exclude( _hoster_opened)
							.choose();
			}
		}

		bool win()
		{
			return _price_is_in == _player_choose;
		}
};

struct AlwaysChangePlayer : Player {
	string name() const { return "The player that ALWAYS changes";}
	bool will_change() const { return true;}
};

struct NeverChangePlayer : Player {
	string name() const { return "The player that Never changes";}
	bool will_change() const { return false;}
};

struct RandomPlayer : Player {
	string name() const { return "The player with coin"; }
	bool will_change() const { return rand() & 0x1;}
};

void exam_player( Player const &player)
{
	unsigned win_count = 0;
	for ( unsigned i = 0; i < EXAM_ROUNDS; i ++) {
		Game game( player);
		game.make_first_choice();
		game.hoster_open_one_door();
		game.give_chance_to_change();
		if ( game.win())
			win_count ++;
	}
	float rate = float( win_count) / EXAM_ROUNDS;
	cout << "Result for " << player.name() << " : ";
	cout << fixed << setprecision( 2);
	cout << rate * 100 << "%" << endl;
}

int main()
{
	srand( time( NULL));
	exam_player( AlwaysChangePlayer());
	exam_player( NeverChangePlayer());
	exam_player( RandomPlayer());
	return 0;
}

