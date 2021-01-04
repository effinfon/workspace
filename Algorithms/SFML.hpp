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
#include <filesystem>

/// TD
/*
    your own Circle type made from many radially placed triangles (multi-threading maybe ?)
    networking: open sockets, communicate with other programs on the machine through their sockets, open
        // a listening port, broadcast through UDP to everything local, etc.
    crawler
    2Dim state-spaces -> (pixels ->) image
    3Dim state-spaces -> (voxels -> projection ->) image
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

    void FindFile(const char * pattern, const char * search_location) {

    }

    void RenderImageFile(sf::RenderWindow* window, std::string file_pathname) {
        sf::Texture texture;
        if(!texture.loadFromFile(file_pathname)) {
            printf("Error loading this file. Does it exist or is it too big to fit in RAM memory ? Or is access to it blocked ?\n");
        }

            // (*?) likely used for loading from an image / texture atlas (!?)
        sf::Texture cropTexture;    // (*?) the IntRect() will have a ~ "pattern generating function"
            // that fits the texture atlas beiong read from
        if(!texture.loadFromFile(file_pathname, sf::IntRect(0, 0, 30, 30))) { ; }

        sf::Texture empty_texture;
        empty_texture.create(200, 200);

        // ... there's some more about textures, but not now

        sf::Sprite sprite;
        sprite.setTexture(texture);
        window->draw(sprite);
    }
};


void GraphicsMain() {
    sf::RenderWindow window {sf::VideoMode(1200, 800), "Title"};
    sf::CircleShape circle(300.f);
    circle.setFillColor(sf::Color::Green);

    std::string file_pathname {"image.png"};

    sf::Texture texture;
    if(!texture.loadFromFile(file_pathname)) {
        printf("Error loading this file. Does it exist or is it too big to fit in RAM memory ? Or is access to it blocked ?\n");
    }

        // (*?) likely used for loading from an image / texture atlas (!?)
    sf::Texture cropTexture;    // (*?) the IntRect() will have a ~ "pattern generating function"
        // that fits the texture atlas beiong read from
    if(!cropTexture.loadFromFile(file_pathname, sf::IntRect(0, 0, 30, 30))) { ; }
//
    sf::Texture empty_texture;
    empty_texture.create(200, 200);

    // ... there's some more about textures, but not now

    sf::Sprite sprite;
    sprite.setTexture(texture);

    while(window.isOpen()) {
        sf::Event event;

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
                return;
            }
        }

        window.clear();
        window.draw(sprite);
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
