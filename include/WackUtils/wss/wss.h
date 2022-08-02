#pragma once

#include <string>
#include <functional>
#include <vector>
#include <WinSock2.h>
#include <Windows.h>

// ----------------------------------- \\
//         Wack Secure Sockets         \\
// ----------------------------------- \\
//   A sub-bibrary of WackUtils that   \\
//       provides secure sockets       \\
// ----------------------------------- \\
// Language: C++                       \\
// Last Updated: 8/2/2022              \\
// Target Platform: Any                \\
// ----------------------------------- \\
// Libraries in use:                   \\
//  - OpenSSL (encryption.h)           \\
//  - CURL    (networking.h)           \\
// ----------------------------------- \\

// TODO: Implement everything

namespace WackUtils::networking::WSS {
	namespace server {
		struct WSS_Client {
			int port;
			SOCKET socket;
			SOCKADDR_IN addr;
			std::string username;
			std::string password;
			std::string outgoingEncryptionKey;
			std::string incomingEncryptionKey;
		};

		/// Callback to authorize a connection.
		typedef std::function<bool(WSS_Client)> WSS_AuthCallback;

		/// Callback to handle outgoing data.
		typedef std::function<void(std::string)> WSS_OutgoingCallback;

		/// Callback to handle incoming data.
		typedef std::function<void(std::string)> WSS_IncomingCallback;

		/// Callback on connection close.
		typedef std::function<void()> WSS_CloseCallback;

		/// Callback to handle incoming connections.
		typedef std::function<void(WSS_Client)> WSS_ConnectionCallback;

		/// Callback on server shutdown.
		typedef std::function<void()> WSS_ShutdownCallback;

		/// Callback to handle internal exceptions.
		typedef std::function<void(std::exception)> WSS_InternalErrorCallback;

		class Server {
		public:
			/// Set port to listen on.
			/// @param port Port to listen on.
			void setPort(int port);

			/// Set callback to authorize connections.
			/// @param callback Callback to authorize connections.
			void setIP(std::string ip);

			/// Set callback to authorize connections.
			/// @param callback Callback to authorize connections.
			void setAuthCallback(WSS_AuthCallback &cb);

			/// Set callback to handle incoming data.
			/// @param callback Callback to handle incoming data.
			void setIncomingCallback(WSS_IncomingCallback &cb);

			/// Set callback to handle outgoing data.
			/// @param callback Callback to handle outgoing data.
			void setOutgoingCallback(WSS_OutgoingCallback &cb);

			/// Set callback to handle disconnection.
			/// @param callback Callback to handle disconnection.
			void setCloseCallback(WSS_CloseCallback &cb);

			/// Set callback to handle shutdown.
			/// @param callback Callback to handle shutdown.
			void setShutdownCallback(WSS_ShutdownCallback &cb);

			/// Set the callback for when a client connects.
			/// @param callback Callback to handle client connection.
			void setClientConnectCallback(std::function<void(WSS_Client)> &cb);

			/// Set the callback for when a client disconnects.
			/// @param callback Callback to handle client disconnection.
			void setClientDisconnectCallback(std::function<void(WSS_Client)> &cb);



			/// Gets the last data that was received.
			/// @param client Client to get data from.
			/// @return Last data that was received.
			std::string getLastData(WSS_Client client);

			/// Gets the last error that occurred.
			/// @return The last error.
			std::string getLastError();

			/// Gets the connected clients.
			/// @return The connected clients.
			std::vector<WSS_Client> getClients();



			/// Disconnects the desired client.
			/// @param client The client to disconnect.
			void disconnectClient(WSS_Client client);

			/// Disconnects targeted clients.
			/// @param clients The clients to disconnect.
			void disconnectClients(std::vector<WSS_Client> clients);

			/// Disconnects all clients.
			void disconnectAll();



			/// Sends data to the desired client.
			/// @param client The client to send data to.
			void send(std::string data, WSS_Client client);

			/// Sends data to targeted clients.
			/// @param data The data to send.
			/// @param len The length of the data.
			/// @param client The client to send data to.
			void send(char *data, int len, WSS_Client client);

			/// Sends data to targeted clients.
			/// @param data The data to send.
			/// @param clients The clients to send data to.
			void send(std::string data, std::vector<WSS_Client> clients);

