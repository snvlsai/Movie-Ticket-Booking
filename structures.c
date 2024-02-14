
typedef struct Show
{
    char time[10];
    char screen[20];
    struct Show *next;
} show;

typedef struct Movie
{
    char name[50];
    char lang[20];
    struct Show *shows;
    struct Movie *next;
} movie;

typedef struct Ticket
{
    struct Movie *t_movie;
    struct Show *t_show;
    int seats[10];
    int nos;
    struct Ticket *next;
} ticket;