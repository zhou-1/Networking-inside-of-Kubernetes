#include "JsonParsing.h"

using json = nlohmann::json;
using std::string;
namespace niok {
namespace log {
/*
    Still need to implement accurate timestamping for keys
*/
JsonParsing::JsonParsing(string name) {
    name_ = name;
}

// returns a value from a given key 
string JsonParsing::getValueFromKey(string key) {
    // read in the file
    std::ifstream test(name_);
    std::stringstream buffer;
    buffer << test.rdbuf();

    // make a json object out of the file contents
    // and return the value for the given key
    json j;
    j = json::parse(buffer.str());

    return j[key].dump();
}

// adds a new log with key and value to a file
void JsonParsing::addLogToFile(string key, string value) {

    // read in the file
    std::ifstream test(name_);
    std::stringstream buffer;
    buffer << test.rdbuf();

    // make a json object out of the file contents
    // and append a new key and value
    json j;
    if (!buffer.str().empty()) {
      j = json::parse(buffer.str());
    }

    j[key] = { value };

    // output the appended json object to the file
    std::ofstream log;
    log.open(name_);
    log << j;
    log.close();
}

// prints the contents of a file 
void JsonParsing::printFileContents() {
    string line;
    std::ifstream log (name_);
    json j;

    if (log.is_open()) {
      while (getline (log, line)) {
        std::cout << line << "\n";
      }
      log.close();
    }
}

// creates a new json object with given key and value
json JsonParsing::createNewJson(string key, string val) {

    string newLog;
    json j;
    
    j[key] = { val };

    return j;
}
} // namespace log
} // namespace niok
