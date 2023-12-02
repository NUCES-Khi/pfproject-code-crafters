#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <windows.h>



void initial_chess_board(char initial_board[8][8]);
void display_initial_board(char initial_board[8][8]);
void switch_player(char *curr_player);
int has_white_space(const char *str);
bool Valid_Pawn_Move(int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]);
bool Valid_Knight_Move(int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]);
bool Valid_Bishop_Move(int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]);
bool Valid_Rook_Move(int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]);
bool Valid_Queen_Move(int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]);
bool Valid_King_Move(int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]);




int main(){
    char initial_board[8][8];
    char player1[15], player2[15], color[10]; 
    char curr_player = 'W';


    do {
        printf("Enter Player 1 name (no spaces): ");
        fgets(player1, sizeof(player1), stdin);
        player1[strcspn(player1, "\n")] = '\0'; 
        if (has_white_space(player1) || strcmp(player1, player2) == 0) {
            printf("No SPACES are allowed in Names\n");
        }
    } while (has_white_space(player1) || strcmp(player1, player2) == 0);

    do {
        printf("Enter Player 2 name (no spaces): ");
        fgets(player2, sizeof(player2), stdin);
        player2[strcspn(player2, "\n")] = '\0'; 
        if (has_white_space(player2) || strcmp(player1, player2) == 0) {
            printf("No SPACES are allowed. Both players cannot have the same name\n");
        }
    } while (has_white_space(player2) || strcmp(player1, player2) == 0);

    do {
        printf("%s, enter the color with which you want to play (black or white): ", player1);
        scanf("%s", color);

        if (strcmp(color, "black") == 0) {
            printf("%s has chosen black color\n", player1);
            printf("%s has been assigned white color\n\n", player2);
        } else if (strcmp(color, "white") == 0) {
            printf("%s has chosen white color\n", player1);
            printf("%s has been assigned black color\n\n", player2);
        } else {
            printf("%s there are only two colors in chess, ASSHOLE?!?!\n", player1);
        }
    } while (strcmp(color, "black") != 0 && strcmp(color, "white") != 0);
    
    
    
//GAMES RULES FOR CHESS 
    HANDLE hConsole = GetStdHandle(STD_OUPUT_HANDLE);
    
    printf("\t\t\t\t\tTHE GAME RULES ARE AS FOLLOWS\n");
    printf("The goal is to checkmate the opponent's king which means to capture the king in such a way that there is no possible escape\n\n");

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    printf("\t\t\t\t\t\tPIECE MOVEMENT\n");
    printf("Pawn moves 1 square forward but captures diagonally. On it's first move a pawn can move 2 squares forward\n");
    printf("King moves 1 square in any direction\n");
    printf("Knights move in L shape. 2 squares in one direction and then 1 square perpendicular\n");
    printf("Bishops move diagonally\n");
    printf("Rooks move horizontally and vertically\n");
    printf("Queen moves diagonally as well as horizontal and vertical\n\n");

    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    printf("\t\t\t\t\t\tSPECIAL MOVES\n");
    printf("En passant: A pawn capturing option when the opponent's pawn moves 2 squares forward and lands beside you pawn\n");
    printf("Castling: A defensive move which allows the King and a Rook to move under certain conditions\n");
    printf("Promotion: When a pawn reaches the 8th Rank it can be promoted to any other piece(except a king)\n\n");

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    printf("\t\t\t\t\t\tOTHER RULES\n");
    printf("Check: When the King is in threat\n");
    printf("Checkmate: When the King has no legal move to escape capture. In this condition the game ends with a win\n\n");

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
    printf("\t\t\t\t\t\tDRAW CONDITIONS\n");
    printf("Stalemate: When the King has no legal move and is not in check\n");
    printf("Deadboard condition: A condition where neither player is able to checkmate the opponent by a legal sequence of moves\n");
    printf("50 move rule: When during the last 50 moves, no pawn has been moved and no capture is made\n\n");

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    
//COMMAND TO START THE GAME
   
    
    char piece, command;
    int curr_row, targ_row;
    char curr_col, targ_col;
    
    while(1){ 
    scanf(" %c", &command);
    
    switch(command){
        case 's':
        initial_chess_board(initial_board);
        display_initial_board(initial_board);
        break;
        
        case 'e':
        printf("Exiting the game");
        break;
    }
    
    while(1){
        switch_player(&curr_player);
        printf("%s's turn(%s): ", (curr_player == 'W') ? player1 : player2, (curr_player == 'W') ? "White" : "Black");

    
            scanf(" %c", &piece);
    
        switch(piece){
            case 'p':
                if(Valid_Pawn_Move(curr_row, curr_col, targ_row, targ_col, initial_board)){
                display_initial_board(initial_board);
            }
            break;
        
            case 'n':
                if(Valid_Knight_Move(curr_row, curr_col, targ_row, targ_col, initial_board)){
                display_initial_board(initial_board);
            }
            break;
        
            case 'b':
                if(Valid_Bishop_Move(curr_row, curr_col, targ_row, targ_col, initial_board)){
                display_initial_board(initial_board);
                }
            break;
        
            case 'r':
                if(Valid_Rook_Move(curr_row, curr_col, targ_row, targ_col, initial_board)){
                display_initial_board(initial_board);
            }
            break;
        
            case 'q':
                if(Valid_Queen_Move(curr_row, curr_col, targ_row, targ_col, initial_board)){
                display_initial_board(initial_board);
            }
            break;
        
            case 'k':
                if(Valid_King_Move(curr_row, curr_col, targ_row, targ_col, initial_board)){
                display_initial_board(initial_board);
            }
            break;
        
            default:
            printf("Invalid input");
        
            }
        }
    }
}
















