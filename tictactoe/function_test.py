from tictactoe import initial_state, player, actions, result, winner, terminal, utility

X = "X"
O = "O"
EMPTY = None

board = [[EMPTY, EMPTY, EMPTY],
         [EMPTY, EMPTY, EMPTY],
         [EMPTY, EMPTY, EMPTY]]

print(terminal(board))
print(player(board))
print(board)
print(actions(board))
action = (0, 0)
print(action)
new_board = result(board,action)
print(new_board)

print(player(new_board))
print(actions(new_board))
action = (1, 0)
print(action)
new_board = result(new_board,action)
print(new_board)

print(player(new_board))
print(actions(new_board))
action = (0,1)
print(action)
new_board = result(new_board,action)
print(new_board)

print(player(new_board))
print(actions(new_board))
action = (1,1)
print(action)
new_board = result(new_board,action)
print(new_board)

print(player(new_board))
print(actions(new_board))
action = (0,2)
print(action)
new_board = result(new_board,action)
print(new_board)

print(terminal(new_board))
print(winner(new_board))
print(utility(new_board))





