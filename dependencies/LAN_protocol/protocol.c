#include "protocol.h"


/* Converts packet to string */
int packetToStr(DataPacket *packet, char buffer[PACKET_STR_SIZE])
{
    int counter;
    counter = sprintf(buffer, "%d|%d|%d|%d|%d|%s", 
                packet -> label, packet -> id, packet -> ans_id, packet -> last, 
                packet -> order, packet -> content);

    //if ( counter != NUM_PACKET_FIELDS ) return -1;
    return 1;
}


/* Converts string to packet */
int strToPacket(DataPacket *packet, char buffer[PACKET_STR_SIZE])
{
    int counter;
    counter = sscanf(buffer, "%d|%d|%d|%d|%d|%[0-9a-zA-Z _,.|/]",
                &(packet -> label), &(packet -> id), &(packet -> ans_id), &(packet -> last), 
                &(packet -> order), packet -> content);
    //if ( counter != NUM_PACKET_FIELDS ) return -1;
    return 1;
}

int fillPacket(DataPacket *packet, int label, int id, int ans_id, int last, int order, char content[CHUNK_SIZE])
{

    packet -> label = label;

    packet -> id = id;
    packet -> ans_id = ans_id;
    packet -> last = last;
    packet -> order = order;

    if ( strncpy(packet -> content, content, CHUNK_SIZE - 1) == NULL ) 
        return 0;
    
    return 1;
}
     

int sendPacket(int fd, DataPacket *packet)
{
    char buffer[PACKET_STR_SIZE];
    int result;

    result = packetToStr(packet, buffer);
    if ( result != 1 )
    {
        #if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
        printf("Unable to convert packet to string.Exiting...\n");
        #endif
        return -1;
    }

    #if defined(DEBUG_PROTOCOL) || defined(DEBUG_ALL) || defined(DEBUG_PACKET)
    printf("[sendPacket] buffer is: %s\n", buffer);
    #endif
    send(fd, buffer, PACKET_STR_SIZE, 0);

    return 1;
}

int recvPacket(int fd, DataPacket *packet)
{
    char buffer[PACKET_STR_SIZE];
    int result;

    recv(fd, buffer, PACKET_STR_SIZE, 0);
    result = strToPacket(packet, buffer);

    #if defined(DEBUG_PROTOCOL) || defined(DEBUG_ALL) || defined(DEBUG_PACKET)
    printf("[recvPacket] buffer is: %s\n", buffer);
    #endif

    return result;
}

/* Receives packets from fd and return them in a dynamic list
 *
 * NOTE:
 * If other packets that are not chained with the first received, 
 * they are appended at the end of the packets list with the field "order"
 * set to NO_ORDER */
//DA DEBUGGARE
//TOFIX: la funzione non agisce in modo corretto se riceve subito l'ultimo paccetto della serie
PacketNode *recvPackets(int fd, int expected_label, int expected_id, int expected_ans_id)
{
    PacketNode *packets, *curNode;    
    PacketNode *others, *othersCursor;
    DataPacket curPacket;

    char buffer[sizeof(DataPacket)];
    int result;

    int counter;
    int foundLast;


    /* receiving the first packet */
    recv(fd, buffer, sizeof(DataPacket), 0);
    result = strToPacket(&curPacket, buffer);
    if ( result != 1 )
    {
        #if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
        printf("Unable to convert string to packet. Exiting...\n");
        #endif
    }


    packets = malloc(sizeof(PacketNode));
    packets -> packet = curPacket;
    packets -> order = curPacket.order;
    packets -> next = NULL;

    /* if it is not the packet that receiver was expecting, function terminates */
    if ( ( expected_label != NO_LABEL) && ( curPacket.label != expected_label) ||
         ( expected_id != NO_ID ) && ( curPacket.id != expected_id ) || 
         ( expected_ans_id != NO_ANS_ID ) && ( curPacket.ans_id != expected_ans_id ) ) return packets;

    /* if it was an atomi packet, function terminates */
    if ( curPacket.order = NO_ORDER ) return packets;

    /* receiving other packets */
    othersCursor = malloc(sizeof(PacketNode));
    others = othersCursor;
    counter = 1;
    curNode = packets;
    foundLast = 0;

    /* while the full packet chain wasn't found (or the last packet wasn't part of
     * the chain) */
    while( (curPacket.id != packets -> packet.id ) || 
           ( foundLast == 1 && arePacketsSequential(packets) != 1 ) )
    {
        recv(fd, buffer, sizeof(DataPacket), 0);
        result = strToPacket(&curPacket, buffer);
        if ( result != 1 )
        {
            #if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
            printf("Unable to convert string to packet. Exiting...\n");
            #endif
        }

        /* following conditions check if it is this packet is chained with the 
         * first one */
        if ( curPacket.id == packets -> packet.id ) 
        {
            curNode -> next = malloc(sizeof(PacketNode));
            curNode -> next -> packet = curPacket;
            curNode -> next -> order = curPacket.order;

            curNode = curNode -> next;
            counter++;

            if ( foundLast == 0 && curPacket.last == LAST ) foundLast = 1;

            sortPackets(&packets);

        }
        /* if it is not chained with the first one, then it is added to "others" */
        else
        {
            othersCursor -> order = NO_ORDER;
            othersCursor -> packet = curPacket;
            othersCursor -> next = NULL;

            othersCursor -> next = malloc(sizeof(PacketNode));
            othersCursor = othersCursor -> next;
        }
            

    }

    curNode -> next = NULL;

    /* now "others" are chained to packets */
    curNode -> next = others;
    free(othersCursor);

    return packets;
}


