#ifndef CHATNETWORK_HPP_INCLUDED
#define CHATNETWORK_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <vector>
#include <thread>
#include <chrono>

/// -----

#define MAX_RAW_DATA 256 //Max bytes supported on Raw Data mode

/// -----

/// TD
/*
    group chat
    PM chat
    server-bypass chat
*/

namespace Chat {

class Client {
//    uint64_t ID;      // (*?) to be used by a manager -> this attribute only exists if there is a manager, but I'd rather that the ID
                        // exist local to the object... (?), a sort of template programming based on static analysis, and dynamic analysis (!?) possibly
    sf::TcpSocket socket;
    sf::Packet read_packet;
    bool isConnected {true};

    sf::TcpListener listener;   // side-channel for PM; can be turned on/off (?) -> linked to a button event in the GUI
    std::thread listener_thread;
    std::thread autonomous_thread;

public:
    inline static const std::string application_identifier {"chat program"};

public:
    Client() {
        printf("Started client.\n");
    }
        // (*?) due to the ID related discussion, this "forces" one to use virtual functions, because if the Client object is called from inside a ClientManager,
            // the error message will be modified to include the ID of the client, basically resulting in dynamic binding of the function (although, it could also be
            // a dynamic binding of the string variables being used, but nonetheless)
        // (*!?) printf's formatting strings are actually very versatile, because it can be reused with variables (which can change at runtime), yet the strings remain the same
    void Connect(const char * address, uint16_t port) {
        if(socket.connect(address, port) != sf::Socket::Status::Done) { // (*?) I do not know how to compare: (== vs !=) and (probabilistically the == will succeed most of the time
                                                                        // and there should be fewer jumps if the comparator is also correlated to it first ?)
            printf("Error connecting to %s:%u\n", address, port);
        } else {
            isConnected = true;
            printf("Connected successfully to %s:%u\n", address, port);
        }
    }

