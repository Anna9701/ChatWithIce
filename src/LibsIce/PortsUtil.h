#ifndef PORTS_UTIL_H
    #define PORTS_UTIL_H

    #include <random>
    using namespace std;

    namespace LibsIce {
        class PortsUtil {
            public:
                inline int getServerPort() const {
                    return SERVER_PORT_NUMBER;
                }

                inline int getRandomPort() const {
                    random_device rseed;
                    mt19937 randomGenerator(rseed());
                    uniform_int_distribution<> distribution(MIN_PORT_NUMBER, MAX_PORT_NUMBER);
                    return distribution(randomGenerator);
                }
            private:
                static const unsigned int RANGE = 40000;
                static const unsigned int SERVER_PORT_NUMBER = 10000;
                static const unsigned int MIN_PORT_NUMBER = SERVER_PORT_NUMBER + 1;
                static const unsigned int MAX_PORT_NUMBER = MIN_PORT_NUMBER + RANGE;
        };
    }
#endif