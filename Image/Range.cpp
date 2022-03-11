#include "Range.hpp"
#include <limits>
Range::Range() : _start(0), _end(0) {}

Range::Range(int _start, int _end) {
    if (_start < 0 || _start >= _end) {
        this->_start = this->_end = 0;
    } else {
        this->_start = _start;
        this->_end = _end;
    }
}

int Range::start() const {
    return _start;
}

int Range::end() const {
    return _end;
}

bool Range::empty() const {
    return (_end - _start) == 0;
}

int Range::size() const {
    return (_end - _start);
}

Range Range::all() {
    return {0, std::numeric_limits<int>::max()};
}





