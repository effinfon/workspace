#ifndef SFML_HPP_INCLUDED
#define SFML_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <string>
#include <algorithm>

/// TD
/*
    your own Circle type made from many radially placed triangles (multi-threading maybe ?)
    networking: open sockets, communicate with other programs on the machine through their sockets, open
        // a listening port, broadcast through UDP to everything local, etc.
    crawl
*/

namespace SFML {

/// Utilitaries
std::string UintToString(uint8_t num) {
    std::string result {};

    while(num) {
        result += '0' + num% 10;
        num /= 10;
    }

    std::reverse(result.begin(), result.end());

    return result;
}

namespace Network {
    void SocketTCP() {
    uint8_t ipv4_1 = 127;   // host ip address to conenct to
    uint8_t ipv4_2 = 0;
    uint8_t ipv4_3 = 0;
    uint8_t ipv4_4 = 1;
    uint16_t port = 53000;  // port to connect to on remote machine; only if remote machine accepts connections on this port

    sf::IpAddress address;  // (*?) can be: URL, IP address, "network host name"

    std::string ip_address = UintToString(ipv4_1) + '.' + UintToString(ipv4_2) + '.'+ UintToString(ipv4_3) + '.'+ UintToString(ipv4_4);
    printf("Trying to connect TCP socket.\n");

    sf::Time timeout = sf::seconds(2.0f);
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect(ip_address, 53000);   // (*?) is this async or blocking (?)
    status = socket.connect(ip_address, 53000, timeout);

    printf("Attempt finished. Reporting status...\n");

    if(status != sf::Socket::Done) {
        printf("Error connecting to %u.%u.%u.%u:%u\n", ipv4_1, ipv4_2, ipv4_3, ipv4_4, port);
    }
}
};


namespace Graphics {
    struct Circle {
        uint64_t fn {15};   // (*?) ~ OpenSCAD
        float diameter {100.0};
        float* vertices {new float[2 * fn]};

        Circle() {
            // roots of 1
        }
        Circle(float diameter) {
            // ..
        }
    };
    struct Ellipse {
    uint64_t fn {15};
    float* vertices {new float[2 * fn]};

    Ellipse() {
        // formula for ellipse, sample
    }
    Ellipse(float a, float b) {
        float& eccentricity = a;    // name aliasing
        float& param2 = b;

        // parametrized ellipse... formula-based extrapolation of vertices
    }
};

    template<uint64_t rows, uint64_t cols>
    void RenderBoolArray(bool array[rows][cols]) {

    }
};


void GraphicsMain() {
    sf::RenderWindow window {sf::VideoMode(400, 400), "Title"};
    sf::CircleShape circle(300.f);
    circle.setFillColor(sf::Color::Green);

    while(window.isOpen()) {
        sf::Event event;

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }

        window.clear();
        window.draw(circle);
        window.display();
    }
}
void NetworkMain() {
    Network::SocketTCP();
}

void main() {
    GraphicsMain();
//    NetworkMain();
}

};

#endif // SFML_HPP_INCLUDED
