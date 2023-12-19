bool Valid_King_Move(char curr_player, int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8], bool is_castling);
bool Capture_Piece(char curr_player, int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8]);
void handlePawnPromotion(char initial_board[8][8], int targ_row, char targ_col, char curr_player);
bool enPassantCapture(char initial_board[8][8], int curr_row, char curr_col, int targ_row, char targ_col, char curr_player);
bool findKingPosition(char curr_player, char initial_board[8][8], int* king_row, int* king_col);
bool isCheck(char curr_player, char initial_board[8][8]);




bool Valid_King_Move(char curr_player, int curr_row, char curr_col, int targ_row, char targ_col, char initial_board[8][8], bool is_castling){
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
