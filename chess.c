#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <windows.h>



void initial_chess_board(char initial_board[8][8]);
void display_initial_board(char initial_board[8][8]);
void display_rules();
void switch_player(char *curr_player);
int has_white_space(const char *str);
bool Valid_White_Pawn_Move(int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]);
bool Valid_Black_Pawn_Move(int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]);
bool Valid_Rook_Move(char curr_player, int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]);
bool Valid_Bishop_Move(char curr_player, int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]);
bool Valid_Knight_Move(char curr_player, int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]);
bool Valid_Queen_Move(char curr_player, int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]);
bool Valid_King_Move(char curr_player, int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8], bool is_castling);
bool enPassantCapture(char initial_board[8][8], int curr_row, char curr_col, int targ_row, char targ_col, char curr_player);
//bool Capture_Piece(char curr_player, int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8])
void handlePawnPromotion(char initial_board[8][8], int targ_row, char targ_col, char curr_player);
bool findKingPosition(char curr_player, char initial_board[8][8], int* king_row, int* king_col);
bool isCheck(char curr_player, char initial_board[8][8]);
bool canCaptureCheckingPiece(char curr_player, char initial_board[8][8], int king_row, char king_col);
void captureCheckingPiece(char capturing_piece, int capturing_piece_row, int capturing_piece_col, int king_row, int king_col, char initial_board[8][8]);
bool canKingEscapeCheck(char curr_player, char initial_board[8][8], int king_row, int king_col);
void moveKingToEscapeCheck(char curr_player, int* king_row, char* king_col, char initial_board[8][8]);
void copyBoard(char source[8][8], char destination[8][8]);
void movePiece(int start_row, char start_col, int end_row, char end_col, char board[8][8]);
bool canBlock(char initial_board[8][8], char blocking_piece, int blocking_row, char blocking_col, int king_row, char king_col);
void blockMove(char blocking_piece, int blocking_row, char blocking_col, int king_row, char king_col, char initial_board[8][8]);
void handleCheckCondition(char curr_player, char initial_board[8][8], int* king_row, char* king_col);


int main(){
    //initializing variables
    char initial_board[8][8];
    char player1[15], player2[15], color; 
    char curr_player = 'B';
    char piece, command;
    int curr_row, targ_row;
    char curr_col, targ_col;
    bool is_castling = false;

    //do while loop asking for names continuously until entered in a correct format
    do {
        printf("Enter Player 1 name: ");
        fgets(player1, sizeof(player1), stdin);
        player1[strcspn(player1, "\n")] = '\0'; 
        if (has_white_space(player1) || strcmp(player1, player2) == 0) {
            printf("No SPACES are allowed in Names\n");
        }
    } while (has_white_space(player1) || strcmp(player1, player2) == 0);

    do {
        printf("Enter Player 2 name: ");
        fgets(player2, sizeof(player2), stdin);
        player2[strcspn(player2, "\n")] = '\0'; 
        if (has_white_space(player2) || strcmp(player1, player2) == 0) {
            printf("No SPACES are allowed. Both players cannot have the same name\n");
        }
    } while (has_white_space(player2) || strcmp(player1, player2) == 0);

    //do while loop asking for character input continuously until meets the requirements
    do {
        printf("%s, enter the color with which you want to play (B for black, and W for white): ", player1);
        scanf("%c", &color);

        if (color == 'B'){
            printf("%s has chosen black color\n", player1);
            printf("%s has been assigned white color\n\n", player2);
        } else if (color == 'W'){
            printf("%s has chosen white color\n", player1);
            printf("%s has been assigned black color\n\n", player2);
        } else {
            printf("%s there are only two colors in chess\n", player1);
        }
    } while ((color != 'B')  && (color != 'W'));

    //calling displaying rules function
    display_rules();

    //game loop
    while(1){ 
        scanf(" %c", &command);

        //switch case for starting or exiting the game
        switch(command){
            case 's': //starting the game
            initial_chess_board(initial_board);
            display_initial_board(initial_board);

            while(1){
                //switch player function
                switch_player(&curr_player);
                if(color == 'B'){
                    printf("%s's turn(%s): ", (curr_player == 'B') ? player1 : player2, (curr_player == 'W') ? "White" : "Black");
                } 
                if(color == 'W'){
                    printf("%s's turn(%s): ", (curr_player == 'W') ? player1 : player2, (curr_player == 'W') ? "White" : "Black");
                }

    
                scanf(" %c", &piece);
    
                switch(piece){
                    case 'p': //calling white pawn function when entering P
                    if(Valid_White_Pawn_Move(curr_row, curr_col, targ_row, targ_col, initial_board)){
                        display_initial_board(initial_board);
                    }
                    break;

                    case 'P': //calling black pawn function when entering p
                    if(Valid_Black_Pawn_Move( curr_row, curr_col, targ_row, targ_col, initial_board)){
                        display_initial_board(initial_board);
                    }
                    break;

                    case 'N':
                    case 'n':
                    //calling knight function when entering N or n
                    if(Valid_Knight_Move(curr_player, curr_row, curr_col, targ_row, targ_col, initial_board)){
                        display_initial_board(initial_board);
                    }
                    break;

                    case 'B':
                    case 'b':
                    //calling bishop function when entering B or b
                    if(Valid_Bishop_Move(curr_player, curr_row, curr_col, targ_row, targ_col, initial_board)){
                        display_initial_board(initial_board);
                    }
                    break;

                    case 'R':
                    case 'r':
                    //calling rook function when entering R or r
                    if(Valid_Rook_Move(curr_player, curr_row, curr_col, targ_row, targ_col, initial_board)){
                        display_initial_board(initial_board);
                    }
                    break;

                    case 'Q':
                    case 'q':
                    //calling queen function when entering Q or q
                    if(Valid_Queen_Move(curr_player, curr_row, curr_col, targ_row, targ_col, initial_board)){
                        display_initial_board(initial_board);
                    }
                    break;

                    case 'K':
                    case 'k':
                    //calling king function when entering K or k
                    if(Valid_King_Move(curr_player, curr_row, curr_col, targ_row, targ_col, initial_board, is_castling)){
                        display_initial_board(initial_board);
                    }
                    break;
        
                    default:
                    //handling invalid input
                    printf("Invalid input");
        
                }
            }
            break;
        
            case 'e': //ending the game
            printf("Exiting the game");
            break;
        }
    }
}
