//THIS PART REPRESENTS THE DEFINITION OF ALL THE FUNCTIONS


//THIS PART IS USED TO DESCRIBE THE INITIAL BOARD AT THE START OF THE GAME
void initial_chess_board(char initial_board[8][8]) {
    char initial_data[8][8] = {
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            initial_board[i][j] = initial_data[i][j];
        }
    }
}

//THIS IS FOR DISPLAYING THE CHESS BOARD
void display_initial_board(char initial_board[8][8]){
    for(int i = 0; i < 8; i++){
        printf("%d", 8 - i);
        for(int j = 0; j < 8; j++){
            printf("\t\t|%c|", initial_board[i][j]);
        }
        printf("\n");
    }
     printf("\n\t\ta\t\tb\t\tc\t\td\t\te\t\tf\t\tg\t\th\n");
}

void switch_player(char *curr_player){
    *curr_player = (*curr_player == 'W') ? 'B' : 'W';
}

//THIS IS USED TO CHECK WHITESPACES WHILE ENTERING THE NAMES
int has_white_space(const char *str) {
    while (*str) {
        if (isspace((unsigned char)*str)) {
            return 1; 
        }
        str++;
    }
    return 0; 
}

//THIS IS THE MOVE LOGIC FOR THE PAWN
bool Valid_Pawn_Move(int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]){
    
    
    
    printf("Enter current Pawn position:");
    scanf(" %c%d", &curr_col, &curr_row);
    if(curr_col < 'a'  ||  curr_col > 'h'  ||  curr_row < 1  || curr_row > 8){
        printf("Invalid current position\n");
        return false;
    }
    
    printf("Enter final Pawn position:");
    scanf(" %c%d", &targ_col, &targ_row);
    if(targ_col < 'a'  ||  targ_col > 'h'  ||  targ_row < 1  || targ_row > 8){
        printf("Invalid final position\n");
        return false;
    }
    
    
    
    if(curr_row < 1  ||  curr_row > 8  ||  curr_col < 'a'  ||  curr_col > 'h'  ||  targ_row < 1  ||  targ_row > 8  ||  targ_col < 'a'  ||  targ_col > 'h'){
        printf("Invalid move for the Pawn\n");
        return false;
    }
    if((curr_row == 2  &&  curr_col == targ_col)  &&  (targ_row == curr_row + 2  ||  targ_row == curr_row + 1)){
        initial_board[curr_row - 1][curr_col - 'a'] = '.';
        initial_board[targ_row - 1][targ_col - 'a'] = 'p';
        printf("Valid move for the Pawn\n");
        return true;
    }
    if((curr_row > 2  &&  curr_col == targ_col)  &&  targ_row == curr_row +1){
        printf("Valid move for the Pawn\n");
        return true;
    } else{
        printf("Invalid move for the Pawn\n");
        return false;
    }
}

