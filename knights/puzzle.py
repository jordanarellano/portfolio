from logic import *

AKnight = Symbol("A is a Knight")
AKnave = Symbol("A is a Knave")

BKnight = Symbol("B is a Knight")
BKnave = Symbol("B is a Knave")

CKnight = Symbol("C is a Knight")
CKnave = Symbol("C is a Knave")

# Puzzle 0
# A says "I am both a knight and a knave."

knowledge0 = And()

# A is Knight or Knave, but not both
knowledge0.add(Biconditional(AKnight,Not(AKnave)))
knowledge0.add(Biconditional(AKnave,Not(AKnight)))

# If statement true, A is a Knight, else a knave
knowledge0.add(Implication(And(AKnight,AKnave), AKnight))
knowledge0.add(Implication(Not(And(AKnight, AKnave)), AKnave ))


# Puzzle 1
# A says "We are both knaves."
# B says nothing.

knowledge1 = And()

# A Knight or Knave, not both. If not one then the other.
knowledge1.add(Biconditional(AKnight,Not(AKnave)))
knowledge1.add(Biconditional(AKnave,Not(AKnight)))

# B Knight or Knave, not both. If not one then the other.
knowledge1.add(Biconditional(BKnight, Not(BKnave)))
knowledge1.add(Biconditional(BKnave, Not(BKnight)))

# If statement 1 is true, A is a Knight, else a Knave
knowledge1.add(Implication(And(AKnave, BKnave), AKnight))
knowledge1.add(Implication(Not(And(AKnave, BKnave)), AKnave))


# Puzzle 2
# A says "We are the same kind."
# B says "We are of different kinds."
knowledge2 = And()

# A Knight or Knave, not both. If not one then the other.
knowledge2.add(Biconditional(AKnight,Not(AKnave)))
knowledge2.add(Biconditional(AKnave,Not(AKnight)))

# B Knight or Knave, not both. If not one then the other.
knowledge2.add(Biconditional(BKnight, Not(BKnave)))
knowledge2.add(Biconditional(BKnave, Not(BKnight)))

# Statement 1

# If statement 1 is true, A is a knight else, A is knave
knowledge2.add(Implication(Or(And(AKnight, BKnight), And(AKnave, BKnave)), AKnight))
knowledge2.add(Implication(Not(Or(And(AKnight, BKnight), And(AKnave, BKnave))), AKnave))

# Statement 2

# If statement 2 is true, B is a knight, else B is a Knave
knowledge2.add(Implication(Not(Or(And(AKnight, BKnight), And(AKnave, BKnave))), BKnight))
knowledge2.add(Implication(Or(And(AKnight, BKnight), And(AKnave, BKnave)), BKnave))

# Puzzle 3
# A says either "I am a knight." or "I am a knave.", but you don't know which.
# B says "A said 'I am a knave'."
# B says "C is a knave."
# C says "A is a knight."
knowledge3 = And()

# A Knight or Knave, not both. If not one then the other.
knowledge3.add(Biconditional(AKnight,Not(AKnave)))
knowledge3.add(Biconditional(AKnave,Not(AKnight)))

# B Knight or Knave, not both. If not one then the other.
knowledge3.add(Biconditional(BKnight, Not(BKnave)))
knowledge3.add(Biconditional(BKnave, Not(BKnight)))

# C Knight or Knave, not both. If not one then the other.
knowledge3.add(Biconditional(CKnight, Not(CKnave)))
knowledge3.add(Biconditional(CKnave, Not(CKnight)))



# Statement 1

# If statement 1 is true, A is a Knight, else a knave
knowledge3.add(Implication(Or(AKnight,AKnave), AKnight))
knowledge3.add(Implication(Not(Or(AKnight, AKnave)), AKnave))

# Statement 2
knowledge3.add(Implication(AKnave, And(AKnight, BKnight)))
knowledge3.add(Implication(Not(AKnave), And(AKnight, BKnave)))


# Statement 3

# If statement 3 is true, B is a knight, else B is Knave
knowledge3.add(Implication(CKnave, BKnight))
knowledge3.add(Implication(Not(CKnave), BKnave))

# Statement 4

#If statement 4 is true, C is a knight, else C is Knave
knowledge3.add(Implication(AKnight, CKnight))
knowledge3.add(Implication(Not(AKnight), CKnave))


def main():
    symbols = [AKnight, AKnave, BKnight, BKnave, CKnight, CKnave]
    puzzles = [
        ("Puzzle 0", knowledge0),
        ("Puzzle 1", knowledge1),
        ("Puzzle 2", knowledge2),
        ("Puzzle 3", knowledge3)
    ]
    for puzzle, knowledge in puzzles:
        print(puzzle)
        if len(knowledge.conjuncts) == 0:
            print("    Not yet implemented.")
        else:
            for symbol in symbols:
                if model_check(knowledge, symbol):
                    print(f"    {symbol}")


if __name__ == "__main__":
    main()
