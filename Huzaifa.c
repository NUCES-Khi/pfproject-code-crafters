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