			/// Sends data to targeted clients.
			/// @param data The data to send.
			/// @param len The length of the data.
			/// @param clients The clients to send data to.
			void send(char *data, int len, std::vector<WSS_Client> clients);

			/// Sends data to all clients.
			/// @param data The data to send.
			void broadcast(std::string data);

			/// Sends data to all clients.
			/// @param data The data to send.
			/// @param len The length of the data.
			void broadcast(char *data, int len);



			/// Is the server running?
			/// @return True if the server is running, false otherwise.
			bool isRunning();

			/// Starts the server.
			void start();

			/// Stops the server.
			void stop();

			/// The constructor.
			/// @param port The port to listen on.
			/// @param ip The IP to listen on.
			/// @param needsAuth Whether or not the incoming clients need to be authorized.
			Server(int port = 6363, std::string ip = "0.0.0.0", bool needsAuth = true);

			/// The destructor.
			~Server();
		private:
			std::vector<WSS_Client> clients;
			int port;
			std::string ip;
			bool needsAuth;

			WSS_AuthCallback &authCallback;
			WSS_IncomingCallback &incomingCallback;
			WSS_CloseCallback &closeCallback;
			WSS_ShutdownCallback &shutdownCallback;
			WSS_OutgoingCallback &outgoingCallback;
		};
	}
	namespace client {
		/// Callback to handle incoming data.
		typedef std::function<void(std::string)> WSS_IncomingCallback;

		/// Callback to handle outgoing data.
		typedef std::function<void(std::string)> WSS_OutgoingCallback;

		/// Callback for when the client disconnects.
		typedef std::function<void()> WSS_DisconnectionCallback;

		/// Callback for when the client connects.
		typedef std::function<void()> WSS_ConnectionCallback;

		/// Callback for when the connected server is shutdown.
		typedef std::function<void()> WSS_ShutdownCallback;

		class Client {
		public:
			/// Send data to the server.
			/// @param data The data to send.
			void send(std::string data);

			/// Send data to the server.
			/// @param data The data to send.
			/// @param len The length of the data.
			void send(char *data, int len);



			/// Gets the last data that was received.
			/// @return Last data that was received.
			std::string getLastData();

			/// returns the last error that occurred.
			/// @return The last error.
			std::string getLastError();



			/// Sets the server IP.
			/// @param ip The server IP.
			void setIP(std::string ip);

			/// Sets the server port.
			/// @param port The server port.
			void setPort(int port);

			/// Set the callback for when the client connects.
			/// @param callback Callback to handle client connection.
			void setConnectionCallback(WSS_ConnectionCallback &cb);

			/// Set the callback for when the client disconnects.
			/// @param callback Callback to handle client disconnection.
			void setDisconnectionCallback(WSS_DisconnectionCallback &cb);

			/// Set the callback for when the server is shutdown.
			/// @param callback Callback to handle server shutdown.
			void setShutdownCallback(WSS_ShutdownCallback &cb);

			/// Set the callback for when data is received.
			/// @param callback Callback to handle data received.
			void setIncomingCallback(WSS_IncomingCallback &cb);

			/// Set the callback for when data is sent.
			/// @param callback Callback to handle data sent.
			void setOutgoingCallback(WSS_OutgoingCallback &cb);

			/// Disconnects the client from the server.
			void disconnect();

			/// Connects to the server.
			/// @param ip The server IP.
			/// @param port The server port.
			void connect(std::string ip, int port);

			/// Connects to the last server.
			void connect();

			/// The constructor of the client.
			/// @param ip The server IP.
			/// @param port The server port.
			/// @param autoConnect Whether or not to automatically connect to the server.
			/// @param username The username to use when connecting.
			/// @param password The password to use when connecting.
			Client(std::string ip, int port = 6363, bool autoConnect = true, std::string username = "", std::string password = "");
			~Client();
		private:
			std::string ip;
			int port;

			std::string lastData;
			std::string lastError;

			WSS_ConnectionCallback &connectionCallback;
			WSS_DisconnectionCallback &disconnectionCallback;
			WSS_ShutdownCallback &shutdownCallback;
			WSS_IncomingCallback &incomingCallback;
			WSS_OutgoingCallback &outgoingCallback;
		};
	}
}