#include<sstream>
#include<vector>
#include<string>
#include<map>
#include<math.h>
#include<algorithm>
#include"utils/stringutils.cpp"

struct Point3D {
    int x, y, z;
    bool operator == (Point3D const& other) {
        return x == other.x && y == other.y && z == other.z;
    }
};

struct Line3D {
    Point3D point1;
    Point3D point2;
    long dist;
};

class Day8 {
private:
    const char* TEST_INPUT =
        "162,817,812\n"
        "57,618,57\n"
        "906,360,560\n"
        "592,479,940\n"
        "352,342,300\n"
        "466,668,158\n"
        "542,29,236\n"
        "431,825,988\n"
        "739,650,466\n"
        "52,470,668\n"
        "216,146,977\n"
        "819,987,18\n"
        "117,168,530\n"
        "805,96,715\n"
        "346,949,466\n"
        "970,615,88\n"
        "941,993,340\n"
        "862,61,35\n"
        "984,92,344\n"
        "425,690,689";

    std::vector<Point3D> parseToPoints(std::stringstream& ss) {
        std::vector<Point3D> result;
        std::string line;
        while (getline(ss, line)) {
            std::vector<std::string> points = StringUtils::split(line, ',');
            result.push_back({
                std::stoi(points[0]),
                std::stoi(points[1]),
                std::stoi(points[2])
                });
        }
        for (auto& point : result) {
            cout << toString(point) << endl;
        }
        return result;
    }

    long distance(Point3D a, Point3D b) {
        return sqrtl(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
    }

    std::string toString(Point3D p) {
        return "(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ", " + std::to_string(p.z) + ")";
    }

public:
    Day8* part1Test() {
        std::stringstream ss(TEST_INPUT);
        std::vector<Point3D> points = parseToPoints(ss);
        std::vector<Line3D> distances;

        for (Point3D point1 : points) {
            for (Point3D point2 : points) {
                if (point1 == point2) {
                    continue;
                }
                if (std::find_if(distances.begin(), distances.end(), [&point1, &point2](auto& line) {
                    return line.point1 == point2 && line.point2 == point1;
                }) != distances.end()) {
                    continue;
                }
                long dist = distance(point1, point2);
                distances.push_back({ point1, point2, dist });
            }
        }

        std::sort(distances.begin(), distances.end(), [](Line3D const& lhs, Line3D const& rhs) {
            return lhs.dist < rhs.dist;
        });

        for (auto& l : distances) {
            cout << "distance between "
                << toString(l.point1) << " and "
                << toString(l.point2) << " is "
                << std::to_string(l.dist)
                << endl;
        }

        // create circut

        return this;
    }
};