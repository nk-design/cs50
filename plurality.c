#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 9

typedef struct
{
    char name[32];
    int votes;
}
candidate;

candidate candidates[MAX];
int candidate_count;

bool vote(const char *name);
void print_winner(void);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./plurality [candidate ...]\n");
        return 1;
    }
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i].name, argv[i + 1]);
        candidates[i].votes = 0;
    }

    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);

    for (int i = 0; i < voter_count; i++)
    {
        char name[32];
        printf("Vote: ");
        scanf("%31s", name);

        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}

bool vote(const char *name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

void print_winner(void)
{
    int max_votes = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}