//THIS PART REPRESENTS THE DEFINITION OF ALL THE FUNCTIONS


//THIS PART IS USED TO DESCRIBE THE INITIAL BOARD AT THE START OF THE GAME
void initial_chess_board(char initial_board[8][8]) {
    char initial_data[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){//nested for loop for storing the chess board in a 2d array
            initial_board[i][j] = initial_data[i][j];
        }
    }
}

//THIS IS FOR DISPLAYING THE CHESS BOARD
void display_initial_board(char initial_board[8][8]){
    printf("\t\x1b[1;32m    a    b    c    d    e    f    g    h\x1b[0m\n");
    printf("\t\x1b[1;34m|--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--|\x1b[0m\n");
    for(int i = 0; i < 8; i++){
        printf("\x1b[1;32m%d\x1b[0m\t\x1b[1;34m+\x1b[0m", i + 1);
        for(int j = 0; j < 8; j++){
            printf("  |%c|", initial_board[i][j]);
        }
        printf("  \x1b[1;34m+\x1b[0m\n");
        printf("\t\x1b[1;34m|--+-+--+-+--+-+--+-+--+-+--+-+--+-+--+-+--|\x1b[0m\n");
    }
}

//THIS FUNCTION DISPLAYS ALL THE RULES OF CHESS
void display_rules(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("\t\t\t\t\tTHE GAME RULES ARE AS FOLLOWS\n");
    printf("The goal is to checkmate the opponent's king which means to capture the king in such a way that there is no possible escape\n\n");
    
    
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    printf("\t\t\t\t\t\t\tPIECE MOVEMENT\n");
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

}

//THIS FUNCTION SWITCHES PLAYERS AFTER EVERY TURN
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



//THIS IS THE MOVE LOGIC FOR THE WHITE PAWN
bool Valid_White_Pawn_Move(int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]){
    printf("Enter current Pawn position:");
    scanf(" %c%d", &curr_col, &curr_row);
    if(curr_col < 'a'  ||  curr_col > 'h'  ||  curr_row < 1  || curr_row > 8){
        //handling the condition if rows and columns are below '1' and 'a' and exceeding '8' and 'h'
        printf("Invalid current position\n");
        return false;
    }
    
    printf("Enter final Pawn position:");
    scanf(" %c%d", &targ_col, &targ_row);
    if(targ_col < 'a'  ||  targ_col > 'h'  ||  targ_row < 1  || targ_row > 8){
        //handling the condition if rows and columns are below '1' and 'a' and exceeding '8' and 'h'
        printf("Invalid final position\n");
        return false;
    }
    
    
    
    if(curr_row < 1  ||  curr_row > 8  ||  curr_col < 'a'  ||  curr_col > 'h'  ||  targ_row < 1  ||  targ_row > 8  ||  targ_col < 'a'  ||  targ_col > 'h'){
        printf("Invalid move for the Pawn\n");
        return false;
    }

    //Check for a valid move
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
    if ((targ_row == curr_row - 1) && (targ_col == curr_col - 1 || targ_col == curr_col + 1)) {
    // Check if there is an opponent's piece to capture
    char target_piece = initial_board[targ_row - 1][targ_col - 'a'];
    if (target_piece != '.' && isupper(target_piece)) { //isupper is used to check for Uppercase (opposition team)
        // Valid capturing move
        initial_board[curr_row - 1][curr_col - 'a'] = '.';
        initial_board[targ_row - 1][targ_col - 'a'] = 'P';
        printf("Valid move for the Pawn (Capture)\n");
        return true;
    }
}
 printf("Invalid move for the Pawn\n");
    return false;
}



//THIS IS THE MOVE LOGIC FOR THE BLACK PAWN
bool Valid_Black_Pawn_Move(int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]) {
    printf("Enter current Pawn position:");
    scanf(" %c%d", &curr_col, &curr_row);
    if (curr_col < 'a' || curr_col > 'h' || curr_row < 1 || curr_row > 8) {
        //handling the condition if rows and columns are below '1' and 'a' and exceeding '8' and 'h'
        printf("Invalid current position\n");
        return false;
    }

    printf("Enter final Pawn position:");
    scanf(" %c%d", &targ_col, &targ_row);
    if (targ_col < 'a' || targ_col > 'h' || targ_row < 1 || targ_row > 8) {
        //handling the condition if rows and columns are below '1' and 'a' and exceeding '8' and 'h'
        printf("Invalid final position\n");
        return false;
    }

    if (curr_row < 1 || curr_row > 8 || curr_col < 'a' || curr_col > 'h' || targ_row < 1 || targ_row > 8 || targ_col < 'a' || targ_col > 'h') {
        printf("Invalid move for the Pawn\n");
        return false;
    }

    // Check for a valid move
    if ((curr_row == 7 && curr_col == targ_col) && (targ_row == curr_row - 2 || targ_row == curr_row - 1)) {
        initial_board[curr_row - 1][curr_col - 'a'] = '.';
        initial_board[targ_row - 1][targ_col - 'a'] = 'P';
        printf("Valid move for the Pawn\n");
        return true;
    }

    if ((curr_row < 7 && curr_col == targ_col) && targ_row == curr_row - 1) {
        printf("Valid move for the Pawn\n");
        return true;
    }

    // Check for a capturing move
    if ((targ_row == curr_row + 1) && (targ_col == curr_col - 1 || targ_col == curr_col + 1)) {
        // Check if there is an opponent's piece to capture
        char target_piece = initial_board[targ_row - 1][targ_col - 'a'];
        if (target_piece != '.' && islower(target_piece)) { // islower is used to check for lowercase (opposition team)
            // Valid capturing move
            initial_board[curr_row - 1][curr_col - 'a'] = '.';
            initial_board[targ_row - 1][targ_col - 'a'] = 'p';
            printf("Valid move for the Pawn (Capture)\n");
            return true;
        }
    }

    printf("Invalid move for the Pawn\n");
    return false;
}