/* Sorts Packet list with increasing order */
int sortPackets(PacketNode **packets)
{
    PacketNode **curNode, *tmpNode;
    int sorted;

    if ( packets == NULL || *packets == NULL ) return -1;
    

    sorted = 1;
    while ( sorted == 1 )
    {
        curNode = packets;
        sorted = 0;
        while ( (*curNode) -> next != NULL )
        {
           if ( (*curNode) -> next -> order < (*curNode) -> order )
            {
                tmpNode = (*curNode) -> next -> next;
                (*curNode) -> next -> next = (*curNode);

                (*curNode) = (*curNode) -> next;
                (*curNode) -> next -> next = tmpNode;
                sorted = 1;
            }
            else curNode = &((*curNode) -> next);
        }

    }
    
}

/* Checking if Packet list is sorted.
 *
 * PARAMETERS:
 *  - PacketNode *packets, the list of packets
 *  - order, the order which has to be respected 
 *      - 0 for decreasing order
 *      - 1 for increasing order
 * 
 * RETURN VALUE:
 *  - 1 if list is sorted, otherwise 0 */
int arePacketsSorted(PacketNode *packets, int order)
{
    int multiplier;
    if ( packets == NULL ) return -1;

    multiplier = order == 1 ? 1 : -1;

    while ( packets -> next != NULL )
    {
        if ( multiplier * (packets -> order) > multiplier * (packets -> next -> order) ) return 0;
        packets = packets -> next;
    }

    return 1;
}

/* Checks whether packets are sequential (ordered and follwing packet order is 
 * current packet order + 1 or -1) */
int arePacketsSequential(PacketNode *packets)
{
    if ( packets == NULL ) return 0;
    
    while ( packets -> next != NULL )    
    {
        if ( packets -> next -> order - packets -> order != 1 &&
             packets -> next -> order - packets -> order != -1 )
             return 0;

        packets = packets -> next;
    }

    return 1;
}

/* Protocol Accept. Accept client connectionusing the protocol RAA / Double-Handshake:
 *  - server sends a Request of connection (ROCONN)
 *  - client answer back with an Acknoledgment (ACK)
 *  - server answer back again with an Acknowledgment (ACK)
 * 
 * RETURN VALUE:
 * If connection is successfull, 0 is returned.
 * If accept() failed, OTHER_FAIL is returned and errno is set to OTHER_FAIL
 * If protocol failed, PROTOCOL_FAIL is returned and errno is set to PROTOCOL_FAIL
 */
