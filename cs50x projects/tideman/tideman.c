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
bool lock = true;

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
bool vote(int rank, const char *name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
int comparator(const void *a, const void *b);
void lock_pairs(void);
void print_winner(void);
bool has_cycle(int winner, int loser);

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

    // Clear graph of locked in pairs and the preferences array from garbage values
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0;
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

bool vote(int rank, const char *name, int ranks[])
{
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

void record_preferences(int ranks[])
{
  // Update preferences given one voter's ranks

  for (int i = 0; i < candidate_count; i++)
  {
    for (int j = i + 1; j < candidate_count; j++)
    {
      // Increment the number of voters who prefer candidate i over candidate j
      preferences[ranks[i]][ranks[j]]++;
    }
  }
}


void add_pairs(void) {
  // Record pairs of candidates where one is preferred over the other

  for (int i = 0; i < candidate_count; i++)
   {
    for (int j = i + 1; j < candidate_count; j++)
     {
      // If candidate i is preferred over candidate j, add the pair to the pairs array
      if (preferences[i][j] > preferences[j][i])
      {
        pairs[pair_count].winner = i;
        pairs[pair_count].loser = j;
        pair_count++;
      } else if (preferences[i][j] < preferences[j][i])
      {
        // If candidate j is preferred over candidate i, add the pair to the pairs array
        pairs[pair_count].winner = j;
        pairs[pair_count].loser = i;
        pair_count++;
      }
    }
  }
}


int comparator(const void *a, const void *b)
{
  // Cast the void pointers to pair pointers
  pair *ab = (pair *)a;
  pair *ba = (pair *)b;

  // Use pointers to access the preferences and check how much a candidate wins over another
  int difference = preferences[ba->winner][ba->loser] - preferences[ab->winner][ab->loser];

  // Return the difference
  return difference;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    qsort(pairs, pair_count, sizeof(pair), comparator);
}

bool has_cycle(int winner, int loser) {
  // Returns True if there is a cycle between winner and loser, False otherwise.

  while (winner != -1 && winner != loser)
  {
    // Initialize found to False
    bool found = false;

    // Iterate over all candidates
    for (int i = 0; i < candidate_count; i++)
    {
      // If candidate i is locked to winner, set found to True and set winner to i
      if (locked[i][winner]) {
        found = true;
        winner = i;
      }
    }

    // If found is still False, set winner to -1
    if (!found)
    {
      winner = -1;
    }
  }

  // If winner is equal to loser, return True
  if (winner == loser)
  {
    return true;
  }

  // Otherwise, return False
  return false;
}

void lock_pairs(void)
{
  // Lock pairs into the candidate graph in order, without creating cycles.

  for (int i = 0; i < pair_count; i++)
  {
    // Check if locking the pair would create a cycle.
    bool is_cycle = has_cycle(pairs[i].winner, pairs[i].loser);

    // If locking the pair would not create a cycle, lock it.
    if (!is_cycle)
    {
      locked[pairs[i].winner][pairs[i].loser] = true;
    }
  }
}

void print_winner(void)
{
  // Prints the winner of the election.

  for (int col = 0; col < candidate_count; col++)
  {
    // Initialize found_source to True
    bool found_source = true;

    // Iterate over all rows
    for (int row = 0; row < candidate_count; row++)
    {
      // If candidate at row is locked to candidate at col, set found_source to False
      if (locked[row][col])
      {
        found_source = false;
        break;
      }
    }

    // If found_source is still True, print the candidate at col
    if (found_source)
    {
      printf("%s\n", candidates[col]);
      return;
    }
  }
  // If no candidate was found, return
  return;
}
