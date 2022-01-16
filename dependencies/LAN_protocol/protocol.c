#include "protocol.h"

static int sortPackets(PacketNode **packets);

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
    int counter;
    int foundLast;


    /* receiving the first packet */
    recv(fd, &curPacket, sizeof(DataPacket), 0);
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
        recv(fd, &curPacket, sizeof(DataPacket), 0);

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

#if defined(DEBUG)
void printList(PacketNode *head)
{
        while ( head != NULL)
        {
                printf("%d ", head -> order);
                head = head -> next;
        }
        printf("\n");
}

PacketNode* inputList()
{
        PacketNode* head;
        int input;

        scanf("%d", &input);
        if (input == -1) return NULL;

        head = malloc(sizeof(PacketNode));
        head -> order = input;
        head -> next = inputList();

        return head;

}


int main()
{
    PacketNode *packets; 

    printf("Inserisci gli ordini dei pacchetti, separandoli tra loro con 1 spazio\n");
    packets = inputList();

    printList(packets);
    printf("\n");

    sortPackets(&packets);

    printf("Is list sorted? %d\n", arePacketsSorted(packets, 1));
    printf("Is list sequential? %d\n", arePacketsSequential(packets));

    return 0;
}
#endif
