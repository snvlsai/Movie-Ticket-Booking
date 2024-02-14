#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.c"

movie *g_movies = NULL;
int movie_size = 3;
int show_count = 2;
ticket *g_ticket = NULL;
ticket *tail = NULL;

// Function Declaration
void init_data();
void book_ticket();
void clear_console();
void show_ticket();
void display_welcome_screen();
void free_memory();

int main()
{
    clear_console();
    init_data();
    display_welcome_screen();
    free_memory();
    return 0;
}
void init_data()
{
    // movie1
    movie *movie1 = (movie *)malloc(sizeof(movie));
    strcpy(movie1->name, "Oppenheimer");
    strcpy(movie1->lang, "English");
    // movie1-show1
    show *show1_1 = (show *)malloc(sizeof(show));
    strcpy(show1_1->time, "8:30 AM");
    strcpy(show1_1->screen, "Screen-1");
    // movie1-show2
    show *show1_2 = (show *)malloc(sizeof(show));
    strcpy(show1_2->time, "12:30 PM");
    strcpy(show1_2->screen, "Screen-2");

    movie1->shows = show1_1;
    show1_1->next = show1_2;

    // movie2
    movie *movie2 = (movie *)malloc(sizeof(movie));
    strcpy(movie2->name, "Leo");
    strcpy(movie2->lang, "Tamil");
    // movie2-show1
    show *show2_1 = (show *)malloc(sizeof(show));
    strcpy(show2_1->time, "5:30 AM");
    strcpy(show2_1->screen, "Screen-1");
    // movie2-show2
    show *show2_2 = (show *)malloc(sizeof(show));
    strcpy(show2_2->time, "8:30 PM");
    strcpy(show2_2->screen, "Screen-2");

    movie2->shows = show2_1;
    show2_1->next = show2_2;

    // movie3
    movie *movie3 = (movie *)malloc(sizeof(movie));
    strcpy(movie3->name, "Salaar");
    strcpy(movie3->lang, "Telugu");
    // movie1-show1
    show *show3_1 = (show *)malloc(sizeof(show));
    strcpy(show3_1->time, "6:30 PM");
    strcpy(show3_1->screen, "Screen-1");
    // movie1-show2
    show *show3_2 = (show *)malloc(sizeof(show));
    strcpy(show3_2->time, "9:30 PM");
    strcpy(show3_2->screen, "Screen-2");

    movie3->shows = show3_1;
    show3_1->next = show3_2;

    movie1->next = movie2;
    movie2->next = movie3;
    movie3->next = NULL;

    g_movies = movie1;
}
int get_movie()
{
    clear_console();
    int movie_choice;
    int is_valid;
    do
    {
        printf("Movies:%d\n", movie_size);
        movie *temp = g_movies;
        int i = 1;
        while (temp != NULL)
        {
            printf("%d-%s (%s)\n", i, temp->name, temp->lang);
            temp = temp->next;
            i++;
        }
        printf("%d-Main Menu\n", (movie_size + 1));
        printf("Enter your choice:");
        scanf("%d", &movie_choice);
        is_valid = (movie_choice > 0) && (movie_choice <= movie_size + 1);
        if (!is_valid)
            printf("Enter a number among the given numbers!\n");
        if (movie_choice == (movie_size + 1))
            display_welcome_screen();
    } while (!is_valid);
    return movie_choice;
}
int get_show(movie *chosen_movie)
{
    clear_console();
    int is_valid, choice;
    do
    {
        printf("%s - Show timings\n", chosen_movie->name);
        show *temp = chosen_movie->shows;
        int i = 1;
        while (temp != NULL)
        {
            printf("%d - %s (%s)\n", i, temp->time, temp->screen);
            temp = temp->next;
            i++;
        }
        printf("%d - Back\n", show_count + 1);
        printf("Enter your choice:");
        scanf("%d", &choice);
        is_valid = (choice > 0) && (choice <= show_count + 1);
        if (!is_valid)
        {
            printf("Enter among the given numbers!\n");
        }
        if (choice == show_count + 1)
            book_ticket();
    } while (!is_valid);
    return choice;
}
void show_seat_layout(movie *chosen_movie, show *chosen_show, int seat_arr[])
{
    clear_console();
    printf("%s-%s (%s)\n", chosen_movie->name, chosen_show->time, chosen_show->screen);
    ticket *temp = g_ticket;
    while (temp != NULL)
    {
        ticket *temp_ticket = temp;
        if ((strcmp(temp_ticket->t_movie->name, chosen_movie->name) == 0) && (strcmp(temp_ticket->t_show->time, chosen_show->time) == 0))
        {
            for (int i = 0; i < temp_ticket->nos; i++)
            {
                seat_arr[temp_ticket->seats[i] - 1] = 1;
            }
        }
        temp = temp->next;
    }
    for (int j = 0; j < 100; j++)
    {
        if (seat_arr[j] != 0)
            printf("*\t");
        else
            printf("%d\t", j + 1);
        if ((j + 1) % 10 == 0)
            printf("\n");
    }
    printf("\n\t\t\tS   C   R   E   E   N\n");
    printf("Press 0 to cancel booking\n");
}
int get_no_of_tickets()
{
    int nop, is_valid;
    do
    {
        is_valid = 1;

        printf("Enter the number of persons:");
        scanf("%d", &nop);
        if (nop == 0)
        {
            clear_console();
            printf("\t \t \tTicking Booking cancelled!\n\n");
            return -1;
        }
        if (nop > 10)
        {
            printf("Only 10 tickets can be booked at a time\n");
            is_valid = 0;
        }
        else if (nop < 0)
        {
            printf("Enter a valid number\n");
            is_valid = 0;
        }

    } while (!is_valid);
    return nop;
}
void get_seats(int nos, int seat_arr[], int seat_no[])
{
    int is_valid, temp;

    for (int itr = 0; itr < nos; itr++)
    {
        do
        {
            is_valid = 1;

            printf("Enter the seat number for person %d:", itr + 1);
            scanf("%d", &temp);

            if (temp > 100 || temp < 1)
            {
                printf("Enter seat number within the given limit\n");
                is_valid = 0;
            }
            else if (seat_arr[temp - 1] != 0)
            {
                printf("Already Booked!\n");
                is_valid = 0;
            }
            for (int itr_2 = itr - 1; itr_2 >= 0; itr_2--)
                if (seat_no[itr_2] == temp)
                {
                    printf("Already selected!\n");
                    is_valid = 0;
                }
        } while (!is_valid);

        seat_no[itr] = temp;
    }
}
void book_ticket()
{
    int seat_arr[100] = {0};
    int m_movie = get_movie();
    movie *chosen_movie = g_movies;
    int i = 1;
    while (i < m_movie && chosen_movie != NULL)
    {
        chosen_movie = chosen_movie->next;
        i++;
    }
    int m_show = get_show(chosen_movie);
    int j = 1;
    show *chosen_show = chosen_movie->shows;
    while (j < m_show && chosen_show != NULL)
    {
        chosen_show = chosen_show->next;
        j++;
    }
    show_seat_layout(chosen_movie, chosen_show, seat_arr);
    int nos = get_no_of_tickets();
    if (nos == -1)
        return;
    int seats[nos];
    get_seats(nos, seat_arr, seats);
    ticket *new_ticket = (ticket *)malloc(sizeof(ticket));
    for (int itr = 0; itr < nos; itr++)
    {
        new_ticket->seats[itr] = seats[itr];
    }
    new_ticket->t_movie = chosen_movie;
    new_ticket->t_show = chosen_show;
    new_ticket->nos = nos;
    new_ticket->next = NULL;
    if (g_ticket == NULL)
        g_ticket = tail = new_ticket;
    else
    {
        ticket *current_ticket = g_ticket;
        while (current_ticket->next != NULL)
        {
            current_ticket = current_ticket->next;
        }
        current_ticket->next = tail = new_ticket;
    }
    clear_console();
    printf("\t\t\tTicket booked successfully!\n\n");
}
void display_welcome_screen()
{
    clear_console();
    int choice;
    printf("\t\t\t\tWelcome To SRM Cinemas\n\n");
    do
    {
        printf("1-Ticket Booking\n2-Show Tickets\n3-Log out\n");
        printf("Enter you choice:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 3:
            clear_console();
            printf("\t\t\t\tThank you!!!\n");
            break;
        case 1:
            book_ticket();
            break;
        case 2:
            show_ticket();
            break;
        default:
            printf("**Enter a number among the given numbers**\n");
        }
    } while (choice != 3);
}
void show_ticket()
{
    clear_console();
    int x;
    if (g_ticket == NULL)
    {
        printf("No tickets Booked!\n\n");
        printf("Press 0 to go back\n");
        scanf("%d", &x);
        if (x == 0)
            display_welcome_screen();
    }
    else
    {
        printf("\t\t\tLast Booked Ticket\n");
        printf("%s (%s) - ", tail->t_movie->name, tail->t_movie->lang);
        printf("%s (%s)\n", tail->t_show->time, tail->t_show->screen);

        printf("Seats:\n");
        for (int i = 0; i < tail->nos; i++)
            printf("%d ", tail->seats[i]);
        printf("\n\n");
        printf("1-Show all tickets\n");
        printf("2-Go back\n");
        scanf("%d", &x);
        if (x == 2)
            display_welcome_screen();
        else if (x == 1)
        {
            clear_console();
            printf("\t\t\tAll Tickets\n");
            ticket *temp = g_ticket;
            while (temp != NULL)
            {
                ticket *temp_ticket = temp;
                printf("%s (%s) - ", temp_ticket->t_movie->name, temp_ticket->t_movie->lang);
                printf("%s (%s)\n", temp_ticket->t_show->time, temp_ticket->t_show->screen);
                printf("Seats:\n");
                for (int i = 0; i < temp_ticket->nos; i++)
                    printf("%d ", temp_ticket->seats[i]);
                printf("\n\n");
                temp = temp->next;
            }
        }
    }
}
void free_memory()
{
    movie *current_movie = g_movies;
    while (current_movie != NULL)
    {
        show *current_show = current_movie->shows;
        while (current_show != NULL)
        {
            show *temp = current_show;
            current_show = current_show->next;
            free(temp);
        }
        movie *temp = current_movie;
        current_movie = current_movie->next;
        free(temp);
    }

    ticket *current_ticket = g_ticket;
    while (current_ticket != NULL)
    {
        ticket *temp = current_ticket;
        current_ticket = current_ticket->next;
        free(temp);
    }
}
void clear_console()
{
    system("clear");
}