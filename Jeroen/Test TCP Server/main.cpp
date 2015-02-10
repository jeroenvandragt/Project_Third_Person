#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <Utils/glm.hpp>


using namespace std;



bool running = true;
char buffer[1024];

sf::Packet packet;

float xPos;
float yPos;
float zPos;

bool startServer()
{
    cout << "Checking for connections." << endl;

    while ( running )
    {
        sf::TcpListener listener;
        sf::TcpSocket socket;

        socket.setBlocking(false);

        listener.listen(1337);
        // Wait for a connection

        listener.accept(socket);
        std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;

        socket.receive(packet);



        // Receive a message from the client
        std::size_t received = 0;
        socket.receive(buffer, sizeof(buffer), received);
        std::cout << "CLIENT: " << buffer << std::endl;


        // Send an answer
        std::string message = "Welcome to the server!";
        socket.send(message.c_str(), message.size() + 1);

        packet >> xPos >> yPos >> zPos;
        cout << xPos << yPos << zPos << endl;

    }
    return running;
}

int main()
{
    cout << "Initiated server." << endl;

    startServer();
    //testClient();
    return 0;
}


