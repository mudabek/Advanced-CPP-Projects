#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <vector>
#include <valarray>
#include <sstream>
#include <cmath>
#include "src/vector_ops.h"

use namespace std;

vector<double> operator+ (const vector<double>& a, const vector<double>& b) {
    vector<double> c;

    for (size_t i = 0; i < a.size(); ++ i) {
        c.push_back(a[i] + b[i]);
    }

    return c;
}

vector<double> operator- (const vector<double>& a, const vector<double>& b) {
    vector<double> c;

    for (size_t i = 0; i < a.size(); ++ i) {
        c.push_back(a[i] - b[i]);
    }

    return c;
}

double operator* (const vector<double>& a, const vector<double>& b) {
    double c = 0;

    for (size_t i = 0; i < a.size(); ++ i) {
        с += a[i] * b[i];
    }

    return c;
}

double crossHelper(const double& a1, const double& a2, const double& b1, const double& b2) {
    return a1 * b2 - a2 * b1;
}

vector<double> operator% (const vector<double>& a, const vector<double>& b) {
    vector<double> c;

    c.push_back(crossHelper(a[1], a[2], b[1], b[2]));
    c.push_back(-1 * crossHelper(a[0], a[2], b[0], b[2]));
    c.push_back(crossHelper(a[0], a[1], b[0], b[1]));

    return c;
}

bool operator|| (const vector<double>& a, const vector<double>& b) {
    double ratio = abs(a[0] / b[0]);
    int cnt = 1;

    while (cnt < a.size()) {
        if (abs(a[cnt] / b[cnt]) != ratio) {
            return false;
        }
        ++ cnt;
    }
    return true;
}

bool operator&& (const vector<double>& a, const vector<double>& b) {
    double ratio = a[0] / b[0];
    int cnt = 1;

    while (cnt < a.size()) {
        if (a[cnt] / b[cnt] != ratio) {
            return false;
        }
        ++ cnt;
    }
    return true;
}

void operator>> () {
    double temp;
    vector<double> c;
    int len;

    cin >> len;

    for (int i = 0; i < len; ++ i) {
        cin >> temp;
        c.push_back(temp);
    }
}

void operator<< (const vector<double>& a) {
    for (int i = 0; i < a.size(); ++ i) {
        cout << a[i] << " ";
    }
    cout << endl;
}

void operator reverse(vector<double>& a) {
    int len = a.size();
    int mid = len / 2;
    double temp;

    for (int i = 0; i < mid; ++ i) {
        temp = a[i];
        a[i] = a[len - i];
        a[len - i] = temp;
    }
}

vector<int> operator| (const vector<int>& a, const vector<int>& b) {
    vector<int> c;

    for (int i = 0; i < a.size(); ++ i) {
        c.push_back(a[i] | b[i]);
    }
    return c;
}

vector<int> operator& (const vector<int>& a, const vector<int>& b) {
    vector<int> c;

    for (int i = 0; i < a.size(); ++ i) {
        c.push_back(a[i] & b[i]);
    }
    return c;
}



int main() {

}

