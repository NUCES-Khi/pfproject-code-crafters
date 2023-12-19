bool canCaptureCheckingPiece(char curr_player, char initial_board[8][8], int king_row, char king_col);
void captureCheckingPiece(char capturing_piece, int capturing_piece_row, int capturing_piece_col, int king_row, int king_col, char initial_board[8][8]);
bool canKingEscapeCheck(char curr_player, char initial_board[8][8], int king_row, int king_col);
void moveKingToEscapeCheck(char curr_player, int* king_row, char* king_col, char initial_board[8][8]);
void copyBoard(char source[8][8], char destination[8][8]);
void movePiece(int start_row, char start_col, int end_row, char end_col, char board[8][8]);
bool canBlock(char initial_board[8][8], char blocking_piece, int blocking_row, char blocking_col, int king_row, char king_col);
void blockMove(char blocking_piece, int blocking_row, char blocking_col, int king_row, char king_col, char initial_board[8][8]);
void handleCheckCondition(char curr_player, char initial_board[8][8], int* king_row, char* king_col);




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