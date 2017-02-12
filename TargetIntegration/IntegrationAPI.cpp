//
// Created by islam on 04.02.17.
//

#include <iostream>

using namespace std;

extern "C" {    // avoid c++ name mangling
    void on_function_call(const char* message) {
        cout << "function call! message: " << message << endl;
    }
}
