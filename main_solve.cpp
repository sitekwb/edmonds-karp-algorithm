#include "Controller.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    try{
        Controller controller;

        if(argc != 2){
            throw invalid_argument("Required one argument. Given "+to_string(argc-1)+".");
        }

        fstream file_stream(argv[1], fstream::in);
        file_stream.exceptions ( ifstream::failbit | ifstream::badbit );

        controller.load_data(file_stream);

        file_stream.close();

        while(controller.exists_augmenting_path()) {
            controller.synchronize_flow_and_graph();
        }

        controller.output_results(cout);
    }
    catch (exception &e) {
        cerr << e.what();
        return -1;
    }

    return 0;
}