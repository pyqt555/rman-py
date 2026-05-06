#include "rman_mount.hpp"

int main(int argc, char *argv[]) {
    try {
        main_.parse_args(argc, argv);
        main_.run();
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        for (auto const &error : error_stack()) {
            std::cerr << error << std::endl;
        }
        error_stack().clear();
        return EXIT_FAILURE;
    }

    return rman_mount_run();
}