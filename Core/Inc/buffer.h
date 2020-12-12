/*
 * buffer.h
 *
 *  Created on: Dec 12, 2020
 *      Author: vincent
 */

#ifndef INC_BUFFER_H_
#define INC_BUFFER_H_

#include <array>

namespace TalkBox
{

template<typename T, int capacity>
class Buffer
{
private:
	std::array<T, capacity> _data;
	int _size;
public:
	Buffer();

	int  Size() const               { return _size;    }
	void Size(int size)             { _size = size;    }
	int  Capacity() const           { return capacity; }
	std::array<T, capacity>& Data() { return _data;    }
};

template<typename T, int capacity>
Buffer<T, capacity>::Buffer()
	: _data()
	, _size(0) {};


} // namespace TalkBox



#endif /* INC_BUFFER_H_ */
