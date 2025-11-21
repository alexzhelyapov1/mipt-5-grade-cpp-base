#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <sstream>

class IPv4
{
    std::array<std::uint8_t, 4> data{0, 0, 0, 0};

public:
    IPv4() = default;

    IPv4(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d)
        : data{a, b, c, d}
    {
    }

    IPv4& operator++()
    {
        for (int i = 3; i >= 0; --i)
        {
            if (++data[i] != 0) break;
        }
        return *this;
    }

    IPv4 operator++(int)
    {
        IPv4 temp = *this;
        ++(*this);
        return temp;
    }

    IPv4& operator--()
    {
        for (int i = 3; i >= 0; --i)
        {
            if (data[i]-- != 0) break;
        }
        return *this;
    }

    IPv4 operator--(int)
    {
        IPv4 temp = *this;
        --(*this);
        return temp;
    }

    friend bool operator==(const IPv4& lhs, const IPv4& rhs) { return lhs.data == rhs.data; }
    friend bool operator!=(const IPv4& lhs, const IPv4& rhs) { return lhs.data != rhs.data; }
    friend bool operator< (const IPv4& lhs, const IPv4& rhs) { return lhs.data <  rhs.data; }
    friend bool operator> (const IPv4& lhs, const IPv4& rhs) { return lhs.data >  rhs.data; }
    friend bool operator<=(const IPv4& lhs, const IPv4& rhs) { return lhs.data <= rhs.data; }
    friend bool operator>=(const IPv4& lhs, const IPv4& rhs) { return lhs.data >= rhs.data; }

    friend std::ostream& operator<<(std::ostream& os, const IPv4& ip)
    {
        return os << +ip.data[0] << '.' << +ip.data[1] << '.'
                  << +ip.data[2] << '.' << +ip.data[3];
    }

    friend std::istream& operator>>(std::istream& is, IPv4& ip)
    {
        int a, b, c, d;
        char dot1, dot2, dot3;

        if (is >> a >> dot1 >> b >> dot2 >> c >> dot3 >> d)
        {
            if (dot1 == '.' && dot2 == '.' && dot3 == '.' &&
                a >= 0 && a <= 255 && b >= 0 && b <= 255 &&
                c >= 0 && c <= 255 && d >= 0 && d <= 255)
            {
                ip.data = {
                    static_cast<std::uint8_t>(a), static_cast<std::uint8_t>(b),
                    static_cast<std::uint8_t>(c), static_cast<std::uint8_t>(d)
                };
            }
            else
            {
                is.setstate(std::ios::failbit);
            }
        }
        return is;
    }
};

int main()
{
    IPv4 ip(192, 168, 0, 1);

    std::stringstream ss;
    ss << ip;
    assert(ss.str() == "192.168.0.1");

    IPv4 ip2;
    ss.str("10.0.0.255");
    ss >> ip2;
    assert((ip2 == IPv4(10, 0, 0, 255)));

    ip2++;
    assert((ip2 == IPv4(10, 0, 1, 0)));

    ip2--;
    assert((ip2 == IPv4(10, 0, 0, 255)));

    IPv4 ip3(0, 0, 0, 0);
    ip3--;
    assert((ip3 == IPv4(255, 255, 255, 255)));
    ip3++;
    assert((ip3 == IPv4(0, 0, 0, 0)));

    assert(IPv4(192, 168, 1, 1) > IPv4(192, 168, 0, 1));
    assert(IPv4(127, 0, 0, 1) != IPv4(127, 0, 0, 2));
}