//THIS IS THE MOVE LOGIC FOR THE KNIGHT
bool Valid_Knight_Move(int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]){
    
    
    
    printf("Enter current Knight position:");
    scanf(" %c%d", &curr_col, &curr_row);
    if(curr_col < 'a'  ||  curr_col > 'h'  ||  curr_row < 1  || curr_row > 8){
        printf("Invalid current position\n");
        return false;
    }
    
    printf("Enter final Knight position:");
    scanf(" %c%d", &targ_col, &targ_row);
    if(targ_col < 'a'  ||  targ_col > 'h'  ||  targ_row < 1  || targ_row > 8){
        printf("Invalid final position\n");
        return false;
    }
    
    
    
    if(curr_row < 1  ||  curr_row > 8  ||  curr_col < 'a'  ||  curr_col > 'h'  ||  targ_row < 1  ||  targ_row > 8  ||  targ_col < 'a'  ||  targ_col > 'h'){
        printf("Invalid move for the Knight");
        return false;
    }
    if((targ_row == curr_row + 2  ||  targ_row == curr_row - 2)  &&  (targ_col == curr_col + 1  ||  targ_col == curr_col - 1)){
        initial_board[curr_row - 1][curr_col - 'a'] = '.';
        initial_board[targ_row - 1][targ_col - 'a'] = 'n';
        printf("Valid move for the knight\n");
        return true;
    } else{
        printf("Invalid move for the knight\n");
        return false;
    }
}

//THIS IS THE MOVE LOGIC FOR THE BISHOP
bool Valid_Bishop_Move(int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]){
    
    
    
    printf("Enter current Bishop position:");
    scanf(" %c%d", &curr_col, &curr_row);
    if(curr_col < 'a'  ||  curr_col > 'h'  ||  curr_row < 1  || curr_row > 8){
        printf("Invalid current position\n");
        return false;
    }
    
    printf("Enter final Bishop position:");
    scanf(" %c%d", &targ_col, &targ_row);
    if(targ_col < 'a'  ||  targ_col > 'h'  ||  targ_row < 1  || targ_row > 8){
        printf("Invalid final position\n");
        return false;
    }
    
    
    
    if (curr_row < 1 || curr_row > 8 || curr_col < 'a' || curr_col > 'h' || targ_row < 1 || targ_row > 8 || targ_col < 'a' || targ_col > 'h') {
        printf("Invalid move for the Bishop");
        return false;
    }

    int row_diff = targ_row - curr_row;
    int col_diff = targ_col - curr_col;

    if (row_diff == col_diff || row_diff == -col_diff) {
        initial_board[curr_row - 1][curr_col - 'a'] = '.';
        initial_board[targ_row - 1][targ_col - 'a'] = 'b';
        printf("Valid move for the bishop\n");
        return true;
    } else {
        printf("Invalid move ofr the bishop\n");
        return false;
    }
}

