#include<sstream>
#include<vector>
#include<string>
#include<map>
#include<math.h>
#include"utils/stringutils.cpp"

struct Point3D {
    int x, y, z;
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
        std::map<Point3D, std::map<Point3D, long>> distances;

        cout << "distance between "
            << toString(points[0]) << " and "
            << toString(points[1]) << " is "
            << std::to_string(distance(points[0], points[1]))
            << endl;

        return this;
    }
};