//THIS IS THE MOVE LOGIC FOR THE ROOK
bool Valid_Rook_Move (char curr_player, int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]) {
    printf("Enter current Rook position:");
    scanf(" %c%d", &curr_col, &curr_row);
    if (curr_col < 'a' || curr_col > 'h' || curr_row < 1 || curr_row > 8) {
        //handling the condition if rows and columns are below '1' and 'a' and exceeding '8' and 'h'
        printf("Invalid current position\n");
        return false;
    }
    
    printf("Enter final Rook position:");
    scanf(" %c%d", &targ_col, &targ_row);
    if (targ_col < 'a' || targ_col > 'h' || targ_row < 1 || targ_row > 8) {
        //handling the condition if rows and columns are below '1' and 'a' and exceeding '8' and 'h'
        printf("Invalid final position\n");
        return false;
    }
    
    if (curr_row < 1 || curr_row > 8 || curr_col < 'a' || curr_col > 'h' || targ_row < 1 || targ_row > 8 || targ_col < 'a' || targ_col > 'h') {
        printf("Invalid move for the Rook\n");
        return false;
    }

    int step;

    if (curr_row == targ_row) { //Move along the same row
        //Determine the direction of movement
        if (curr_col < targ_col) {
            step = 1; //Move to the right
        } else {
            step = -1; //Move to the left
        }

        int col = curr_col + step;

        //Check for pieces in the way
        while (col != targ_col) {
            if (initial_board[curr_row - 1][col - 'a'] != '.') {
                printf("Invalid move due to presence of similar color piece\n");
                return false;
            }
            col += step;
        }

        // Capture while moving along the same row
        if (initial_board[targ_row - 1][targ_col - 'a'] != '.') {
            printf("Capturing move for the Rook\n");
            initial_board[curr_row - 1][curr_col - 'a'] = '.';
            initial_board[targ_row - 1][targ_col - 'a'] = (curr_player == 'W') ? 'r' : 'R';//tenary condition for replacing '.'
            return true;
        }
    } else if (curr_col == targ_col) { //Move along the same column
        //Determine the direction of movement
        if (curr_row < targ_row) {
            step = 1; //Move downwards
        } else {
            step = -1; //Move upwards
        }

        int row = curr_row + step;

        //Check for pieces in the way
        while (row != targ_row) {
            if (initial_board[row - 1][curr_col - 'a'] != '.') {
                printf("Invalid move due to presence of similar color piece\n");
                return false;
            }
            row += step;
        }

        // Capture while moving along the same column
        if (initial_board[targ_row - 1][targ_col - 'a'] != '.') {
            printf("Capturing move for the Rook\n");
            initial_board[curr_row - 1][curr_col - 'a'] = '.';
            initial_board[targ_row - 1][targ_col - 'a'] = (curr_player == 'W') ? 'r' : 'R';//tenary condition for replacing '.'
            return true;
        }
    } else {
        printf("Invalid move for the Rook\n");
        return false;
    }

    // If the move is valid (no capture), update the board
    initial_board[curr_row - 1][curr_col - 'a'] = '.';
    initial_board[targ_row - 1][targ_col - 'a'] = (curr_player == 'W') ? 'r' : 'R';//tenary condition for replacing '.'
    printf("Valid move for the Rook\n");
    return true;
}



//THIS IS THE MOVE LOGIC FOR THE BISHOP
bool Valid_Bishop_Move(char curr_player, int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]) {
    printf("Enter current Bishop position:");
    scanf(" %c%d", &curr_col, &curr_row);
    if (curr_col < 'a' || curr_col > 'h' || curr_row < 1 || curr_row > 8) {
        //handling the condition if rows and columns are below '1' and 'a' and exceeding '8' and 'h'
        printf("Invalid current position\n");
        return false;
    }

    printf("Enter final Bishop position:");
    scanf(" %c%d", &targ_col, &targ_row);
    if (targ_col < 'a' || targ_col > 'h' || targ_row < 1 || targ_row > 8) {
        //handling the condition if rows and columns are below '1' and 'a' and exceeding '8' and 'h'
        printf("Invalid final position\n");
        return false;
    }

    if (curr_row < 1 || curr_row > 8 || curr_col < 'a' || curr_col > 'h' || targ_row < 1 || targ_row > 8 || targ_col < 'a' || targ_col > 'h') {
        printf("Invalid move for the Bishop\n");
        return false;
    }

    //Calculate row and column differences for diagonal movement
    int row_diff = targ_row - curr_row;
    int col_diff = targ_col - curr_col;
    int row_step, col_step;

    //Check if the move follows the diagonal pattern
    if (row_diff == col_diff || row_diff == -col_diff) {
        //Check for pieces in the way
        if (row_diff > 0) {
            row_step = 1;
        } else {
            row_step = -1;
        }

        if (col_diff > 0) {
            col_step = 1;
        } else {
            col_step = -1;
        }

        int row = curr_row + row_step;
        int col = curr_col + col_step;

        while (row != targ_row && col != targ_col) {
            if (initial_board[row - 1][col - 'a'] != '.') {
                printf("Invalid move due to the presence of similar color piece\n");
                return false;
            }
            row += row_step;
            col += col_step;
        }

        //Capturing move for bishop
        if (initial_board[targ_row - 1][targ_col - 'a'] != '.') {
            printf("Capturing move for the Bishop\n");
            initial_board[curr_row - 1][curr_col - 'a'] = '.';
            initial_board[targ_row - 1][targ_col - 'a'] = (curr_player == 'W') ? 'b' : 'B';
            return true;
        }else {
            //If it's not a capturing move, just move to the target position
            initial_board[curr_row - 1][curr_col - 'a'] = '.';
            initial_board[targ_row - 1][targ_col - 'a'] = (curr_player == 'W') ? 'b' : 'B';
            printf("Valid move for the Bishop\n");
            return true;
        }
    }else {
        printf("Invalid move for the Bishop\n");
        return false;
    }
}



