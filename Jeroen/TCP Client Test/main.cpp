#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <Utils/glm.hpp>
#include <string>

using namespace std;

bool running = true;

float xPos = 1.23;
float yPos = 3.45;
float zPos = 6.78;

sf::Packet packet;

bool connectTheClient()
{


    // ----- The client -----
    // Create a socket and connect it to the IP on the chosen port
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect(sf::IpAddress::getLocalAddress(), 10000);

    socket.connect(sf::IpAddress::getLocalAddress(), 1337);

    std::string sXPos = std::to_string(xPos);
    std::string sYPos = std::to_string(yPos);
    std::string sZPos = std::to_string(zPos);

    float localXPos = std::stod(sXPos);
    float localYPos = std::stod(sYPos);
    float localZPos = std::stod(sZPos);

    packet << localXPos << localYPos << localZPos;

    glm::vec3 testVector = glm::vec3(localXPos,localYPos,localZPos);
    //cout << "Position: " << testVector << endl;

    // Send a message to the connected host
    std::string message = sXPos + " , " + sYPos + " , " + sZPos ;//"CLIENT HERE!";//std::to_string(myFloat);
    socket.send(message.c_str(), message.size() + 1);

    // Receive an answer from the server
    char buffer[1024];
    std::size_t received = 0;
    socket.receive(buffer, sizeof(buffer), received);
    std::cout << "SERVER: " << buffer << std::endl;

    if (status != sf::Socket::Done)
    {
        std::string message = "Client disconnected.";
        socket.send(message.c_str(), message.size() + 1);
    }

    while ( running )
    {
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )running = false;
    }

    return running;
}

int main()
{
    cout << "Initiated a client." << endl;
    connectTheClient();
    return 0;
}
