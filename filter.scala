def list_filter(lst: List[Int], x: Int): List[Int] = {
  if (lst.isEmpty) Nil else if (lst.head == x) lst.head :: list_filter(lst.tail, x) else list_filter(lst.tail, x)
}
