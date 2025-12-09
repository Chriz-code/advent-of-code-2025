#ifndef RANGE_H
#define RANGE_H
namespace Utils {
    struct Range {
        long long start;
        long long end;

        bool operator < (const Range& r) {
            return start < r.start;
        }

        bool operator > (const Range& r) {
            return start > r.start;
        }

        bool operator == (const Range& r) {
            return start == r.start && end == r.end;
        }

        bool operator != (const Range& r) {
            return !(start == r.start && end == r.end);
        }
    };
}
#endif