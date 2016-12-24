//
// Created by prith on 12/22/2016.
//

#ifndef ANDROIDREMOTECONTROL_HELPER_H
#define ANDROIDREMOTECONTROL_HELPER_H

#include <string>
#include <sstream>

namespace Helper {
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#define MIN(a,b) (((a) > (b)) ? (b) : (a))

    template<typename T>
    std::string to_string(T value) {
        std::ostringstream os;
        os << value;
        return os.str();
    }

    int to_int(const std::string &str) {
        std::stringstream ss(str);
        int N;
        ss << str;
        ss >> N;
        return N;
    }
}

#endif //ANDROIDREMOTECONTROL_HELPER_H
