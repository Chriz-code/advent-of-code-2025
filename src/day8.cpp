#include<sstream>
#include<vector>
#include<string>
#include<map>
#include<math.h>
#include<algorithm>
#include"utils/stringutils.cpp"
#include "utils/filereader.cpp"
#include<set>
#include<unordered_set>


struct Point3D {
    int x, y, z;
    bool operator == (const Point3D& other) {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator < (const Point3D& other) const {
        return std::tie(x, y, z) < std::tie(other.x, other.y, other.z);
    }
};

struct Line3D {
    Point3D point1;
    Point3D point2;
    long dist;

    bool operator == (const Line3D& other) {
        return (point1 == other.point1 && point2 == other.point2)
            || (point2 == other.point1 && point1 == other.point2);
    }
    bool operator < (const Line3D& other) const {
        return dist < other.dist;
    }
};

typedef std::vector<Point3D> Circut;
typedef std::map<Point3D, std::map<Point3D, long>> PointDistances;

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
        return result;
    }

    long distance(Point3D& a, Point3D& b) {
        return sqrtl(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
    }

    long distance(Line3D& line) {
        return distance(line.point1, line.point2);
    }

    std::string toString(Point3D p) {
        return "(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ", " + std::to_string(p.z) + ")";
    }

    bool hasKey(PointDistances& distances, const Point3D& a, const Point3D& b) {
        return distances.find(a) != distances.end() && distances[a].find(b) != distances[a].end();
    }

    std::vector<Line3D> calculateDistances(std::vector<Point3D>& points) {
        std::set<Line3D> distances;
        for (Point3D point1 : points) {
            for (Point3D point2 : points) {
                if (point1 == point2) {
                    continue;
                }
                Line3D line = Line3D({ point1, point2, 0 });
                if (distances.find(line) != distances.end()) {
                    cout << "dupe" << endl;
                    continue;
                }
                line.dist = distance(line);
                distances.insert(line);
            }
            cout << ".";
        }
        cout << endl << "transforming" << endl;;
        return std::vector<Line3D>(distances.begin(), distances.end());
    }

    std::vector<Circut> createCircuts(std::vector<Line3D>& distances, int noConnections = 10) {
        std::sort(distances.begin(), distances.end(), [](Line3D const& lhs, Line3D const& rhs) {
            return lhs.dist < rhs.dist;
        });

        // create circuts, connect the 10 shortest
        std::vector<Circut> circuts;
        for (int i = 0; i < noConnections; ++i) {
            Line3D line = distances[i];

            bool hasPoint1 = false;
            bool hasPoint2 = false;
            auto hasEitherJunction = std::find_if(
                circuts.begin(),
                circuts.end(),
                [&line, &hasPoint1, &hasPoint2](auto& circut) {
                hasPoint1 = std::find(circut.begin(), circut.end(), line.point1) != circut.end();
                hasPoint2 = std::find(circut.begin(), circut.end(), line.point2) != circut.end();
                return hasPoint1 || hasPoint2;
            });
            int circutIdx = hasEitherJunction - circuts.begin();
            if (hasEitherJunction == circuts.end()) {
                circuts.push_back(Circut({ line.point1, line.point2 }));
                cout << ".";
                continue;
            }
            if (hasPoint1) {
                circuts[circutIdx].push_back(line.point2);
                cout << ".";
                continue;
            }
            if (hasPoint2) {
                circuts[circutIdx].push_back(line.point1);
                cout << ".";
                continue;
            }
        }

        cout << endl;
        return circuts;
    }

    long long resultValue(std::vector<Circut>& circuts, int length = 3) {
        std:set<long> circutSizes;
        for (auto& circut : circuts) {
            circutSizes.insert(circut.size());
        }
        std::vector<long> orderedCircutSizes(circutSizes.begin(), circutSizes.end());
        std::sort(orderedCircutSizes.begin(), orderedCircutSizes.end(), greater<long>());

        long long sum = 1;
        for (int i = 0; i < length; i++) {
            sum *= orderedCircutSizes[i];
        }

        return sum;
    }

public:
    Day8* part1Test() {
        std::stringstream stream(TEST_INPUT);
        std::vector<Point3D> points = parseToPoints(stream);
        cout << "Points parsed: " << points.size() << endl;
        std::vector<Line3D> distances = calculateDistances(points);
        cout << "Distances calculated: " << distances.size() << endl;
        std::vector<Circut> circuts = createCircuts(distances);

        long long sum = resultValue(circuts);

        cout << "Thats a lot of Mario Kart: " << sum << endl;
        return this;
    }
    // 18699743462400000 -- too high :(
    // 24 -- not right :(
    // 14300 -- too low
    Day8* part1() {
        FileReader reader("inputs/day8.txt");
        stringstream stream = reader.toStringStream();
        std::vector<Point3D> points = parseToPoints(stream);
        cout << "Points parsed: " << points.size() << endl;
        std::vector<Line3D> distances = calculateDistances(points);
        cout << "Distances calculated: " << distances.size() << endl;
        std::vector<Circut> circuts = createCircuts(distances, 1000);

        long long sum = resultValue(circuts);

        cout << "Thats a lot of Mario Kart: " << sum << endl;

        return this;
    }
};