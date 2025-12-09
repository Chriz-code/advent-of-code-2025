#include "utils/filereader.cpp"
#include "utils/stringutils.cpp"
#include "utils/disjointsetunion.cpp"
#include <iostream>
#include <vector>
#include <map>

namespace Day8 {
    //Love my guy kruskal he so smart
    class SolutionKruskal {
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

        std::vector<Utils::Point3D> parseToPoints(std::stringstream& stream) {
            std::vector<Utils::Point3D> result;
            std::string line;
            int id = 0;
            while (getline(stream, line)) {
                std::vector<std::string> points = Utils::StringUtils::split(line, ',');
                result.push_back({
                    id,
                    std::stol(points[0]),
                    std::stol(points[1]),
                    std::stol(points[2]),
                    });
                id++;
            }
            return result;
        }

        long distance(Utils::Point3D& a, Utils::Point3D& b) {
            return sqrtl(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
        }

        Utils::DSU kruskal(std::vector<Utils::Point3D>& points, int limit) {
            std::vector<Utils::Edge> edges;

            for (int i = 0; i < points.size(); ++i) {
                for (int j = i + 1; j < points.size(); ++j) {
                    double dist = distance(points[i], points[j]);
                    edges.push_back({ points[i].id, points[j].id, dist });
                }
            }

            sort(edges.begin(), edges.end());

            Utils::DSU dsu(points.size());

            int edgesCount = 0;
            for (auto& edge : edges) {
                if (dsu.find(edge.src) != dsu.find(edge.dest)) {
                    dsu.unite(edge.src, edge.dest);
                }
                edgesCount++;
                if (edgesCount >= limit) {
                    break;
                }
            }

            return dsu;
        }

        std::vector<int> groupSizes(std::vector<Utils::Point3D>& points, Utils::DSU& dsu) {
            std::map<int, std::vector<int>> groups;

            for (auto& point : points) {
                int id = dsu.find(point.id);
                groups[id].push_back(point.id);
            }

            std::vector<int> result;
            for (auto& pair : groups) {
                result.push_back(pair.second.size());
            }

            std::sort(result.begin(), result.end(), std::greater<int>());

            return result;
        }

        Utils::Edge kruskalReturnLastEdge(std::vector<Utils::Point3D>& points) {
            std::vector<Utils::Edge> edges;

            for (int i = 0; i < points.size(); ++i) {
                for (int j = i + 1; j < points.size(); ++j) {
                    double dist = distance(points[i], points[j]);
                    edges.push_back({ points[i].id, points[j].id,  dist });
                }
            }

            sort(edges.begin(), edges.end());

            Utils::DSU dsu(points.size());

            Utils::Edge lastEdge = { -1, -1, -1.0 };
            for (auto& edge : edges) {

                if (dsu.find(edge.src) != dsu.find(edge.dest)) {

                    if (dsu.getNumComponents() == 2) {
                        lastEdge = edge;
                    }
                    dsu.unite(edge.src, edge.dest);

                    if (dsu.getNumComponents() == 1) {
                        break;
                    }
                }
            }

            return lastEdge;
        }

        void printGroups(std::vector<int> groups) {
            for (auto& group : groups) {
                if (group == 1) {
                    continue;
                }
                std::cout << group << std::endl;
            }
        }

    public:
        SolutionKruskal* part1Test() {
            std::stringstream stream(TEST_INPUT);
            std::vector<Utils::Point3D> points = parseToPoints(stream);

            Utils::DSU finalDSU = kruskal(points, 10);

            std::vector<int> groups = groupSizes(points, finalDSU);
            printGroups(groups);

            return this;
        }

        SolutionKruskal* part1() {
            Utils::FileReader reader("inputs/day8.txt");
            std::stringstream stream = reader.toStringStream();
            std::vector<Utils::Point3D> points = parseToPoints(stream);

            Utils::DSU finalDSU = kruskal(points, 1000);

            std::vector<int> groups = groupSizes(points, finalDSU);

            std::cout << "Thats a lot of Mario Kart: " << (groups[0] * groups[1] * groups[2]) << std::endl;

            return this;
        }

        SolutionKruskal* part2Test() {
            std::stringstream stream(TEST_INPUT);
            std::vector<Utils::Point3D> points = parseToPoints(stream);

            Utils::Edge finalEdge = kruskalReturnLastEdge(points);

            Utils::Point3D src = points[finalEdge.src];
            Utils::Point3D dest = points[finalEdge.dest];
            std::cout << "The last edge added" << std::endl;
            std::cout << "Point: " << finalEdge.src << " " << Utils::Point3D::toString(src)
                << " and Point: " << finalEdge.dest << " " << Utils::Point3D::toString(dest)
                << std::endl;
            std::cout << "Thats a lot of Mario Kart: " << (src.x * dest.x) << std::endl;

            return this;
        }

        SolutionKruskal* part2() {
            Utils::FileReader reader("inputs/day8.txt");
            std::stringstream stream = reader.toStringStream();
            std::vector<Utils::Point3D> points = parseToPoints(stream);

            Utils::Edge finalEdge = kruskalReturnLastEdge(points);

            Utils::Point3D src = points[finalEdge.src];
            Utils::Point3D dest = points[finalEdge.dest];
            std::cout << "Thats a lot of Mario Kart: " << ((long long)src.x * dest.x) << std::endl;

            return this;
        }
    };

}

