#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include <errno.h>

#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#include <unistd.h>

#define MAX_CLIENTS 1

#define CHUNK_SIZE 50
/* max number of packets with same ID */
#define PACKET_STR_SIZE (CHUNK_SIZE + 200)

#define MAX_PACKETS 5

#define MAX_SEND_ATTEMPTS 10

#define SERVER_PORT 5050
#define CLIENT_PORT 5070

#define NUM_PACKET_FIELDS 6
typedef struct dataPacket
{
    /* label (type of content/packet) of this packet 
     * If set to NO_LABEL, packet will have no label (not suggested) */
    int label;

    /* a numerical identificator of this packet.
     * packets' ids starts from 1
     * If set to NO_ID, packet will have no id (not suggested) */
    int id;

    /* id of packet to whom this packet is answering 
     * If set to NO_ANS_ID, it means that this is not an answer packet */
    int ans_id;

    /* Tell whether this is the last message of the chain.
     * If set to LAST, the packet is the last one
     * If set to NOT_LAST, the packet is not the last one. */
    int last;

    /* A piece of information can be divided into multiple chunks (packets). 
     * This field indicates how packets are ordered.
     * Order starts from 0
     * Ignored if last != 0
     * If set to NO_ORDER, packets will have no order */
    int order;

    /* content of the message.
     * If set to NO_CONTENT, packet will have no content*/
    char content[CHUNK_SIZE];
} DataPacket;

typedef struct packetNode
{
    int order;
    DataPacket packet;
    struct packetNode *next;

} PacketNode;

/* macros for filling packets fields easily */
#define NO_LABEL -1
#define NO_ID -1
#define NO_ANS_ID -1
#define LAST 1
#define NOT_LAST -1
#define NO_ORDER -1
#define NO_CONTENT ""

/* Error of CONNection (invalid data) */
#define ECONN -2
#define ECONN_DATA (DataPacket) { .label = ECOMM }
/* End Of Connection */
#define EOC -3
#define EOCONN_DATA (DataPacket) { .label = EOC }
/* Acknowledgment */
#define ACK 2
#define ACK_DATA (DataPacket) { .label = ACK }

/* Request Of CONNection */
#define ROCONN 1
#define ROCONN_DATA (DataPacket) { .label = ROCONN }

/* Receiver needs to perform a specific action (description of action in "content") */
#define ACTION 3
/* Missing response to ACTION */
#define REPEAT 4
/* Receiver confirming that required action was done. If any result has to be sent, 
 * it is written in "content" field. */
#define ACTION_DONE 5
/* Result sent by receiver as response to ACTION is correct */
#define CORRECT 6
/* If a single packet is missing (in a packet list) */
#define MISSING 7

/* if a function fail for a non-specified value, errno is set to OTHER_FAIL and/or 
 * the function returns OTHER_FAIL */
#define OTHER_FAIL -2
/* if a function fail due to protocol (for example Double-Handshake has failed) then
 * errno is set to PROTOCOL_FAIL and/or the function returns PROTOCOL_FAIL */
#define PROTOCOL_FAIL -1

/* fills the packet fileds with parameters */
int fillPacket(DataPacket *packet, int label, int id, int ans_id, int last, int order, char content[CHUNK_SIZE]);


int sendPacket(int fd, DataPacket *packets);

int recvPacket(int fd, DataPacket *packets);

PacketNode *recvPackets(int fd, int expected_label, int expected_id, int expected_ans_id);

/* Sorts Packet list with increasing order */
int sortPackets(PacketNode **packets);

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
int arePacketsSorted(PacketNode *packets, int order);

/* Checks whether packets are sequential (ordered and follwing packet order is 
 * current packet order + 1 or -1) */
int arePacketsSequential(PacketNode *packets);

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
int paccept(int server_socket, int client_socket, struct sockaddr *client_address);


/* Protocol Connect. Connect to server using the protocol RAA / Double-Handshake.
 * 
 * RETURN VALUE:
 * If connection is successfull, 0 is returned.
 * If connect() failed, OTHER_FAIL is returned and errno is set to OTHER_FAIL
 * If protocol failed, PROTOCOL_FAIL is returned and errno is set to PROTOCOL_FAIL
 */
int pconnect(int local_socket, struct sockaddr *server_address);