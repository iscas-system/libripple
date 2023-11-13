// Author: Zhen Tang <tangzhen12@otcaix.iscas.ac.cn>
// Affiliation: Institute of Software, Chinese Academy of Sciences

#include "../include/Logger.h"

int main(int argc, char *argv[]) {
    Ripple::Logger::Info("StaticTest::main()", "Hello, world. argc = %d", argc);
    return 0;
}