//THIS IS THE MOVE LOGIC FOR THE KNIGHT
bool Valid_Knight_Move (char curr_player, int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]){
    printf("Enter current Knight position:");
    scanf(" %c%d", &curr_col, &curr_row);
    if(curr_col < 'a'  ||  curr_col > 'h'  ||  curr_row < 1  || curr_row > 8){
        //handling the condition if rows and columns are below '1' and 'a' and exceeding '8' and 'h'
        printf("Invalid current position\n");
        return false;
    }
    
    printf("Enter final Knight position:");
    scanf(" %c%d", &targ_col, &targ_row);
    if(targ_col < 'a'  ||  targ_col > 'h'  ||  targ_row < 1  || targ_row > 8){
        //handling the condition if rows and columns are below '1' and 'a' and exceeding '8' and 'h'
        printf("Invalid final position\n");
        return false;
    }
    
    if(curr_row < 1  ||  curr_row > 8  ||  curr_col < 'a'  ||  curr_col > 'h'  ||  targ_row < 1  ||  targ_row > 8  ||  targ_col < 'a'  ||  targ_col > 'h'){
        printf("Invalid move for the Knight\n");
        return false;
    }

    int row_diff = targ_row - curr_row;
    int col_diff = targ_col - curr_col;

    if ((row_diff == -2 && col_diff == -1)  ||  (row_diff == 2 && col_diff == -1)  ||  (row_diff == -2 && col_diff == 1)  ||  (row_diff == 2 && col_diff == 1)   ||   
        (row_diff == -1 && col_diff == -2)  ||  (row_diff == 1 && col_diff == -2)  ||  (row_diff == -1 && col_diff == 2)  ||  (row_diff == 1 && col_diff == 2)) {
        if (initial_board[targ_row - 1][targ_col - 'a'] != '.') {
        //Capturing move
        printf("Capturing move for the Knight\n");
        initial_board[curr_row - 1][curr_col - 'a'] = '.';  //Empty the current position
        initial_board[targ_row - 1][targ_col - 'a'] = (curr_player == 'W') ? 'n' : 'N';  // Place the knight in the target position
         } else {
        //Non-capturing move
        printf("Valid move for the Knight\n");
        initial_board[curr_row - 1][curr_col - 'a'] = '.';  //Empty the current position
        initial_board[targ_row - 1][targ_col - 'a'] = (curr_player == 'W') ? 'n' : 'N';  // Place the knight in the target position
    }
    } else {
    printf("Invalid move for the Knight\n");
    //Handle the case where it's an invalid move
}
}



//THIS IS THE MOVE LOGIC FOR THE QUEEN
bool Valid_Queen_Move(char curr_player, int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]){
    printf("Enter current Queen position:");
    scanf(" %c%d", &curr_col, &curr_row);
    if(curr_col < 'a'  ||  curr_col > 'h'  ||  curr_row < 1  || curr_row > 8){
        //handling the condition if rows and columns are below '1' and 'a' and exceeding '8' and 'h'
        printf("Invalid current position\n");
        return false;
    }
    
    printf("Enter final Queen position:");
    scanf(" %c%d", &targ_col, &targ_row);
    if(targ_col < 'a'  ||  targ_col > 'h'  ||  targ_row < 1  || targ_row > 8){
        //handling the condition if rows and columns are below '1' and 'a' and exceeding '8' and 'h'
        printf("Invalid final position\n");
        return false;
    }
    
    
    
    if (curr_row < 1 || curr_row > 8 || curr_col < 'a' || curr_col > 'h' || targ_row < 1 || targ_row > 8 || targ_col < 'a' || targ_col > 'h') {
        printf("Invalid move for the Queen");
        return false;
    }

    int row_diff = targ_row - curr_row;
    int col_diff = targ_col - curr_col;

    //Check for a valid move(combination of bishop and rooks movement)
    if (row_diff == 0 || col_diff == 0 || row_diff == col_diff || row_diff == -col_diff) {//either horizontal, vertical, or diagonal.
        //Check for pieces in the way
        int row_step, col_step;

        if (row_diff > 0) {
            row_step = 1; //move up
        } else if (row_diff < 0) {
            row_step = -1; //move down
        } else {
            row_step = 0; //same row
        }

        if (col_diff > 0) {
            col_step = 1;//move right
        } else if (col_diff < 0) {
            col_step = -1;//move left
        } else {
            col_step = 0;//same column
        }

        int row = curr_row + row_step;
        int col = curr_col + col_step;

        while (row != targ_row || col != targ_col) {  //while loop to check for pieces in between current and target position
            if (initial_board[row - 1][col - 'a'] != '.') {
                printf("Invalid move due to the presence of similar color\n");
                return false;
            }
            row += row_step;
            col += col_step;
        }
           if (initial_board[targ_row - 1][targ_col - 'a'] != '.') {
            // Capturing move
            printf("Capturing move for the Queen\n");
            initial_board[curr_row - 1][curr_col - 'a'] = '.';  //Empty the current position
            initial_board[targ_row - 1][targ_col - 'a'] = (curr_player == 'W') ? 'q' : 'Q';  //Place the queen in the target position
            return true;
        } else {
            // Non-capturing move
            printf("Valid move for the Queen\n");
            initial_board[curr_row - 1][curr_col - 'a'] = '.';  //Empty the current position
            initial_board[targ_row - 1][targ_col - 'a'] = (curr_player == 'W') ? 'q' : 'Q';  //Place the queen in the target position
            return true;
        }
    } else {
        printf("Invalid move for the Queen\n");
        return false;
    }
}



