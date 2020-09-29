#pragma once
#include <vector>
#include <iostream>


namespace task {

    std::vector<double> operator+ (const std::vector<double>& a, const std::vector<double>& b) {
        std::vector<double> c;

        for (size_t i = 0; i < a.size(); ++ i) {
            c.push_back(a[i] + b[i]);
        }

        return c;
    }

    std::vector<double> operator+ (const std::vector<double>& a) {
        std::vector<double> c;
        for (size_t i = 0; i < a.size(); ++ i) {
            c[i] = a[i];
        }
        return c;
    }

    std::vector<double> operator- (const std::vector<double>& a) {
        std::vector<double> c;
        for (size_t i = 0; i < a.size(); ++ i) {
            c[i] = -a[i];
        }
        return c;
    }

    std::vector<double> operator- (const std::vector<double>& a, const std::vector<double>& b) {
        std::vector<double> c;

        for (size_t i = 0; i < a.size(); ++ i) {
            c.push_back(a[i] - b[i]);
        }

        return c;
    }

    double operator* (const std::vector<double>& a, const std::vector<double>& b) {
        double c = 0;

        for (size_t i = 0; i < a.size(); ++ i) {
            c += a[i] * b[i];
        }

        return c;
    }

    double crossHelper(const double& a1, const double& a2, const double& b1, const double& b2) {
        return a1 * b2 - a2 * b1;
    }

    std::vector<double> operator% (const std::vector<double>& a, const std::vector<double>& b) {
        std::vector<double> c;

        c.push_back(crossHelper(a[1], a[2], b[1], b[2]));
        c.push_back(-1 * crossHelper(a[0], a[2], b[0], b[2]));
        c.push_back(crossHelper(a[0], a[1], b[0], b[1]));

        return c;
    }

    bool operator|| (const std::vector<double>& a, const std::vector<double>& b) {
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

    bool operator&& (const std::vector<double>& a, const std::vector<double>& b) {
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

    std::vector<double> operator>> (std::istream &input, std::vector<double>& c) {
        double temp;
        int len;

        input >> len;

        for (int i = 0; i < len; ++ i) {
            input >> temp;
            c.push_back(temp);
        }
    }

    std::vector<double> operator<< (std::ostream &output, const std::vector<double>& a) {
        for (int i = 0; i < a.size(); ++ i) {
            output << a[i] << " ";
        }
        output << std::endl;
    }

    std::vector<double> reverse(std::vector<double>& a) {
        int len = a.size();
        int mid = len / 2;
        double temp;

        for (int i = 0; i < mid; ++ i) {
            temp = a[i];
            a[i] = a[len - i];
            a[len - i] = temp;
        }
    }

    std::vector<int> operator| (const std::vector<int>& a, const std::vector<int>& b) {
        std::vector<int> c;

        for (int i = 0; i < a.size(); ++ i) {
            c.push_back(a[i] | b[i]);
        }
        return c;
    }

    std::vector<int> operator& (const std::vector<int>& a, const std::vector<int>& b) {
        std::vector<int> c;

        for (int i = 0; i < a.size(); ++ i) {
            c.push_back(a[i] & b[i]);
        }
        return c;
    }
}  // namespace task
