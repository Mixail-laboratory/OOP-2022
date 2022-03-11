#ifndef IMAGE_RANGE_HPP
#define IMAGE_RANGE_HPP


class Range {
    int _start, _end;
public:
    Range();

    Range(int _start, int _end);

    [[nodiscard]] int size() const;

    [[nodiscard]] bool empty() const;

    [[nodiscard]] int start() const;

    [[nodiscard]] int end() const;

    static Range all();
};

#endif
