#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CANDIDATES 9

typedef struct
{
    int winner;
    int loser;
}
pair;

int preferences[MAX_CANDIDATES][MAX_CANDIDATES];
bool locked[MAX_CANDIDATES][MAX_CANDIDATES];
pair pairs[MAX_CANDIDATES * (MAX_CANDIDATES - 1) / 2];
char candidates[MAX_CANDIDATES][32];
int pair_count;
int candidate_count;

bool vote(int rank, const char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool creates_cycle(int winner, int loser);
void print_winner(void);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./tideman [candidate ...]\n");
        return 1;
    }
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i], argv[i + 1]);
    }
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);

    for (int i = 0; i < voter_count; i++)
    {
        int ranks[MAX_CANDIDATES];

        for (int j = 0; j < candidate_count; j++)
        {
            char name[32];
            printf("Rank %i: ", j + 1);
            scanf("%31s", name);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
}

bool vote(int rank, const char *name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j && preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        int max = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            int strength_j = preferences[pairs[j].winner][pairs[j].loser];
            int strength_max = preferences[pairs[max].winner][pairs[max].loser];
            if (strength_j > strength_max)
            {
                max = j;
            }
        }
        pair tmp = pairs[i];
        pairs[i] = pairs[max];
        pairs[max] = tmp;
    }
}

void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if (!creates_cycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
}

bool creates_cycle(int winner, int loser)
{
    if (winner == loser)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] && creates_cycle(winner, i))
        {
            return true;
        }
    }
    return false;
}

void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool has_incoming = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                has_incoming = true;
                break;
            }
        }
        if (!has_incoming)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