//THIS IS THE MOVE LOGIC FOR THE KING
bool Valid_King_Move(char curr_player, int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8], bool is_castling) {
    printf("Enter current King position:");
    scanf(" %c%d", &curr_col, &curr_row);
    if (curr_col < 'a' || curr_col > 'h' || curr_row < 1 || curr_row > 8) {
        //handling the condition if rows and columns are below '1' and 'a' and exceeding '8' and 'h'
        printf("Invalid current position\n");
        return false;
    }

    printf("Enter final King position:");
    scanf(" %c%d", &targ_col, &targ_row);
    if (targ_col < 'a' || targ_col > 'h' || targ_row < 1 || targ_row > 8) {
        //handling the condition if rows and columns are below '1' and 'a' and exceeding '8' and 'h'
        printf("Invalid final position\n");
        return false;
    }

    if (curr_row < 1 || curr_row > 8 || curr_col < 'a' || curr_col > 'h' || targ_row < 1 || targ_row > 8 || targ_col < 'a' || targ_col > 'h') {
        printf("Invalid move for the King\n");
        return false;
    }

    int row_diff = targ_row - curr_row;
    int col_diff = targ_col - curr_col;

    //Check for a valid move (king can move one step in any direction)
    if (row_diff >= -1 && row_diff <= 1 && col_diff >= -1 && col_diff <= 1) {

        // Check for similar color pieces in the path
        int row_step, col_step;
        if (row_diff > 0) {
            row_step = 1;
        } else if (row_diff < 0) {
            row_step = -1;
        } else {
            row_step = 0;
        }

        if (col_diff > 0) {
            col_step = 1;
        } else if (col_diff < 0) {
            col_step = -1;
        } else {
            col_step = 0;
        }

    int row = curr_row + row_step;
    int col = curr_col - 'a' + col_step;

    while (row != targ_row || col != targ_col - 'a' + 1) {
        if (initial_board[row - 1][col] != '.') {
            // There is a piece in the path
            printf("Invalid move due to the presence of similar color\n");
            return false;
        }

        row += row_step;
        col += col_step;
    }
        if (initial_board[targ_row - 1][targ_col - 'a'] != '.') {
            // Capturing move
            printf("Capturing move for the King\n");
            initial_board[curr_row - 1][curr_col - 'a'] = '.';  //Empty the current position
            initial_board[targ_row - 1][targ_col - 'a'] = (curr_player == 'W') ? 'k' : 'K';  //Place the king in the target position
            return true;
        } else {
            // Non-capturing move
            printf("Valid move for the King\n");
            initial_board[curr_row - 1][curr_col - 'a'] = '.';  // Empty the current position
            initial_board[targ_row - 1][targ_col - 'a'] = (curr_player == 'W') ? 'k' : 'K';  // Place the king in the target position
            return true;
        }
    }

    //Check for castling
    if (is_castling && curr_row == targ_row) {
        if (curr_col == 'e' && (targ_col == 'c' || targ_col == 'g')) {
            //King-side or queen-side castling
            int rook_col = (targ_col == 'c') ? 'a' : 'h';

            //Check if the rook is present
            if (initial_board[curr_row - 1][rook_col - 'a'] == 'r') {
                //Check if the squares between king and rook are empty
                if (initial_board[curr_row - 1][curr_col - 'a'] == '.' &&
                    initial_board[curr_row - 1][curr_col - 'a' + 1] == '.' &&
                    initial_board[curr_row - 1][curr_col - 'a' + 2] == '.') {
                    //Move the king and rook for castling
                    initial_board[curr_row - 1][curr_col - 'a'] = '.';
                    initial_board[curr_row - 1][targ_col - 'a'] = 'k';

                    initial_board[curr_row - 1][rook_col - 'a'] = '.';
                    initial_board[curr_row - 1][targ_col - 'a' - (targ_col == 'c' ? 1 : -1)] = 'r';

                    printf("Valid castling move for the king\n");
                    return true;
                     }
            }
        }
    }
    return false;  //Default case if none of the conditions are satisfied
}


//THIS FUNCTION CONTAINS ALL THE LOGIC FOR CAPTURING
bool Capture_Piece(char curr_player, int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]){
    // Check if the target position is within bounds
    if (targ_row < 1 || targ_row > 8 || targ_col < 'a' || targ_col > 'h') {
        printf("Invalid target position\n");
        return false;
    }

    char target_piece = initial_board[targ_row - 1][targ_col - 'a'];

    // Check if the target square is empty
    if (target_piece == '.') {
        printf("No piece to capture\n");
        return false;
    }

    // Check if there is an opponent's piece to capture
    bool valid_capture = false;
    if ((curr_player == 'W' && islower(target_piece)) || (curr_player == 'B' && isupper(target_piece))) {
        valid_capture = true;
    }

    // Check the type of piece at the target square and perform capturing logic accordingly
    switch (target_piece) {
        case 'B':
        case 'b':
            // Capturing move for Bishop
            printf("Capturing move for the Bishop\n");
            initial_board[curr_row - 1][curr_col - 'a'] = '.';
            initial_board[targ_row - 1][targ_col - 'a'] = (curr_player == 'W') ? 'b' : 'B';
            break;

        case 'K':
        case 'k':
            // Capturing move for King
            printf("Capturing move for the King\n");
            initial_board[curr_row - 1][curr_col - 'a'] = '.';
            initial_board[targ_row - 1][targ_col - 'a'] = (curr_player == 'W') ? 'k' : 'K';
            break;

        case 'Q':
        case 'q':
            // Capturing move for Queen
            printf("Capturing move for the Queen\n");
            initial_board[curr_row - 1][curr_col - 'a'] = '.';
            initial_board[targ_row - 1][targ_col - 'a'] = (curr_player == 'W') ? 'q' : 'Q';
            break;

        case 'N':
        case 'n':
            // Capturing move for Knight
            printf("Capturing move for the Knight\n");
            initial_board[curr_row - 1][curr_col - 'a'] = '.';
            initial_board[targ_row - 1][targ_col - 'a'] = (curr_player == 'W') ? 'n' : 'N';
            break;

        case 'R':
        case 'r':
            // Capturing move for Rook
            printf("Capturing move for the Rook\n");
            initial_board[curr_row - 1][curr_col - 'a'] = '.';
            initial_board[targ_row - 1][targ_col - 'a'] = (curr_player == 'W') ? 'r' : 'R';
            break;

        case 'p':
            if ((targ_row == curr_row - 1) && (targ_col == curr_col - 1 || targ_col == curr_col + 1)) {
            // Check if there is an opponent's piece to capture
                char target_piece = initial_board[targ_row - 1][targ_col - 'a'];
                if (target_piece != '.' && isupper(target_piece)) { //isupper is used to check for Uppercase (opposition team)
                // Valid capturing move
                    initial_board[curr_row - 1][curr_col - 'a'] = '.';
                    initial_board[targ_row - 1][targ_col - 'a'] = 'p';
                    printf("Valid move for the Pawn (Capture)\n");
                    return true;
                }
            } else {
                printf("Invalid move for the Pawn\n");
                return false;
            }
            break;

        case 'P':
            if ((targ_row == curr_row + 1) && (targ_col == curr_col - 1 || targ_col == curr_col + 1)) {
            // Check if there is an opponent's piece to capture
                char target_piece = initial_board[targ_row - 1][targ_col - 'a'];
                if (target_piece != '.' && islower(target_piece)) { // islower is used to check for lowercase (opposition team)
                // Valid capturing move
                    initial_board[curr_row - 1][curr_col - 'a'] = '.';
                    initial_board[targ_row - 1][targ_col - 'a'] = 'P';
                    printf("Valid move for the Pawn (Capture)\n");
                    return true;
                }
            } else {
                    printf("Invalid move for the Pawn\n");
                    return false;
            }
            break;

        default:
            // Handle invalid piece type
            printf("Invalid piece type\n");
            return false;
    }

    return true;
}



