// TicTacToe.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
// by 3n3a

#include <cstdlib>
#include <cstdio>
#include <windows.h>

#define DEBUG false

// 1 = 'O'
// 2 = 'X'

//TODO: overwriting still possible

void display_winner(int winner, int arr[3][3]);

char num_to_tic(int num)
{
  switch (num)
  {
  case 0:
    return ' ';
  case 1:
    return 'O';
  case 2:
    return 'X';
  default:
    return ' ';
  }
}

void print_playing_field(int arr[3][3])
{
  for (int i = 0; i < 3; ++i)
  {
    const char one = num_to_tic(arr[i][0]);
    const char two = num_to_tic(arr[i][1]);
    const char three = num_to_tic(arr[i][2]);
    printf(" %c | %c | %c \n", one, two, three);

    if (i != 2) printf("---|---|---\n");
  }
}

void print_debug_array(int arr[3][3])
{
  printf("\nDisplaying values:\n");
  for (int i = 0; i < 3; ++i)
  {
    printf("[%i][%i][%i]\n", arr[i][0], arr[i][1], arr[i][2]);

  }
}

int set_state_for_pos(int arr[3][3], const int position, const int state)
{
  const int row = (position - 1) / 3;
  const int column = (position - 1) % 3;
  if (arr[row][column] == 0) {
    arr[row][column] = state;
    return 0;
  }
  return 1;
}

void init()
{
  printf("\n\n\n\t\t---- TIC TAC TOE ----\n\t\t\tby 3n3a\n\n\n");
  Sleep(2000);
}

void count_x_o(int number, int sum_arr[3][2], int elem_sum_arr)
{
  if (number> 0)
  {
    switch (number)
    {
    case 1:
      sum_arr[elem_sum_arr][0]++;
      break;
    case 2:
      sum_arr[elem_sum_arr][1]++;
      break;
    }
  }
}

int who_wins(int arr[3][3])
{
  //Calculation

  // [no 1/o][no 2/x]
  int sum_rows[3][2] = { {0, 0}, {0, 0}, {0, 0} };
  int sum_columns[3][2] = { {0, 0}, {0, 0}, {0, 0} };
  int sum_diags[2][2] = { {0, 0}, {0, 0} };
  for (int j = 0; j < 3; ++j)
  {
    for (int i = 0; i < 3; ++i)
    {
      // rows
      count_x_o(arr[j][i], sum_rows, j);

      // columns
      count_x_o(arr[i][j], sum_columns, j);     
    }

    // diagonals
    count_x_o(arr[j][j], sum_diags, 0);
    count_x_o(arr[j][2 - j], sum_diags, 1);
  }

  // Checking
  if (DEBUG)
  {
    printf("\nDisplaying values:\n");
    for (int i = 0; i < 3; ++i)
    {
      printf("C%i\tSums: [o: %i | x: %i]\n", i, sum_columns[i][0], sum_columns[i][1]);
    }

    for (int i = 0; i < 3; ++i)
    {
      printf("R%i\tSums: [o: %i | x: %i]\n", i, sum_rows[i][0], sum_rows[i][1]);
    }

    for (int i = 0; i < 2; ++i)
    {
      printf("D%i\tSums: [o: %i | x: %i]\n", i, sum_diags[i][0], sum_diags[i][1]);
    }
  }

  if (sum_rows[0][0] == 3) return 1;
  if (sum_rows[0][1] == 3) return 2;

  if (sum_columns[0][0] == 3) return 1;
  if (sum_columns[0][1] == 3) return 2;

  if (sum_diags[0][0] == 3) return 1;
  if (sum_diags[0][1] == 3) return 2;

  return 0;
}

int main() {
  int tic_tac_array[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
  int player = 1;
  int positions_filled = 0;

  init();

  // Game Loop
  do
  {
    if (!DEBUG) system("cls");
    if (DEBUG) print_debug_array(tic_tac_array);
    printf("PLAYER %i - %c\n", player, player == 1 ? 'O' : 'X');
    print_playing_field(tic_tac_array);

    int chosen_position;
    printf("Enter position [1-9]: ");
    scanf_s("%i", &chosen_position);
    printf("\n");

    
    set_state_for_pos(tic_tac_array, chosen_position, player);
    //if () == 1) goto continuation;
    positions_filled++;

    // Swap Player after every round
    if (player == 1)
    {
      player = 2;
    }
    else if (player == 2)
    {
      player = 1;
    }

    const int winner = who_wins(tic_tac_array);
    if (positions_filled == 9)
    {      
      switch (winner)
      {
        case 0:
          printf("No one wins. Draw\n");
          exit(EXIT_SUCCESS);
        case 2:
          display_winner(winner, tic_tac_array);
        case 1:
          display_winner(winner, tic_tac_array);
        default:
          exit(EXIT_FAILURE);
      }
    }
      
    switch(winner)
    {
    case 1:
      display_winner(winner, tic_tac_array);
    case 2:
      display_winner(winner, tic_tac_array);
    }

  //continuation:;
  } while (true);
  return 0;
}

void display_winner(int winner, int arr[3][3])
{
  system("cls");
  print_playing_field(arr);
  printf("Player %i Wins!!\n", winner);
  exit(EXIT_SUCCESS);
}