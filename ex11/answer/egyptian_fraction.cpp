#include <iostream>
#include <vector>

using namespace std;

unsigned const MAX_RESULT_SIZE = 50;

class fraction {
	private:
		unsigned _upper, _lower;
		unsigned _gcd( unsigned a, unsigned b)
		{
			if ( b)
				return _gcd( b, a % b);
			return a;
		}
		void _check_gcd()
		{
			unsigned gcd = _gcd( upper, lower);
			if ( gcd) {
				_upper /= gcd;
				_lower /= gcd;
			}
		}
	public:
		unsigned const &upper, &lower;
		fraction( unsigned upper = 0, unsigned lower = 0)
			: _upper( upper), _lower( lower),
				upper( _upper), lower( _lower)
		{
			_check_gcd();
		}
		fraction( fraction const &frac)
			: _upper( frac.upper), _lower( frac.lower),
				upper( _upper), lower( _lower)
		{
			_check_gcd();
		}

		fraction &operator=( fraction const &frac)
		{
			_upper = frac.upper;
			_lower = frac.lower;
			return *this;
		}

		bool operator<=( fraction const &frac) const
		{
			return upper * frac.lower <= lower * frac.upper;
		}

		bool operator==( fraction const &frac) const
		{
			return upper * frac.lower == lower * frac.upper;
		}

		fraction operator-( fraction const &frac) const
		{
			unsigned upper = this->upper * frac.lower
						- this->lower * frac.upper;
			unsigned lower = this->lower * frac.lower;
			return fraction( upper, lower);
		}
};

ostream &operator<<( ostream &os, fraction const &frac)
{
	os << frac.upper << '/' << frac.lower;
	return os;
}

// max_lower limits maximal lower number search() can try for current fraction:
bool search( fraction const &target, unsigned size, vector< fraction> &answer, unsigned min_lower)
{
	if ( size == 1) {
		if ( target.upper == 1 && target.lower > min_lower) {
			answer.push_back( target);
			return true;
		}
	} else {
		/* fraction must be bigger than target / size, a.k.a. target.upper/(target.lower * size)
		 * and also must be small than 1/min_lower, to avoid duplicate former fractions:
		 */
		for ( unsigned lower = target.lower * size / target.upper; lower > min_lower; lower --) {
			fraction frac( 1, lower);
			if ( frac <= target) {
				answer.push_back( frac);
				if ( search( target - frac, size - 1, answer, lower))
					return true;
				answer.pop_back();
			}
		}
	}
	return false;
}

int main()
{
	unsigned upper, lower;
	cin >> upper >> lower;
	fraction target( upper, lower);

	vector< fraction> answer;
	for ( unsigned size = 1; size <= MAX_RESULT_SIZE; size ++)
		// try to divide target with size number of fractions:
		if ( search( target, size, answer, 0))
			break;

	if ( answer.size()) {
		vector< fraction>::iterator it = answer.begin();
		cout << upper << '/' << lower << " = " << *it;
		for ( ++ it; it != answer.end(); ++ it)
			cout << " + " << *it;
		cout << endl;
	} else
		cout << "Sorry." << endl;

	return 0;
}

