#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>
#include <glog/logging.h>
#include <argparse/argparse.hpp>

#include "graphics/window.hpp"

void initLogging(bool debug) {
    FLAGS_log_dir = "./logs/";
    if (debug) {
        FLAGS_log_dir = "../logs/";
        FLAGS_alsologtostderr = true;
    }
    google::InitGoogleLogging("ascii_presentations");
}

YAML::Node loadConfig(std::string path) {
    YAML::Node config = YAML::LoadFile(path);
    if (!config)
        LOG(FATAL) << "Unable to read or parse file \"" << path << "\"";
    LOG(INFO) << "Successfully parsed \"" << path << "\"";
    return config;
}

int main(int argc, char* argv[]) {
    argparse::ArgumentParser program(argv[0]);
    program.add_argument("--debug")
        .default_value(false)
        .implicit_value(true);
    try {
        program.parse_args(argc, argv);
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        exit(1);
    }

    initLogging(program.get<bool>("--debug"));

    YAML::Node config = loadConfig("data/config.yaml");
    Graphics::Window* window = new Graphics::Window(config);
    window->debug = program.get<bool>("--debug");
    LOG(INFO) << "Successfully initialized window";

    while (true) {
        window->update();
    }
}
