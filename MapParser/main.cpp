#include <iostream>
#include <string>
#include <fstream>
#include <google/protobuf/util/json_util.h>
#include "message_map.pb.h"

void main () {
    std::string mapPath = "test.smap";
    std::fstream fs(mapPath, std::ios::in | std::ios::binary);
    if (fs) {
        std::string line;
        getline(fs, line);

        rbk::protocol::Message_Map map_msg;
        google::protobuf::util::JsonParseOptions json_parse_option;
        json_parse_option.ignore_unknown_fields = true;
        google::protobuf::util::Status parseStatus = google::protobuf::util::JsonStringToMessage(line, &map_msg, json_parse_option);

        if (fs.is_open()) {
            fs.close();
        }

        if (parseStatus.ok()) {
            std::cout << "Parse map " << mapPath << " success" << std::endl;
            std::cout << "normal point size: " << map_msg.normal_pos_list_size() << ", advanced point size: " << map_msg.advanced_point_list_size() << std::endl;
        }
        else {
            std::cout << "Parse map " << mapPath << " error: " << parseStatus.error_message() << std::endl;
        }
    }
    else {
        if (fs.is_open()) {
            fs.close();
        }
        std::cout << "Can not open map: " << mapPath << std::endl;
    }
}
