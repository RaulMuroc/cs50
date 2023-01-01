#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

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
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // look for a candidate called name.
    // if candidate found, update ranks and return true. ranks[i] is the voter's ith preference.
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // update the preferences array based on the current voter's rank
    // preferences[i][j] is number of voters who prefer i over j
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    // add each pair of candidates to pairs array if one candidate is preferred over the other.
    // update global var pair_count to be the total numbers of pairs.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences [j][i])
            {
                pair p;
                p.winner = i;
                p.loser = j;
                pairs[pair_count++] = p;
            }
        }
    }
}

int compare(const void *elem1, const void *elem2)
{
    pair f = *((pair *) elem1);
    pair s = *((pair *) elem2);
    int f_margin = preferences[f.winner][f.loser] - preferences[f.loser][f.winner];
    int s_margin = preferences[s.winner][s.loser] - preferences[s.loser][s.winner];
    return s_margin - f_margin;
}
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // sort pairs in order by decreaasing strenght of victory.
    qsort(pairs, pair_count, sizeof(pair), compare);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // update locked to create the locked graph by adding alll edges in decreaising order of victory strength, as long as there is no cycle.
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;

        bool visited[candidate_count];
        for (int j = 0; j < candidate_count; j++)
        {
            visited[j] = false;
        }
        if (visited[i])
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
        visited[i] = true;
        for (int x = 0; x < candidate_count; x++)
        {
            if (locked[i][x])
            {
                locked[pairs[i].winner][pairs[i].loser] = false;
            }
        }
    }
}

bool is_source(int index)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][index])
        {
            return false;
        }
    }
    return true;
}

int get_source()
{
    for (int i = 0; candidate_count; i++)
    {
        if (is_source(i))
        {
            return i;
        }
    }
    return -1;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // print out the winner of the electrion, who will be the source of the graph.
    // you may assue there will not be more than one source.
    int index = get_source();
    if (index != -1)
    {
        printf("%s\n", candidates [index]);
    }
}