#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
void mul(const array<float,3>& p, const float m[3][3], array<float,3>& r) {
    for (int j=0; j<3; j++) {
        r[j] = 0;
        for (int k=0; k<3; k++) {
           //r[j] += m[j][k] * p[k];
            r[j] += p[k] * m[k][j];

        }
    }
}
array<float,3> rotate(float x, float y, float angle) {
    array<float,3> point = {x, y, 1};
    float mtx[3][3] = {
        {cos(angle), -sin(angle), 0},
        {sin(angle), cos(angle), 0},
        {0, 0, 1}
    };
    array<float,3> result = {0, 0, 0};
    mul(point, mtx, result);
    return result;
}
array<float,3> translate(float x, float y, float edinici_x, float edinici_y) {
    array<float,3> point = {x, y, 1};
    float mtx[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {edinici_x, edinici_y, 1}
    };
    array<float,3> result = {0, 0, 0};
    mul(point, mtx, result);
    return result;
}
array<float,3> scale(float x, float y, float coefficient) {
    array<float,3> point = {x, y, 1};
    float mtx[3][3] = {
        {coefficient, 0, 0},
        {0, coefficient, 0},
        {0, 0, 1}
    };
    array<float,3> result = {0, 0, 0};
    mul(point, mtx, result);
    return result;
}
int main()
{
   /* float koord1 = 1, koord2 = 1;
    auto z = rotate(koord1, koord2, M_PI / 2);
    for (int i=0; i<3; i++) {
        cout << z[i] << " ";
    } */
    vector<int> coord;
    string lajn;
    ifstream fajl("square.obj");
    vector<array<float,3>> teminja;
    if (fajl.is_open()) {
        while (getline(fajl, lajn)) {
                if (lajn.rfind("v ", 0) == 0) {
                    istringstream iss(lajn);
                    char trash;
                    float x,y,z;
                    iss >> trash >> x >> y >> z;
                    teminja.push_back({x,y,z});
                }
            }
        }
    array<float,3> z = rotate(teminja[0][0], teminja[0][1], M_PI/4);
    array<float,3> z1 = translate(z[0], z[1], 2, 0);
    array<float,3> z2 = scale(z1[0], z1[1], 4);
    array<float,3> z_ = rotate(teminja[1][0], teminja[1][1], M_PI/4);
    array<float,3> z1_ = translate(z_[0], z_[1], 2, 0);
    array<float,3> z2_ = scale(z1_[0], z1_[1], 4);
    array<float,3> z__ = rotate(teminja[2][0], teminja[2][1], M_PI/4);
    array<float,3> z1__ = translate(z__[0], z__[1], 2, 0);
    array<float,3> z2__ = scale(z1__[0], z1__[1], 4);
    array<float,3> z___ = rotate(teminja[3][0], teminja[3][1], M_PI/4);
    array<float,3> z1___ = translate(z___[0], z___[1], 2, 0);
    array<float,3> z2___ = scale(z1___[0], z1___[1], 4);
    for (auto& it : z2) {
        cout << it << " ";
    }
    cout << endl;
    for (auto& it : z2_) {
        cout << it << " ";
    }
    cout << endl;
    for (auto& it : z2__) {
        cout << it << " ";
    }
    cout << endl;
    for (auto& it : z2___) {
        cout << it << " ";
    }
    return 0;
}