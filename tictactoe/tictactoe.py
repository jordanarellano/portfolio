"""
Tic Tac Toe Player
"""

import math
import copy
import operator

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    count_x = 0
    count_o = 0
    for i in range(3):
        for j in range(3):
            if board[i][j] == X:
                count_x += 1
            if board[i][j] == O:
                count_o += 1

    if count_x > count_o:
        return O
    else:
        return X

def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    possible_actions = []
    for i in range(3):
        for j in range(3):
            if board[i][j] == EMPTY:
                possible_actions.append(tuple((i, j)))
    return possible_actions



def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """

    if action not in actions(board):
        raise Exception("Action not possible")

    board_copy = copy.deepcopy(board)
    current_player = player(board)
    i = action[0]
    j = action[1]
    board_copy[i][j] = current_player
    return board_copy

def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    if player(board) == X:
        last_played = O
    else:
        last_played = X

    for i in range(3):
        count = 0
        for j in range(3):
            if board[i][j] == last_played:
                count += 1
            if count == 3:
                return last_played

    for j in range(3):
        count = 0
        for i in range(3):
            if board[i][j] == last_played:
                count += 1
            if count == 3:
                return last_played

    if board[0][0] == last_played and board[1][1] == last_played and board[2][2] == last_played:
        return last_played

    if board[2][0] == last_played and board[1][1] == last_played and board[0][2] == last_played:
        return last_played

    return None


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    if winner(board) is not None:
        return True

    elif len(actions(board)) == 0:
        return True

    else:
        return False


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    if winner(board) == X:
        our_utility = 1

    elif winner(board) == O:
        our_utility = -1

    else:
        our_utility = 0

    return our_utility


def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    if terminal(board):
        return utility(board)

    if player(board) == X:
        v_dict = {}
        for action in actions(board):
            v = min_value(result(board, action))
            if v == 1:
                return action
            v_dict[action] = v

        # courtesy of: https://stackoverflow.com/questions/268272/getting-key-with-maximum-value-in-dictionary
        max_v = max(v_dict.items(), key=operator.itemgetter(1))[0]
        return max_v

    else:
        v_dict = {}
        for action in actions(board):
            v = max_value(result(board, action))
            if v == -1:
                return action
            v_dict[action] = v
        min_v = min(v_dict.items(), key = operator.itemgetter(1))[0]
        return min_v




def max_value(board):
    if terminal(board):
        return utility(board)
    else:
        v = -2
        for action in actions(board):
            v = max(v, min_value(result(board, action)))
        return v


def min_value(board):
    if terminal(board):
        return utility(board)
    else:
        v = 2
        for action in actions(board):
            v = min(v, max_value(result(board, action)))
        return v