//THIS IS THE MOVE LOGIC FOR THE ROOK
bool Valid_Rook_Move(int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]){
    
    
    
    printf("Enter current Rook position:");
    scanf(" %c%d", &curr_col, &curr_row);
    if(curr_col < 'a'  ||  curr_col > 'h'  ||  curr_row < 1  || curr_row > 8){
        printf("Invalid current position\n");
        return false;
    }
    
    printf("Enter final Rook position:");
    scanf(" %c%d", &targ_col, &targ_row);
    if(targ_col < 'a'  ||  targ_col > 'h'  ||  targ_row < 1  || targ_row > 8){
        printf("Invalid final position\n");
        return false;
    }
    
    
    
    if (curr_row < 1 || curr_row > 8 || curr_col < 'a' || curr_col > 'h' || targ_row < 1 || targ_row > 8 || targ_col < 'a' || targ_col > 'h') {
        printf("Invalid move for the Rook");
        return false;
    }

    if (curr_row == targ_row || curr_col == targ_col) {
         initial_board[curr_row - 1][curr_col - 'a'] = '.';
        initial_board[targ_row - 1][targ_col - 'a'] = 'r';
        printf("Valid move for the rook\n");
        return true;
    } else {
        printf("Invalid move for the rook\n");
        return false;
    }
}

//THIS IS THE MOVE LOGIC FOR THE QUEEN
bool Valid_Queen_Move(int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]){
    
    
    
    printf("Enter current Queen position:");
    scanf(" %c%d", &curr_col, &curr_row);
    if(curr_col < 'a'  ||  curr_col > 'h'  ||  curr_row < 1  || curr_row > 8){
        printf("Invalid current position\n");
        return false;
    }
    
    printf("Enter final Queen position:");
    scanf(" %c%d", &targ_col, &targ_row);
    if(targ_col < 'a'  ||  targ_col > 'h'  ||  targ_row < 1  || targ_row > 8){
        printf("Invalid final position\n");
        return false;
    }
    
    
    
    if (curr_row < 1 || curr_row > 8 || curr_col < 'a' || curr_col > 'h' || targ_row < 1 || targ_row > 8 || targ_col < 'a' || targ_col > 'h') {
        printf("Invalid move for the Queen");
        return false;
    }

    int row_diff = targ_row - curr_row;
    int col_diff = targ_col - curr_col;

    if (curr_row == targ_row || curr_col == targ_col || row_diff == col_diff || row_diff == -col_diff) {
         initial_board[curr_row - 1][curr_col - 'a'] = '.';
        initial_board[targ_row - 1][targ_col - 'a'] = 'q';
        printf("Valif move for the queen\n");
        return true;
    } else {
        printf("Invalid move for the queen\n");
        return false;
    }
}

//THIS IS THE MOVE LOGIC FOR THE KING
bool Valid_King_Move(int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]){
    
    
    
    printf("Enter current King position:");
    scanf(" %c%d", &curr_col, &curr_row);
    if(curr_col < 'a'  ||  curr_col > 'h'  ||  curr_row < 1  || curr_row > 8){
        printf("Invalid current position\n");
        return false;
    }
    
    printf("Enter final King position:");
    scanf(" %c%d", &targ_col, &targ_row);
    if(targ_col < 'a'  ||  targ_col > 'h'  ||  targ_row < 1  || targ_row > 8){
        printf("Invalid final position\n");
        return false;
    }
    
    
    
    if(curr_row < 1  ||  curr_row > 8  ||  curr_col < 'a'  ||  curr_col > 'h'  ||  targ_row < 1  ||  targ_row > 8  ||  targ_col < 'a'  ||  targ_col > 'h'){
        printf("Invalid move for the King");
        return false;
    }
    int row_diff = targ_row - curr_row;
    int col_diff = targ_col - curr_col;
    
    if((row_diff >= -1  &&  row_diff <= 1)  &&  (col_diff >= -1  &&  col_diff <= 1)){
        initial_board[curr_row - 1][curr_col - 'a'] = '.';
        initial_board[targ_row - 1][targ_col - 'a'] = 'k';
        printf("Valid move for the king\n");
        return true;
    } else{
        printf("Invalid move for the king\n");
        return false;
    }
}