int paccept(int server_socket, int* client_socket, struct sockaddr *client_address)
{
    int addr_len;
    int numAttempts;

    DataPacket serverMsg, clientMsg;
    int currID, clientID;

    if ( client_socket == NULL ) 
    {
        printf("Invalid client_socket variable.");
        return OTHER_FAIL;
    }

    if ( client_address == NULL ) return OTHER_FAIL;
    addr_len = sizeof(server_socket);

    do 
    {
        errno = 0;
        *client_socket = accept(server_socket, client_address, 
                            (socklen_t *) &addr_len);
        #if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
        if ( errno != 0 || client_socket == -1 )
        {
            printf("[hostOnlineGame] Server tried to accept client but something went wrong\n");

        } 
        #endif

    } while ( errno != 0 || *client_socket == -1 );
    printf("Out of accept loop\n");

    /* checking if it is possible to communicate with client */
    numAttempts = 0;
    do
    {
        fillPacket(&serverMsg, ROCONN, currID, NO_ANS_ID, LAST, NO_ORDER, NO_CONTENT);

        #if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
        printf("[Sending ROCONN] Sending...\n");
        #endif
        sendPacket(*client_socket, &serverMsg);
        currID++;
        #if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
        printf("[Waiting for ACK] ROCONN sent, waiting for ACK\n");
        #endif
        recvPacket(*client_socket, &clientMsg);

        clientID = clientMsg.id;

        //#if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
        if ( clientMsg.label != ACK )
        {
            printf("[Waiting for ACK] Connection not acknowledged! Trying again\n");
        }
        //#endif
        numAttempts++;
    } while ( ( clientMsg.label != ACK ) && ( numAttempts < MAX_SEND_ATTEMPTS ) );


    if ( numAttempts >= MAX_SEND_ATTEMPTS )
    {
        //#if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
        #if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
        printf("[Waiting for ACK] No acknowledge received from client!");
        #endif
        //#endif
        errno = PROTOCOL_FAIL;
        return PROTOCOL_FAIL;
    }

    #if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
    printf("[Waiting for ACK] ACK found\n");
    #endif

    fillPacket(&serverMsg, ACK, currID, clientID, LAST, NO_ORDER, NO_CONTENT);

    sendPacket(*client_socket, &serverMsg);
    return 0;
}

/* Protocol Connect. Connect to server using the protocol RAA / Double-Handshake.
 * 
 * RETURN VALUE:
 * If connection is successfull, 0 is returned.
 * If connect() failed, OTHER_FAIL is returned and errno is set to OTHER_FAIL
 * If protocol failed, PROTOCOL_FAIL is returned and errno is set to PROTOCOL_FAIL
 */
int pconnect(int local_socket, struct sockaddr *server_address)
{
    int localSocket;
    DataPacket serverMsg, localMsg;
    char buffer[15];

    int serverID, currID;
    int numAttempts;
    int result;

    /* connecting to the server */
    errno = 0;
    result = connect(local_socket, server_address, sizeof(struct sockaddr_in));

    if ( result != 0 || errno != 0 )
    {
        printf("Unable to connect to server. Exiting ...\n");

        errno = OTHER_FAIL;
        return OTHER_FAIL;
    } 
    #if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
    else printf("Connected!\n");
    #endif

    /* doing protocol procedures ... */
    /* 1) server sends a Request for Connection (ROCONN) */
    numAttempts = 0;
    do
    {
        #if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
        printf("[Waiting for ROCONN] Waiting...!\n");
        #endif

        recvPacket(local_socket, &serverMsg);
        numAttempts++;

        #if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
        printf("[Waiting for ROCONN] Packet received!\n");
        #endif
    } while ( ( serverMsg.label != ROCONN ) && ( numAttempts < MAX_SEND_ATTEMPTS ));

    // if no request was found, connection fails
    if ( numAttempts >= MAX_SEND_ATTEMPTS )
    {
        #if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
        printf("[Wating for ROCONN] No request received from server\n");
        #endif

        errno = PROTOCOL_FAIL;
        return PROTOCOL_FAIL;
    } 
    #if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
    else printf("[Waiting for ROCONN] Right packet found\n");
    #endif

    /* 2) client sends an Acknoledgement (ACK) */
    serverID = serverMsg.id;
    currID = 1;

    fillPacket(&localMsg, ACK, currID, serverID, LAST, NO_ORDER, NO_CONTENT);
    sendPacket(local_socket, &localMsg);

    numAttempts = 0;
    do 
    {
        recvPacket(local_socket, &serverMsg);
        numAttempts++;
        
        #if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
        printf("[Waiting for ACK] Packet received\n");
        #endif
    } while ( ( serverMsg.label != ACK ) && numAttempts < MAX_SEND_ATTEMPTS );

    // if no acknowledgement was found, connection fails 
    if ( numAttempts >= MAX_SEND_ATTEMPTS )
    {
        #if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
        printf("[Waiting for ACK] No acknowledgement received from server\n");
        #endif

        errno = PROTOCOL_FAIL;
        return PROTOCOL_FAIL;
    } 
    #if defined(DEBUG_ALL) || defined(DEBUG_PROTOCOL)
    else printf("[Waiting for ACK] Right packet found\n");
    #endif

    return 0;
}

