#include <iostream>
#include <vector>
using namespace std;

struct Point { double x, y; };
struct Triangle { Point p1, p2, p3; };

bool voKrug(const Point& p1, const Point& p2, const Point& p3, const Point& p) {
    double ax = p1.x - p.x, ay = p1.y - p.y;
    double bx = p2.x - p.x, by = p2.y - p.y;
    double cx = p3.x - p.x, cy = p3.y - p.y;
    double det = (ax*ax + ay*ay) * (bx*cy - cx*by) - (bx*bx + by*by) * (ax*cy - cx*ay) + (cx*cx + cy*cy) * (ax*by - bx*ay);
    return det > 0;
}

bool istaTocka(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

bool istoRebro(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
    return (istaTocka(a1,b1) && istaTocka(a2,b2)) || (istaTocka(a1,b2) && istaTocka(a2,b1));
}

int main() {
    vector<Point> points = {{0,0}, {2,0}, {1,2}, {1,1}};
    vector<Triangle> triangulacija;
    triangulacija.push_back({{-100,-100}, {100,-100}, {0,100}});

    for (int i = 0; i < points.size(); i++) {
        Point p = points[i];
        vector<Triangle> triangulacija2;
        vector<pair<Point,Point>> edges;

        for (int j = 0; j < triangulacija.size(); j++) {
            if (voKrug(triangulacija[j].p1, triangulacija[j].p2, triangulacija[j].p3, p)) {
                edges.push_back({triangulacija[j].p1, triangulacija[j].p2});
                edges.push_back({triangulacija[j].p2, triangulacija[j].p3});
                edges.push_back({triangulacija[j].p3, triangulacija[j].p1});
            } else {
                triangulacija2.push_back(triangulacija[j]);
            }
        }

        for (int j=0; j<edges.size(); j++) {
            bool duplicate = false;
            for (int k=0; k<edges.size(); k++) {
                if (j != k && istoRebro(edges[j].first, edges[j].second, edges[k].first, edges[k].second)) {
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate)
                triangulacija2.push_back({edges[j].first, edges[j].second, p});
        }

        triangulacija = triangulacija2;
    }

    Point s1 = {-100,-100}, s2 = {100,-100}, s3 = {0,100};
    vector<Triangle> result;
    for (int i=0;  i<triangulacija.size(); i++) {
        Triangle& t = triangulacija[i];
        if (!istaTocka(t.p1,s1) && !istaTocka(t.p1,s2) && !istaTocka(t.p1,s3) && !istaTocka(t.p2,s1) && !istaTocka(t.p2,s2) && !istaTocka(t.p2,s3) && !istaTocka(t.p3,s1) && !istaTocka(t.p3,s2) && !istaTocka(t.p3,s3)) {
            result.push_back(t);
        }
    }

    cout << "triangulacija: " << result.size() << "\n";
    for (int i = 0; i < result.size(); i++) {
        cout << "T" << i << ": (" << result[i].p1.x << "," << result[i].p1.y << ") (" << result[i].p2.x << "," << result[i].p2.y << ") (" << result[i].p3.x << "," << result[i].p3.y << ")\n";
    }
    return 0;
}