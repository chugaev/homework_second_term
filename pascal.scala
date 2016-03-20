def solve(x: Int, y: Int): Int = {
    if ((x == y) || (y == 0)) 1 else solve(x - 1, y) + solve(x - 1, y - 1)
}
