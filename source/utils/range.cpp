#ifndef RANGE_H
#define RANGE_H
struct Range
{
    long long start;
    long long end;

    bool operator < (const Range& r) {
        return start < r.start;
    }
};
#endif