char* findIPWindows()
{

	FILE *buf;
	char lineBuffer[BUF_SIZE];
	char *ipBuffer;
	int counter, counter2;
	int offset;

	int sectionFound;

	ipBuffer = malloc(sizeof(IP_SIZE) * sizeof(char) + sizeof(char));
	// 15 + 1 chars

    buf = fopen("buffer.txt", "w");
    fclose(buf);

	system("ipconfig > buffer.txt");

	buf = fopen("buffer.txt", "r+");

	sectionFound = 0;
	while ( feof(buf) == 0 )
	{

		counter = 0;
		while ( (lineBuffer[counter] = fgetc(buf)) != '\n')
			counter++;

		lineBuffer[counter] = '\0';

		if ( strstr(lineBuffer, "Wireless LAN adapter WiFi:") != NULL || 
			strstr(lineBuffer, "Scheda LAN wireless Wi-Fi") != NULL )
		{
			sectionFound = 1;
		} 
		if ( sectionFound == 1 )
		{
			if ( strstr(lineBuffer, "IPv4 Address") != NULL || 
				strstr(lineBuffer, "Indirizzo IPv4") != NULL)
			{
				for ( counter2 = 10; counter2 < counter && lineBuffer[counter2] != ':'; counter2++);

				counter2 = counter2 + 2;
				if ( counter2 < counter ) 
				{
					for ( offset = 0; counter2 + offset < counter && lineBuffer[counter2 + offset] != '\0'; offset++)
					{
						ipBuffer[offset] = lineBuffer[counter2 + offset];
					}
					ipBuffer[offset] = '\0';
				}
				else printf("Nothing found\n");


				return ipBuffer;
			}
		}
					

	}

	fclose(buf);

	return "\0";
}

char* findIPLinux()
{

	FILE *buf;
	char lineBuffer[BUF_SIZE];
	char *ipBuffer;
	int counter, counter2;
	int offset;

	int sectionFound;

	ipBuffer = malloc(sizeof(IP_SIZE) * sizeof(char) + sizeof(char));

    buf = fopen("buffer.txt", "w");
    fclose(buf);

	system("ip address > buffer.txt");

	buf = fopen("buffer.txt", "r+");

	sectionFound = 0;
	while ( feof(buf) == 0 )
	{

		counter = 0;
		while ( (lineBuffer[counter] = fgetc(buf)) != '\n')
			counter++;

		lineBuffer[counter] = '\0';

		if ( strstr(lineBuffer, "wifi") != NULL &&
			strstr(lineBuffer, "UP") != NULL )
		{
			sectionFound = 1;
		} 
		if ( sectionFound == 1 )
		{
			if ( strstr(lineBuffer, "inet") != NULL &&
				strstr(lineBuffer, "inet6") == NULL)
			{
				for ( counter2 = 0; counter2 < counter && lineBuffer[counter2] != 't'; counter2++);

				counter2 = counter2 + 2;
				if ( counter2 < counter ) 
				{
					for ( offset = 0; counter2 + offset < counter && lineBuffer[counter2 + offset] != '/'; offset++)
					{
						ipBuffer[offset] = lineBuffer[counter2 + offset];
					}
					ipBuffer[offset] = '\0';

				}
				else printf("Nothing found\n");

				return ipBuffer;
			}
		}
					

	}

	fclose(buf);

	return "\0";
}

char *findIP()
{
    #if defined(_WIN32)
    return findIPWindows();
    #elif defined(__linux__)
    return findIPLinux();
    #endif
}
