#include <iostream>
#include <cmath>
#include <cstdint>
#include <climits>

int integer_log2(int n) {
    if (n <= 0) return -1;
    unsigned int u = static_cast<unsigned int>(n);
    int log = 0;
    while (u > 1) {
        u >>= 1;
        log++;
    }
    return log;
}


union FloatIntUnion {
    float f;
    uint32_t i;
};

int float_log2(float f) {
    if (f < 0 || f == 0) return -1;
    FloatIntUnion u;
    u.f = f;

    if ((u.i & 0x7f800000) == 0x7f800000) {
        return (u.i & 0x007fffff) == 0 ? INT_MAX : INT_MIN; // Log(inf) is inf, Log(NaN) is undefined
    }

    int exponent = (u.i >> 23) & 0xFF;

    if (exponent == 0) {
        if (u.i == 0) return -1;
        uint32_t mantissa = u.i & 0x007FFFFF;
        int log = -127;
        for (int i = 22; i >= 0; --i) {
            if ((mantissa >> i) & 1) {
                log += (i - 23);
                break;
            }
        }
        return log;

    } else {
        // Normalized number
        return exponent - 127;
    }
}

int main() {
    // Test int version
    std::cout << "Integer Log2:" << std::endl;
    std::cout << "log2(1) = " << integer_log2(1) << " (Correct: " << static_cast<int>(std::log2(1)) << ")" << std::endl;
    std::cout << "log2(15) = " << integer_log2(15) << " (Correct: " << static_cast<int>(std::log2(15)) << ")" << std::endl;
    std::cout << "log2(16) = " << integer_log2(16) << " (Correct: " << static_cast<int>(std::log2(16)) << ")" << std::endl;
    std::cout << "log2(17) = " << integer_log2(17) << " (Correct: " << static_cast<int>(std::log2(17)) << ")" << std::endl;
    std::cout << "log2(1024) = " << integer_log2(1024) << " (Correct: " << static_cast<int>(std::log2(1024)) << ")" << std::endl;

    // Test float version
    std::cout << "\nFloat Log2:" << std::endl;
    std::cout << "log2(1.0f) = " << float_log2(1.0f) << " (Correct: " << static_cast<int>(std::log2(1.0f)) << ")" << std::endl;
    std::cout << "log2(15.5f) = " << float_log2(15.5f) << " (Correct: " << static_cast<int>(std::log2(15.5f)) << ")" << std::endl;
    std::cout << "log2(0.1f) = " << float_log2(0.1f) << " (Correct: " << static_cast<int>(std::log2(0.1f)) << ")" << std::endl;
    std::cout << "log2(1024.0f) = " << float_log2(1024.0f) << " (Correct: " << static_cast<int>(std::log2(1024.0f)) << ")" << std::endl;

    // Denormalized
    float denorm = 1.0e-40f;
    std::cout << "log2(" << denorm << ") = " << float_log2(denorm) << " (Correct: " << static_cast<int>(std::log2(denorm)) << ")" << std::endl;

    return 0;
}
