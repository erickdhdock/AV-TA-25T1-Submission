#include <iostream>
#include <fstream>
#include <string>

// Question 3: This is an extension task that requires you to decode sensor data from a CAN log file.
// CAN (Controller Area Network) is a communication standard used in automotive applications (including Redback cars)
// to allow communication between sensors and controllers.
//
// Your Task: Using the definition in the Sensors.dbc file, extract the "WheelSpeedRR" values
// from the candump.log file. Parse these values correctly and store them in an output.txt file with the following format:
// (<UNIX_TIME>): <DECODED_VALUE>
// eg:
// (1705638753.913408): 1234.5
// (1705638754.915609): 6789.0
// ...
// The above values are not real numbers; they are only there to show the expected data output format.
// You do not need to use any external libraries. Use the resources below to understand how to extract sensor data.
// Hint: Think about manual bit masking and shifting, data types required,
// what formats are used to represent values, etc.
// Resources:
// https://www.csselectronics.com/pages/can-bus-simple-intro-tutorial
// https://www.csselectronics.com/pages/can-dbc-file-database-intro





// SG_ WheelSpeedRR : 32|16@0+ (0.1,0) [0|0] "km/h" Vector__XXX
// 32 bit, 16 bit length, lil endian, scailing fact=0.1, offset 0

// can id: BO_ 1797 -> 705 (hex)
// ECU_WheelSpeed: 8 Vector__XXX

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>


int main() {
    std::ifstream infile("../Question-3/candump.log");
    std::ofstream outfile("../Question-3/output.txt");
    if (!infile.is_open() || !outfile.is_open()) {
        std::cerr << "gimme permission to file || check file location" << std::endl;
        return 1;
    }




    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        char ch;
        double timestamp;
        std::string bus, can_id, payload;

        // parse and filter
        if (!(iss >> ch >> timestamp >> ch >> bus >> can_id)) continue;  

        // (1705638761.726437) vcan0 705#6B70B3420E47FE20
        // can_id#payload
        size_t hash_pos = can_id.find('#');
        if (hash_pos == std::string::npos) continue;

        std::string hex_id = can_id.substr(0, hash_pos);
        payload = can_id.substr(hash_pos + 1);
        
        // into integer
        int id;
        std::stringstream(hex_id) >> std::hex >> id;

        // 1797=0x705
        if (id == 0x705 && payload.length() >= 10) {
            // Extract bytes 4 and 5 
            std::string byte4 = payload.substr(8, 2); 
            std::string byte5 = payload.substr(10, 2); 


            // to integer 
            int wheel_speed_rr = std::stoi(byte5 + byte4, nullptr, 16);

            // scaling fact = 0.1
            double decoded_value = wheel_speed_rr * 0.1;
            


            // output
            outfile << "(" << std::fixed << std::setprecision(6) << timestamp << "): " << decoded_value << std::endl;
        }
    }

    infile.close();
    outfile.close();
    std::cout << "done!" << std::endl;
    return 0;
}
