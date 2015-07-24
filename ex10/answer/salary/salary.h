#ifndef _SALARY_H
#define _SALARY_H

class Salary {
	private:
		static const int INITIAL_SALARY = 2000;

		/*
		 * array _record used as a complete binary tree with structure like:
		 *                     0			*
		 *           _________/ \__________		*
		 *          1                      2		*
		 *     ____/ \___             ____/ \____	*
		 *    3          4           5           6	*
		 *   / \        / \         / \         / \	*
		 *  7   8      9  10      11   12     13   14	*
		 *                  ... ...			*
		 * every leaf node represents one employee,
		 * so the employee number must be power of 2.
		 * thus the array should have (2 * employee_number - 1) elements,
		 */
		int *_record;
		size_t _size;

		/*
		 * easy to notice, for the complete binary tree above,
		 * we can locate any node by:
		 */
		inline static size_t _parent( size_t idx) { return ( idx - 1) / 2;}
		inline static size_t _left_child( size_t idx) { return idx * 2 + 1;}
		inline static size_t _right_child( size_t idx) { return idx * 2 + 2;}

		// we also able to determine if one node is a leaf node:
		inline bool _is_leaf( size_t idx) { return idx >= _size - 1;}

		/* now we treat every node in _record as a segment of range.
		 * each leaf node stands for a segment with only 1 employee it
		 * represents.
		 * other node stands for a segment it's 2 children combine.
		 */
		struct NodeInfo {
			size_t idx;
			size_t segment_begin;
			size_t segment_end;
			inline size_t middle()
			{
				return ( segment_begin + segment_end) / 2;
			}
			inline NodeInfo left_child()
			{
				NodeInfo child = {
					_left_child( idx),
					segment_begin,
					middle()
				};
				return child;
			}
			inline NodeInfo right_child()
			{
				NodeInfo child = {
					_right_child( idx),
					middle() + 1,
					segment_end
				};
				return child;
			}
			inline bool is_leaf()
			{
				return segment_begin == segment_end;
			}
		};
		// obviously, the root node stands for the whole range of employees:
		inline NodeInfo _root()
		{
			NodeInfo root = {
				0,	// idx
				0,	// segment_begin
				size - 1// segment_end
			};
			return root;
		}
		void _rise( NodeInfo &node, size_t from, size_t to, int how_much);

	public:
		size_t const &size;

		Salary( size_t max_employee_id = 100000000);
		~Salary();

		void rise( size_t from, size_t to, int how_much);

		// for law difficulties, salary drop has been forbidden:
		// drop( size_t from, size_t to, int how_mush);

		int query( size_t id);
};


#endif

