#include <deque>
#include <unordered_map>

#include "priority_queue.h"

using namespace std;

class PriorityQueueImpl {
	private:
		struct MapData {
			bool		ready;
			unsigned	priority;
			MapData() {}
			MapData( bool ready, unsigned priority)
				: ready( ready), priority( priority)
			{}
		};
		unordered_map< PID, MapData> _map;
		typedef unordered_map< PID, MapData>::iterator MapIter;

		deque< PID> _queue[ MAX_PRIORITY + 1];

		unsigned _most_priority;

		inline void _set_ready( unsigned priority, PID id)
		{
			_queue[ priority].push_back( id);
			if ( priority > _most_priority)
				_most_priority = priority;
		}

	public:
		PriorityQueueImpl() : _most_priority( 0) {}

		virtual ~PriorityQueueImpl()
		{
		}

		void push( PID id, PSTATE state, unsigned priority)
		{
			if ( state == P_READY)
				_set_ready( priority, id);
			else
				_map[ id] = MapData( false, priority);
		}

		void set_ready( PID id)
		{
			MapIter it( _map.find( id));
			if ( it != _map.end()) {
				_set_ready( it->second.priority, it->first);
				_map.erase( it);
			}
		}

		PID pop()
		{
			PID id = _queue[ _most_priority].front();
			_queue[ _most_priority].pop_front();
			return id;
		}

		bool empty()
		{
			while ( _most_priority && _queue[ _most_priority].empty())
				-- _most_priority;
			return _queue[ _most_priority].empty();
		}
};

PriorityQueue::PriorityQueue()
	: _impl( new PriorityQueueImpl)
{
}

PriorityQueue::~PriorityQueue()
{
	delete _impl;
}

void
PriorityQueue::push( PID id, PSTATE state, unsigned priority)
{
	_impl->push( id, state, priority);
}

void
PriorityQueue::set_ready( PID id)
{
	_impl->set_ready( id);
}

bool
PriorityQueue::empty()
{
	return _impl->empty();
}

PID
PriorityQueue::pop()
{
	return _impl->pop();
}