//THIS IS THE LOGIC FOR PAWN PROMOTION
void handlePawnPromotion(char initial_board[8][8], int targ_row, char targ_col, char curr_player) {
    if ((curr_player == 'W' && targ_row == 8) || (curr_player == 'B' && targ_row == 1)) {
        printf("Pawn reached promotion rank! Choose a piece (Q, R, N, or B): ");
        char promotedPiece;
        scanf(" %c", &promotedPiece);

        // Validate the chosen piece (you can add more validation if needed)
        if (promotedPiece == 'Q' || promotedPiece == 'R' || promotedPiece == 'N' || promotedPiece == 'B') {
            initial_board[targ_row - 1][targ_col - 'a'] = promotedPiece;
            printf("Pawn promoted to %c!\n", promotedPiece);
        } else {
            printf("There are only 4 alphabets to choose from lol. Pawn promoted to Queen by default.\n");
            initial_board[targ_row - 1][targ_col - 'a'] = 'Q';
        }
    }
}


//THIS IS THE LOGIC FOR ENPASSANT CAPTURE
bool enPassantCapture(char initial_board[8][8], int curr_row, char curr_col, int targ_row, char targ_col, char curr_player) {
    // Check if the target square is a valid position
    if (targ_row < 1 || targ_row > 8 || targ_col < 'a' || targ_col > 'h') {
        return false;
    }

    // Check if the target square is a valid position for En Passant
    if (curr_player == 'W' && targ_row == 5 && initial_board[targ_row - 1][targ_col - 'a'] == 'P') {
        // Check if the last move was a double-step move by a black pawn
        if (initial_board[targ_row][targ_col - 'a'] == 'p') {
            // Valid En Passant capture for white
            initial_board[targ_row][targ_col - 'a'] = '.'; // Remove the captured pawn
            return true;
        }
    } else if (curr_player == 'B' && targ_row == 4 && initial_board[targ_row - 1][targ_col - 'a'] == 'p') {
        // Check if the last move was a double-step move by a white pawn
        if (initial_board[targ_row - 2][targ_col - 'a'] == 'P') {
            // Valid En Passant capture for black
            initial_board[targ_row - 2][targ_col - 'a'] = '.'; // Remove the captured pawn
            return true;
        }
    }

   return false;
}


//THIS FUNCTIONS FINDS THE POSITION OF THE KING
bool findKingPosition(char curr_player, char initial_board[8][8], int* king_row, int* king_col) {
    // Determine the piece representing the king based on the current player
    char king_piece = (curr_player == 'W') ? 'k' : 'K';

    // Iterate through each row of the chessboard
    for (int row = 0; row < 8; ++row) {
        // Iterate through each column of the chessboard
        for (int col = 0; col < 8; ++col) {
            // Check if the current position contains the king piece
            if (initial_board[row][col] == king_piece) {
                // King found
                // Adjust the row and column indices to 1-indexed and character column, respectively
                *king_row = row + 1;
                *king_col = col + 'a';
                return true;  // Return true to indicate that the king was found
            }
        }
    }

    // King not found
    return false;  // Return false to indicate that the king was not found on the chessboard
}


