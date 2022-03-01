typedef struct packet {
    int auth;
    float x;
    float y;
} packet_t;

int init_socket();

int send_data(int player_id, float x, float y);

char* recive_data();