        // (*?) at the moment it assumes the byte stream is a string stream (!)
    void ReceivePackets(sf::TcpSocket* socket) { // (*?) selectable source ?
        while(true) {
            if(socket->receive(read_packet) == sf::Socket::Status::Done) {
                std::string received {};
                read_packet >> received;

//                std::string received_string; std::string sender_address; unsigned short sender_port;
//                last_packet >> received_string >> sender_address >> sender_port;

                printf("Message: %s", received.c_str());
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }

        // (*?) (i) a send() that can be verified for progress [imagine that it sends to a micro-controller with very bad connection]
        // (ii) error correction codes
        // (iii) hashing of the packet and verification
        // (iv) encryption
    void SendPackets(sf::Packet& packet) {    // arbitrary target
            // (*?) this "strange" expression is but a compact way of conditioning the execution of socket.send(...) by whether
                // packet.getDataSize() > 0 or not, which again, basically checks that there be data to send in the packet, before
                // attempting to send (sending is probably unsafe then ?)
        if(packet.getDataSize() > 0 && socket.send(packet) != sf::Socket::Status::Done) {  // (*?) == seems to have a higher average complexity than interval comparator-property operations such
                                        // as > and <; even != has lower average complexity (due to "early termination")
            printf("Error sending packet ...?(packet ID or ?) to ...?(client ID, address, etc.)\n");
        }
    }
    void PreparePacketSend(void* byte_data, uint64_t size) {    // error correction code overhead, encryption, hashing
    }
    void PreparePacketReceive() {   // repair, decryption, hash verification (maybe even use certificates to verify source), etc.; might even ask for re-transmission
    }

        // (*?) currently, this function blocks the caller, indefinitely; it needs to instead turn itself into a pair of
            // threads, one getting input and sending packets and the other listening on the socket and receiving packets
    void Run() {
//        std::thread reception_thread(&Client::ReceivePackets, this, &socket);    // (*?) what is $this for ? and what's with the strange &Client:ReceivePackets thing ?
        std::thread reception_thread(&Client::ReceivePackets, this, &socket);

        while(true) {
            std::string user_input;
            std::getline(std::cin, user_input);

            sf::Packet reply_packet;
            reply_packet << user_input;
            SendPackets(reply_packet);

            // (*?) this would require that the SendPackets() require an lvalue instead of an rvalue,
                // and the constructor to be directly applicable onto std::string for type-casting (!?)
            // (*?) or could I use "sf::Packet() << user_input" (!?)
//            SendPackets(sf::Packet(user_input));
//            SendPackets(sf::Packet() << user_input);
        }
    }

    void StartListenerOnSideChannel() {}
    void StopListenerOnSideChannel() {}
    std::string GenerateRandomMessage() {
    }
    void StartThreadAutonomousClient(sf::Time interval_between_messages) {
    }
    void StopThreadAutonomousClient() {
    }

    uint16_t* PortScanner() {   // (*?) will find any open ports that respond to the connection request: does this imply
                                // that it's the server for this specific program ? maybe there should be a ~ "application
                                // identification protocol" for this to actually work that way; otherwise, it might find
                                // other progarms' open ports and connect to those...
    }

    void VerifyPortProtocol(uint16_t* ports) {  // this will implement that "app identif. protocol" concept

    }

};

class Server {
    sf::TcpListener listener;
    std::vector<sf::TcpSocket *> clients;

    uint16_t listening_port {2525}; // (*!?) it's fine being local here, but it's still worrying whenever something has to change (!?), so
                                    // a mechanism for better ensuring "consistency" / ~ "soruce code, data integrity" would be prefered
    bool rawMode {false};
public:
    void Init() {
        printf("Chat server constructing.\n");
        if(rawMode) { printf("Warning: raw mode is active.\n"); }

            // (*?) there is again that thing IpAddress::Any; what is that for ?
        if(listener.listen(listening_port) != sf::Socket::Done) {
            printf("Could not start listening on port %u. Is it being used by something else ?\n", listening_port);
        }
    }

    Server() { Init(); }
    Server(uint16_t listening_port) : listening_port(listening_port) { Init(); }
    Server(bool rawMode) : rawMode(rawMode) { Init(); }
    Server(uint16_t listening_port, bool rawMode) : listening_port(listening_port), rawMode(rawMode) { Init(); }

//ServerNetwork::ServerNetwork(unsigned short port, bool rawMode = false) : listen_port(port){
//     logl("Chat Server Started");
//
//     this->rawMode = rawMode;
//     if(rawMode) logl("Warning, raw mode enabled");
//
//     if(listener.listen(listen_port) != sf::Socket::Done){
//          logl("Could not listen");
//     }
//}

    void StartListening();
    void StopListening();
    void SetListeningPort(uint16_t listening_port) {}


//    void ServerNetwork::ConnectClients(std::vector<sf::TcpSocket *> * client_array){
//     while(true){
//          sf::TcpSocket * new_client = new sf::TcpSocket();
//          if(listener.accept(*new_client) == sf::Socket::Done){
//               new_client->setBlocking(false);
//               client_array->push_back(new_client);
//               logl("Added client " << new_client->getRemoteAddress() << ":" << new_client->getRemotePort() << " on slot " << client_array->size());
//          }else{
//               logl("Server listener error, restart the server");
//               delete(new_client);
//               break;
//          }
//     }
//}

    void ConnectClient(sf::TcpSocket* client) {}
    void ConnectClients(std::vector<sf::TcpSocket *> * clients) {  // (*?) this has been designed by the author to be a ~ "thread function" / "co-function" (~!= "co-routine")
        while(true) {
            sf::TcpSocket * new_client = new sf::TcpSocket();
            if(listener.accept(*new_client) == sf::Socket::Status::Done) {
                new_client->setBlocking(false); // (*?) whether it's blocking or whether it's not blocking, what changes ? the communication to the socket ?
                // (*?) generate an id or something, maybe the position in the vector
                clients->push_back(new_client);
                printf("New client connected: %u id, %s address, etc.\n", clients->size(), new_client->getRemoteAddress());
            }
        }
    }

    void DisconnectClient(sf::TcpSocket* client) {}
    void DisconnectClients(std::vector<sf::TcpSocket *> clients) {}

    void ReceivePacket(sf::TcpSocket* client, uint64_t size) {  // (*?) size implies bytes
                                                                // effectively, an encoded byte stream (?)
    }
    void ReceiveRawData(sf::TcpSocket* client, uint64_t size) { // UDP (?) or just byte stream ?
    }

    void BroadcastPacket(sf::Packet& packet, sf::IpAddress address, uint16_t port /* is this really the port ? */) {    // why do you need the address if it's a broadcast ? or is it the broadcast IP ?
                                                                        // (*?) so, one can "broadcast" in a local network at a distance (?!), on a different local network from its own
    }
    void BroadcastRawData(const uint8_t*, sf::IpAddress, uint16_t port) {}

    void ManagePackets() {}
    void Run() {
        std::thread connection_thread(&Server::ConnectClients, this, &clients);

        ManagePackets();
    }

};

class ClientsManager {
    std::vector<std::pair<uint64_t, Client>> clients;

};

void main(int argc, char** argv) {
    // interpret the input to see whether to execute the Client or the Server,
        // and with what arguments (address, port)
    Server server1 {2525, false};
    server1.Run();

    Client client1;
    client1.Connect("localHost", 2525);
    client1.Run();
}

    // (*?) this is undesired; locality of the initialization of class-specific data, I desire it to occur in the class, not outside it...
};

#endif // CHATNETWORK_HPP_INCLUDED