//THIS FUNCTION CHECKS WHETHER THE KING IS IN CHECK OR NOT
bool isCheck(char curr_player, char initial_board[8][8]) {
    int king_row, king_col;
    bool is_castling;
    
    // Find the current player's king position
    if (!findKingPosition(curr_player, initial_board, &king_row, &king_col)) {
        // Handle case where the king is not found (which shouldn't happen in a legal chess position)
        return false;
    }

    // Iterate through the opponent's pieces to see if any can attack the king
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            char piece = initial_board[row][col];
            
            // Check if the piece belongs to the opponent
            if ((curr_player == 'W' && islower(piece)) || (curr_player == 'B' && isupper(piece))) {
                // Check if the piece can attack the king using the corresponding move validation function
                bool validMove = false;
                switch (piece) {
                    case 'p':
                        validMove = Valid_Black_Pawn_Move(row + 1, col + 'a', king_row, king_col, initial_board);
                        break;
                    case 'P':
                        validMove = Valid_White_Pawn_Move(row + 1, col + 'a', king_row, king_col, initial_board);
                        break;
                    case 'r':
                    case 'R':
                        validMove = Valid_Rook_Move(curr_player, row + 1, col + 'a', king_row, king_col, initial_board);
                        break;
                    case 'b':
                    case 'B':
                        validMove = Valid_Bishop_Move(curr_player, row + 1, col + 'a', king_row, king_col, initial_board);
                        break;
                    case 'n':
                    case 'N':
                        validMove = Valid_Knight_Move(curr_player, row + 1, col + 'a', king_row, king_col, initial_board);
                        break;
                    case 'q':
                    case 'Q':
                        validMove = Valid_Queen_Move(curr_player, row + 1, col + 'a', king_row, king_col, initial_board);
                        break;
                    case 'k':
                    case 'K':
                        validMove = Valid_King_Move(curr_player, row + 1, col + 'a', king_row, king_col, initial_board, is_castling);
                        break;
                    default:
                        // Handle other piece types if needed
                        break;
                }

                // Check if the move is valid
                if (validMove) {
                    printf("King is in Check!! Pls protect it\n");
                    return true;
                }
            }
        }
    }

    // No check
    return false;
}


//THIS FUNCTION CHECKS WHETHER THE PIECE GIVING THE CHECK CAN BE CAPTURED OR NOT
bool canCaptureCheckingPiece(char curr_player, char initial_board[8][8], int king_row, char king_col) {
    bool is_castling;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            char piece = initial_board[row][col];

            // Check if the piece belongs to the current player
            if ((curr_player == 'W' && isupper(piece)) || (curr_player == 'B' && islower(piece))) {
                // Check if the piece can legally capture the checking piece using the custom-made piece validation functions
                bool validMove = false;
                switch (piece) {
                    case 'p':
                        validMove = Valid_Black_Pawn_Move(row + 1, col + 'a', king_row, king_col, initial_board);
                        break;
                    case 'P':
                        validMove = Valid_White_Pawn_Move(row + 1, col + 'a', king_row, king_col, initial_board);
                        break;
                    case 'r':
                    case 'R':
                        validMove = Valid_Rook_Move(curr_player, row + 1, col + 'a', king_row, king_col, initial_board);
                        break;
                    case 'b':
                    case 'B':
                        validMove = Valid_Bishop_Move(curr_player, row + 1, col + 'a', king_row, king_col, initial_board);
                        break;
                    case 'n':
                    case 'N':
                        validMove = Valid_Knight_Move(curr_player, row + 1, col + 'a', king_row, king_col, initial_board);
                        break;
                    case 'q':
                    case 'Q':
                        validMove = Valid_Queen_Move(curr_player, row + 1, col + 'a', king_row, king_col, initial_board);
                        break;
                    case 'k':
                    case 'K':
                        validMove = Valid_King_Move(curr_player, row + 1, col + 'a', king_row, king_col, initial_board, is_castling);
                        break;
                    default:
                        // Handle other piece types if needed
                        break;
                }

                // Check if the move is valid
                if (validMove) {
                    printf("Piece at %c%d can capture the checking piece.\n", col + 'a', row + 1);
                    return true;
                }
            }
        }
    }

    // No piece can capture the checking piece
    return false;
}



//THIS FUNCTION CAPTURES THE PIECE GIVING THE CHECK
void captureCheckingPiece(char capturing_piece, int capturing_piece_row, int capturing_piece_col,
                          int king_row, int king_col, char initial_board[8][8]) {
    // Empty the capturing piece's current position
    initial_board[capturing_piece_row - 1][capturing_piece_col - 'a'] = '.';
    // Place the capturing piece at the position of the captured piece
    initial_board[king_row - 1][king_col - 'a'] = capturing_piece;
}



//THIS FUNCTION CHECKS WHETHER THE KING CAN ESCAPE CHECK BY MOVING ITSELF
bool canKingEscapeCheck(char curr_player, char initial_board[8][8], int king_row, int king_col) {
    bool is_castling;
    // Iterate through all possible positions the king can move to
    for (int new_row = 1; new_row <= 8; ++new_row) {
        for (int new_col = 'a'; new_col <= 'h'; ++new_col) {
            // Check if the new position is a legal move for the king
            if (Valid_King_Move(curr_player, king_row, king_col, new_row, new_col, initial_board, is_castling)) {
                // Check if the king is still in check after the move
                char temp_board[8][8];
                copyBoard(initial_board, temp_board);  // Implement a function to copy the board
                movePiece(king_row, king_col, new_row, new_col, temp_board);  // Implement a function to move a piece
                if (!isCheck(curr_player, temp_board)) {
                    // The king can escape check, return true
                    return true;
                }
            }
        }
    }
    // The king cannot escape check
    return false;
}



//THIS FUNCTION MOVES THE KING TO ESCAPE CHECK
void moveKingToEscapeCheck(char curr_player, int* king_row, char* king_col, char initial_board[8][8]) {
    bool is_castling;
    // Display available moves for the king
    printf("Available moves for the king:\n");
    for (int new_row = 1; new_row <= 8; ++new_row) {
        for (int new_col = 'a'; new_col <= 'h'; ++new_col) {
            // Check if the new position is a legal move for the king
            if (Valid_King_Move(curr_player, *king_row, *king_col, new_row, new_col, initial_board, is_castling)) {
                // Check if the king is still in check after the move
                char temp_board[8][8];
                copyBoard(initial_board, temp_board);
                movePiece(*king_row, *king_col, new_row, new_col, temp_board);
                if (!isCheck(curr_player, temp_board)) {
                    // Display the move as an option
                    printf("(%d, %c)\n", new_row, new_col);
                }
            }
        }
    }

    // Ask the player to choose a move
    printf("Enter the row and column to move the king (e.g., 1a): ");
    int new_row;
    char new_col;
    scanf("%d%c", &new_row, &new_col);

    // Check if the chosen move is valid
    if (Valid_King_Move(curr_player, *king_row, *king_col, new_row, new_col, initial_board, is_castling)) {
        // Update the king's position on the board
        movePiece(*king_row, *king_col, new_row, new_col, initial_board);
        // Update the king's position variables
        *king_row = new_row;
        *king_col = new_col;
        printf("King moved to (%d, %c) to escape check!\n", new_row, new_col);
    } else {
        // Invalid move
        printf("Invalid move! King remains in check.\n");
    }
}



