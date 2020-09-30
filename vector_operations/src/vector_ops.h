#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>


namespace task {
    
    double round_up(double value, int decimal_places) {
        const double multiplier = std::pow(10.0, decimal_places);
        return std::ceil(value * multiplier) / multiplier;
    }
    
    double vector_len(const std::vector<double>& a) {
        double len = 0;
        
        for (size_t i = 0; i < a.size(); ++ i) {
            len += a[i] * a[i];
        }
        return sqrt(len);
    }
    
    double crossHelper(const double& a1, const double& a2, const double& b1, const double& b2) {
        return a1 * b2 - a2 * b1;
    }

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
            c.push_back(a[i]);
        }

        return c;
    }

    std::vector<double> operator- (const std::vector<double>& a) {
        std::vector<double> c;
        for (size_t i = 0; i < a.size(); ++ i) {
            c.push_back(-a[i]);
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

    

    std::vector<double> operator% (const std::vector<double>& a, const std::vector<double>& b) {
        std::vector<double> c;

        c.push_back(crossHelper(a[1], a[2], b[1], b[2]));
        c.push_back(-1 * crossHelper(a[0], a[2], b[0], b[2]));
        c.push_back(crossHelper(a[0], a[1], b[0], b[1]));

        return c;
    }
    

    bool operator|| (const std::vector<double>& a, const std::vector<double>& b) {
        if (abs(round_up(a * b, 6)) == abs(round_up(vector_len(a) * vector_len(b), 6)))
            return true;
        return false;
    }

    bool operator&& (const std::vector<double>& a, const std::vector<double>& b) {
        if (round_up(a * b, 6) == round_up(vector_len(a) * vector_len(b), 6))
            return true;
        return false;
        
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

    std::vector<double> operator<< (std::ostream& output, const std::vector<double>& a) {
        for (int i = 0; i < a.size(); ++ i) {
            output << a[i] << " ";
        }
        output << std::endl;
    }

    std::vector<double> reverse(std::vector<double>& a) {
        double temp;
        int j = a.size() - 1;
	    int i = 0;

	    while(i < j) {
		    temp = a[i];
		    a[i] = a[j];
		    a[j] = temp;
		    i++;
		    j--;
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
