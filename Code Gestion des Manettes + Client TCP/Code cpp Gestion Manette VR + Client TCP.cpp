// ControlleMannette.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "headers/openvr.h"
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace vr;

IVRSystem* vr_pointer = NULL;
void RunProcedure2(SOCKET socket);
void RunProcedure1();

std::string Message;
char buf[4096];




void main()
{

	

	int controllerIndex; //The index of the controllers[] array that corresponds with the controller that had a buttonEvent
	EVRInitError eError = VRInitError_None;
	vr_pointer = VR_Init(&eError, VRApplication_Background);

	std::string ipAddress = "192.168.1.120";			// IP Address of the server
	int port = 54000;						// Listening port # on the server

	// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		std::cout << "Can't start Winsock, Err #" << wsResult << std::endl;
		return;
	}

	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cout << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		std::cout << "Can't connect to server, Err #" << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		return;
	}
	
	
	if (eError != VRInitError_None)
	{
		vr_pointer = NULL;
		printf("Unable to init VR runtime: %s \n",
			VR_GetVRInitErrorAsEnglishDescription(eError));
		exit(EXIT_FAILURE);
	}
	
	

	std::cout << "Hello World!\n";

	//Message = "Hello World";
	/*if (Message.size() > 0)		// Make sure the user has typed in something
	{
		// Send the text
		int sendResult = send(sock, Message.c_str(), Message.size() + 1, 0);
		/*if (sendResult != SOCKET_ERROR)
		{
			// Wait for response
			ZeroMemory(buf, 4096);
			int bytesReceived = recv(sock, buf, 4096, 0);
			if (bytesReceived > 0)
			{
				// Echo response to console
				std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
			}
		}*/
	//}
	Message = "";
	while (1) {
		//std::cout << "okok\n";
		//RunProcedure1();
		RunProcedure2(sock);
	}

    
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.

void RunProcedure1() {
	VREvent_t event1;
	if (vr_pointer->PollNextEvent(&event1, sizeof(event1)))
	{
		switch (event1.eventType)
		{
		case VREvent_TrackedDeviceActivated:
			printf("EVENT (OpenVR) Device : %d attached\n",
				event1.trackedDeviceIndex);
			break;

			//and so on, can test for any amount of vr events

		default:
			printf("EVENT--(OpenVR) Event: %d\n", event1.eventType);
		}
	}
}