// Function to copy the chessboard
void copyBoard(char source[8][8], char destination[8][8]) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            destination[i][j] = source[i][j];
        }
    }
}



// Function to move a piece on the chessboard
void movePiece(int start_row, char start_col, int end_row, char end_col, char board[8][8]) {
    board[end_row - 1][end_col - 'a'] = board[start_row - 1][start_col - 'a'];
    board[start_row - 1][start_col - 'a'] = '.';
}



//THIS FUNCTION IS USED TO CHECK IF ANOTHER PIECE CAN BLOCK THE CHECK
bool canBlock(char initial_board[8][8], char blocking_piece, int blocking_row, char blocking_col, int king_row, char king_col){
    char curr_player;
    // Determine the direction from the blocking piece to the king
    int row_direction = (king_row > blocking_row) ? 1 : -1;
    int col_direction = (king_col > blocking_col) ? 1 : -1;

    // Iterate through the squares between the blocking piece and the king
    for (int row = blocking_row + row_direction, col = blocking_col + col_direction;
         row != king_row || col != king_col;
         row += row_direction, col += col_direction) {

        // Check if the square is empty
        if (initial_board[row - 1][col - 'a'] == '.') {
            // Check if the blocking piece can legally move to this square
            bool validMove = false;

            // Check the move validity based on the type of blocking piece
            switch (blocking_piece) {
                case 'b':
                case 'B':
                    validMove = Valid_Bishop_Move(curr_player, blocking_row, blocking_col, row, col + 'a', initial_board);
                    break;
                case 'q':
                case 'Q':
                    validMove = Valid_Queen_Move(curr_player, blocking_row, blocking_col, row, col + 'a', initial_board);
                    break;
                case 'n':
                case 'N':
                    validMove = Valid_Knight_Move(curr_player, blocking_row, blocking_col, row, col + 'a', initial_board);
                    break;
                case 'r':
                case 'R':
                    validMove = Valid_Rook_Move(curr_player, blocking_row, blocking_col, row, col + 'a', initial_board);
                    break;
                case 'p':
                case 'P':
                    // Check if the pawn can block in horizontal or diagonal path
                    if (row_direction == 0) {  // Vertical path
                        validMove = false;
                    } else {
                        validMove = Valid_White_Pawn_Move(blocking_row, blocking_col, row, col + 'a', initial_board);
                    }
                    break;
                // Add more cases if needed for other blocking pieces
                default:
                    // Handle other piece types if needed
                    break;
            }

            // Check if the move is valid
            if (validMove) {
                return true;
            }
        } else {
            // Square is not empty, break the loop (can't move through other pieces)
            break;
        }
    }

    // No valid blocking move found
    return false;
}



//THIS FUNCTION EXECUTES THE MOVEMENT OF ANOTHER PIECE TO BLOCK CHECK
void blockMove(char blocking_piece, int blocking_row, char blocking_col, int king_row, char king_col, char initial_board[8][8]) {
    // Determine the direction from the blocking piece to the king
    int row_direction = (king_row > blocking_row) ? 1 : -1;
    int col_direction = (king_col > blocking_col) ? 1 : -1;

    // Iterate through the squares between the blocking piece and the king
    for (int row = blocking_row + row_direction, col = blocking_col + col_direction;
         row != king_row || col != king_col;
         row += row_direction, col += col_direction) {

        // Check if the square is empty
        if (initial_board[row - 1][col - 'a'] == '.') {
            // Execute the blocking move
            initial_board[row - 1][col - 'a'] = blocking_piece;
            printf("Blocking move executed.\n");
            return;
        }
    }
}



//THIS FUNCTION CALLS ALL THE FUNCTIONS AND HANDLES OVERALL CHECK CONDITION
void handleCheckCondition(char curr_player, char initial_board[8][8], int* king_row, char* king_col) {
    //Check if the king is in check
    if (isCheck(curr_player, initial_board)) {
        printf("King is in check!\n");

        //Check if the king can escape check
        if (canKingEscapeCheck(curr_player, initial_board, *king_row, *king_col)) {
            moveKingToEscapeCheck(curr_player, king_row, king_col, initial_board);
        } else {
            //Check if any piece can capture the checking piece
            if (canCaptureCheckingPiece(curr_player, initial_board, *king_row, *king_col)) {
                //Identify the capturing piece's location (you need to implement this logic)
                int capturing_piece_row, capturing_piece_col;
                //Assuming you have the capturing piece's location, capture the checking piece
                captureCheckingPiece(initial_board[capturing_piece_row - 1][capturing_piece_col - 'a'], capturing_piece_row, capturing_piece_col, *king_row, *king_col, initial_board);
                printf("Capturing the attacking piece!\n");
            } else {
                //Check if any piece can block the check
                 int blocking_piece_row, blocking_piece_col,blocking_piece, blocking_row, blocking_col;
                if (canBlock(initial_board, blocking_piece, blocking_row, blocking_col, *king_row, *king_col)) {
                    //Identify the blocking piece's location (you need to implement this logic)
                   //Assuming you have the blocking piece's location, block the check
                   blockMove(blocking_piece, blocking_row, blocking_col, *king_row, *king_col, initial_board);
                    printf("Blocking the check!\n");
                } else {
                    //Checkmate, end the game
                    printf("Checkmate! Game over.\n");
                }
            }
        }
    } else {
        printf("No check. Continue the game.\n");
        //Continue with the normal game logic
    }
}
