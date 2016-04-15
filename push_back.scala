def push_back(lst: List[Int], x: Int): List[Int] = {
  if (lst.isEmpty) x :: Nil else lst.head :: push_back(lst.tail, x)
}