void RunProcedure2(SOCKET socket )
{
	
	VREvent_t event;
	
	
	if (vr_pointer->PollNextEvent(&event, sizeof(event)))
	{
		//Process the VREvent
		
		ETrackedControllerRole role = vr_pointer->GetControllerRoleForTrackedDeviceIndex(event.trackedDeviceIndex);

		switch (event.data.controller.button) {
		case k_EButton_Grip:
			switch (event.eventType) {
			case VREvent_ButtonPress:
				
				std::cout << "Grip press\n";
				//Message = "Grip press";

				if (role == TrackedControllerRole_Invalid) {
					std::cout << "error\n";
					//Message += " error";
				}
				else if (role == TrackedControllerRole_LeftHand) {
					std::cout << "Left\n";
					Message = "3";
				}
				else if (role == TrackedControllerRole_RightHand)
				{
					std::cout << "right\n";
					Message = "4";
				}
				
				
				if (Message.size() > 0)		// Make sure the user has typed in something
				{
					// Send the text
					int sendResult = send(socket, Message.c_str(), Message.size() + 1, 0);
					/*if (sendResult != SOCKET_ERROR)
					{
						// Wait for response
						ZeroMemory(buf, 4096);
						int bytesReceived = recv(socket, buf, 4096, 0);
						if (bytesReceived > 0)
						{
							// Echo response to console
							std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
						}
					}*/
				}
				Message = "";

				break;

			case VREvent_ButtonUnpress:
				
				std::cout << "Grip unpress\n";
				//Message = "Grip unpres";

				if (role == TrackedControllerRole_Invalid) {
					std::cout << "error\n";
					//Message += " error";
				}
				else if (role == TrackedControllerRole_LeftHand) {
					std::cout << "Left\n";
					//Message += " Left";
				}
				else if (role == TrackedControllerRole_RightHand)
				{
					std::cout << "right\n";
					//Message += " right";
				}

				Message = "0";
				if (Message.size() > 0)		// Make sure the user has typed in something
				{
					// Send the text
					int sendResult = send(socket, Message.c_str(), Message.size() + 1, 0);
					/*if (sendResult != SOCKET_ERROR)
					{
						// Wait for response
						ZeroMemory(buf, 4096);
						int bytesReceived = recv(socket, buf, 4096, 0);
						if (bytesReceived > 0)
						{
							// Echo response to console
							std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
						}
					}*/
				}
				Message = "";

				break;
			}
			break;

		case k_EButton_SteamVR_Trigger:
			switch (event.eventType) {
			case VREvent_ButtonPress:
				
				std::cout << "Trigger press\n";
				//Message = "Trigger press";

				
				if (role == TrackedControllerRole_Invalid) {
					std::cout << "error\n";
					//Message += " error";
				}
				else if (role == TrackedControllerRole_LeftHand) {
					std::cout << "Left\n";
					Message = "2";
				}
				else if (role == TrackedControllerRole_RightHand)
				{
					std::cout << "right\n";
					//Message += " right";
					Message = "1";
				}
				

				if (Message.size() > 0)		// Make sure the user has typed in something
				{
					// Send the text
					int sendResult = send(socket, Message.c_str(), Message.size() + 1, 0);
					/*if (sendResult != SOCKET_ERROR)
					{
						// Wait for response
						ZeroMemory(buf, 4096);
						int bytesReceived = recv(socket, buf, 4096, 0);
						if (bytesReceived > 0)
						{
							// Echo response to console
							std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
						}
					}*/
				}
				Message = "";

				break;

			case VREvent_ButtonUnpress:
				
				std::cout << "Trigger unpress\n";
				//Message = "Trigger unpress";

				if (role == TrackedControllerRole_Invalid) {
					std::cout << "error\n";
					//Message += " error";
				}
				else if (role == TrackedControllerRole_LeftHand) {
					std::cout << "Left\n";
					//Message += " Left";
				}
				else if (role == TrackedControllerRole_RightHand)
				{
					std::cout << "right\n";
					//Message += " right";
				}

				Message = "0";
				if (Message.size() > 0)		// Make sure the user has typed in something
				{
					// Send the text
					int sendResult = send(socket, Message.c_str(), Message.size() + 1, 0);
					/*if (sendResult != SOCKET_ERROR)
					{
						// Wait for response
						ZeroMemory(buf, 4096);
						int bytesReceived = recv(socket, buf, 4096, 0);
						if (bytesReceived > 0)
						{
							// Echo response to console
							std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
						}
					}*/
				}
				Message = "";


				break;
			}
			break;

		case k_EButton_SteamVR_Touchpad:
			switch (event.eventType) {
			case VREvent_ButtonPress:
				
				std::cout << "Touchpad press\n";

				if (role == TrackedControllerRole_Invalid) {
					std::cout << "error\n";
					
				}
				else if (role == TrackedControllerRole_LeftHand) {
					std::cout << "Left\n";
					
				}
				else if (role == TrackedControllerRole_RightHand)
				{
					std::cout << "right\n";
					
				}
				break;

			case VREvent_ButtonUnpress:
				
				std::cout << "Touchpad press\n";

				if (role == TrackedControllerRole_Invalid) {
					std::cout << "error\n";
					
				}
				else if (role == TrackedControllerRole_LeftHand) {
					std::cout << "Left\n";
					
				}
				else if (role == TrackedControllerRole_RightHand)
				{
					std::cout << "right\n";
					
				}
				break;

			case VREvent_ButtonTouch:
				
				std::cout << "ButtonTouch press\n";
				//Message = "ButtonTouch press";

				if (role == TrackedControllerRole_Invalid) {
					std::cout << "error\n";
					//Message += " error";
				}
				else if (role == TrackedControllerRole_LeftHand) {
					std::cout << "Left\n";
					//Message += " Left";
				}
				else if (role == TrackedControllerRole_RightHand)
				{
					std::cout << "right\n";
					//Message += " right";
				}
				//Message = "5";

				//if (Message.size() > 0)		// Make sure the user has typed in something
				//{
					// Send the text
					//int sendResult = send(socket, Message.c_str(), Message.size() + 1, 0);
					/*if (sendResult != SOCKET_ERROR)
					{
						// Wait for response
						ZeroMemory(buf, 4096);
						int bytesReceived = recv(socket, buf, 4096, 0);
						if (bytesReceived > 0)
						{
							// Echo response to console
							std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
						}
					}*/
				//}
				//Message = "";

				break;

			case VREvent_ButtonUntouch:
				
				std::cout << "ButtonTouch unpress\n";
				//Message = "ButtonTouch unpress";

				if (role == TrackedControllerRole_Invalid) {
					std::cout << "error\n";
					//Message += " error";
				}
				else if (role == TrackedControllerRole_LeftHand) {
					std::cout << "Left\n";
					//Message += " Left";
				}
				else if (role == TrackedControllerRole_RightHand)
				{
					std::cout << "right\n";
					//Message += " right";
				}
				//Message = "6";
				//if (Message.size() > 0)		// Make sure the user has typed in something
				//{
					// Send the text
					//int sendResult = send(socket, Message.c_str(), Message.size() + 1, 0);
					/*if (sendResult != SOCKET_ERROR)
					{
						// Wait for response
						ZeroMemory(buf, 4096);
						int bytesReceived = recv(socket, buf, 4096, 0);
						if (bytesReceived > 0)
						{
							// Echo response to console
							std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
						}
					}*/
				//}
				//Message = "";

				break;
			}
			break;

		case k_EButton_ApplicationMenu:
			switch (event.eventType) {
			case VREvent_ButtonPress:
				
				std::cout << "ApplicationMenu press\n";
				if (role == TrackedControllerRole_Invalid) {
					std::cout << "error\n";
				}
				else if (role == TrackedControllerRole_LeftHand) {
					std::cout << "Left\n";
				}
				else if (role == TrackedControllerRole_RightHand)
				{
					std::cout << "right\n";
				}
				break;

			case VREvent_ButtonUnpress:
				
				std::cout << "ApplicationMenu unpress\n";

				if (role == TrackedControllerRole_Invalid) {
					std::cout << "error\n";
				}
				else if (role == TrackedControllerRole_LeftHand) {
					std::cout << "Left\n";
				}
				else if (role == TrackedControllerRole_RightHand)
				{
					std::cout << "right\n";
				}
				break;
			}
			break;
		}

		
	}

}
	
	//Output tracking data or do other things


